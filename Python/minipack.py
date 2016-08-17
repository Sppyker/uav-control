MINIPACKET_MAX_PACKET_LENGTH = 50

MINIPACK_MESSAGE_START = ord('(')
MINIPACK_MESSAGE_END = ord(')')

MINIPACK_MESSAGE_ZERO = ord('0')
MINIPACK_MESSAGE_BASE = 64
MINIPACK_CHAR_BITS = 6



MINIPACK_FLOAT_CHARS = 3;
MINIPACK_FLOAT_SCALAR_BITS = 3;
MINIPACK_FLOAT_MANTISSA_BITS = (MINIPACK_CHAR_BITS * MINIPACK_FLOAT_CHARS) - MINIPACK_FLOAT_SCALAR_BITS - 1;

MINIPACK_FLOAT_MAX_MANTISSA = (1 << MINIPACK_FLOAT_MANTISSA_BITS) - 1;
MINIPACK_FLOAT_MAX_SCALAR = (1 << MINIPACK_FLOAT_SCALAR_BITS) - 1;

MINIPACK_FLOAT_SCALAR_TABLE = [
  0.01,
  1,
  10,
  100,
  1000,
  10000,
  100000,
  1000000,
]




class MinipackInput():
    def __init__(self):
        self.error = False
        self.started = False
        self.index = 0
        self.packet = [0]*MINIPACKET_MAX_PACKET_LENGTH


    def Give(self, ch):

        ch = ord(ch)

        if ch == MINIPACK_MESSAGE_START:
            self.packet[0] = ch
            self.started = True
            self.index = 1
            self.error = False

        elif self.started:

            if self.index == MINIPACKET_MAX_PACKET_LENGTH:
                self.started = False
                self.index = 0;
            else:
                self.packet[self.index] = ch;
                self.index += 1
                if ch == MINIPACK_MESSAGE_END:
                    self.packet[self.index] = 0;
                    
                    index_copy = self.index - 2
                    self.index = 1
                    return index_copy
        return 0

    
    def Char2Bits(self, ch):
        bits = ch - MINIPACK_MESSAGE_ZERO
        if bits >= MINIPACK_MESSAGE_BASE:
            self.error = True
        return bits

    def Unpack(self, char_count):

        if self.error: return 0

        num = 0;
        for i in range(char_count):
            bits = self.Char2Bits( self.packet[self.index + i] )
            num <<= MINIPACK_CHAR_BITS
            num += bits

        self.index += char_count
        return num

    
    def UnpackSigned(self, char_count):
        halfway = 1 << ((char_count*MINIPACK_CHAR_BITS) - 1);

        return self.Unpack(char_count) - halfway; 

    def UnpackFloat(self):
        inum = 0;
        inum = self.Char2Bits(self.packet[self.index]);
        inum <<= 6;
        inum |= self.Char2Bits(self.packet[self.index+1]);
        inum <<= 2;

        b3 = self.Char2Bits(self.packet[self.index+2]);
        inum |= (b3 >> 4) & 0x3;

        
        self.index += 3

        neg = (b3 & 0x8);
        scalar = b3 & 0x7;

        num = float(inum) / MINIPACK_FLOAT_SCALAR_TABLE[scalar];
        if neg: num = -num;

        return num;

    def UnpackError(self):
        return (self.error) or (self.packet[self.index] != MINIPACK_MESSAGE_END)



class MinipackOutput():
    def __init__(self):
        self.index = 1
        self.packet = [0]*MINIPACKET_MAX_PACKET_LENGTH
        self.packet[0] = MINIPACK_MESSAGE_START

    def NewPacket(self):
        self.index = 1

    def Pack(self, char_count, num):
        end_index = self.index + char_count - 1
        for i in range(char_count):
            bits = num & ((1 << MINIPACK_CHAR_BITS)-1)
            self.packet[end_index - i] = self.Bits2Chr(bits)
            num >>= MINIPACK_CHAR_BITS
        self.index += char_count

    def PackSigned(self, char_count, num):
        halfway = 1 << ((char_count*MINIPACK_CHAR_BITS) - 1);
        self.Pack(char_count, halfway + num);


    def PackFloat(self, num):
        neg = num < 0;
        if (neg): num = -num;
        
        i = 0;
        while (i < MINIPACK_FLOAT_MAX_SCALAR) and (num * MINIPACK_FLOAT_SCALAR_TABLE[i+1] < MINIPACK_FLOAT_MAX_MANTISSA):
          i += 1
        
        #print(i)

        inum = int( num*MINIPACK_FLOAT_SCALAR_TABLE[i] );

        self.packet[self.index+2] = self.Bits2Chr( ((inum & 0x3) << 4) | (neg << 3) | i );
        inum >>= 2;
        self.packet[self.index+1] = self.Bits2Chr( inum & 0x3F );
        inum >>= 6;
        self.packet[self.index+0] = self.Bits2Chr( inum & 0x3F );
        self.index += 3;


    def EndPacket(self):
        self.packet[self.index] = MINIPACK_MESSAGE_END
        self.packet[self.index + 1] = 0
        return self.Packet2String(self.packet)

    def Bits2Chr(self, bits):
        return bits + MINIPACK_MESSAGE_ZERO

    def Packet2String(self, packet):
        outgoingpacket = []
        i = 0
        ch = self.packet[i]
        while ch != 0:
            outgoingpacket.append( chr(ch) )
            i += 1
            ch = self.packet[i]

        return "".join(outgoingpacket)



