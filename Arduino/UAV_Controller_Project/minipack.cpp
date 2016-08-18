
#include "minipack.h"



MinipackInput::MinipackInput()
{
  error = false;
  started = false;
}


byte MinipackInput::Give(char ch)
{
  if ( ch == MINIPACK_MESSAGE_START )
  {
    // new message, start filling buffer
    packet[0] = ch;
    started = true;
    index = 1;
    error = false; // Important to note we clear the error flag here.
  }
  
  else if (started) // if we already have a packet to fill
  {
    if (index == MINIPACKET_MAX_PACKET_LENGTH)
    {
      // buffer overflow inbound... ABORT!
      started = false;
      index = 0;
    }
    else
    {
      packet[index++] = ch; // Load 'er up!
      
      if (ch == MINIPACK_MESSAGE_END) // check for termination
      {
        packet[index] = 0; // null terminate for good measure.
        started = false;
        
        byte index_copy = index - 2; // because we dont include the brackets as part of the packet
        index = 1;
        return index_copy;
      }
    }
  }
  return 0;
}

byte MinipackInput::Chr2Bits(char ch)
{
  byte bits = ch - MINIPACK_MESSAGE_ZERO;
  error |= (bits >= MINIPACK_MESSAGE_BASE);
  return bits;
}

uint32_t MinipackInput::Unpack(byte char_count)
{
  if (error) { return 0; } // if there is a logged error, then dont waste any time
  
  uint32_t num = 0;
  for ( byte i = 0; i < char_count; i++ )
  {
    // for each char, we read it, then decode it
    byte bits = Chr2Bits(packet[index + i]);
    
    num <<= MINIPACK_CHAR_BITS;
    num += bits;
  }
  index += char_count;
  return num;
}

int32_t MinipackInput::UnpackSigned(byte char_count)
{
  uint32_t halfway = 1 << ((char_count*MINIPACK_CHAR_BITS) - 1);
  return Unpack(char_count) - halfway; 
}

float MinipackInput::UnpackFloat()
{
  uint32_t inum = 0;
  inum = Chr2Bits(packet[index++]);
  inum <<= 6;
  inum |= Chr2Bits(packet[index++]);
  inum <<= 2;

  byte b3 = Chr2Bits(packet[index++]);
  inum |= (b3 >> 4) & 0x3;

  bool neg = (b3 & 0x8);
  byte scalar = b3 & 0x7;

  float num = inum / MINIPACK_FLOAT_SCALAR_TABLE[scalar];
  num = (neg) ? -num : num;
  return num;
}

bool MinipackInput::UnpackError()
{
  return ( (error) || (packet[index] != MINIPACK_MESSAGE_END) );
}





MinipackOutput::MinipackOutput()
{
  index = 1;
  packet[0] = MINIPACK_MESSAGE_START;
  packet[1] = 0;
}


void MinipackOutput::NewPacket()
{
  index = 1;
}

void MinipackOutput::Pack(byte char_count, uint32_t num)
{
  byte end_index = index + char_count - 1;
  for (byte i = 0; i < char_count; i++)
  {
    byte bits = num & ((1 << MINIPACK_CHAR_BITS) - 1);
    packet[end_index - i] = Bits2Chr(bits);
    num >>= MINIPACK_CHAR_BITS;
  }
  index += char_count;
}

void MinipackOutput::PackSigned(byte char_count, int32_t num)
{
  uint32_t halfway = 1 << ((char_count*MINIPACK_CHAR_BITS) - 1);
  Pack(char_count, halfway + num);
}

void MinipackOutput::PackFloat(float num)
{
  bool neg = num < 0;
  num = (neg) ? -num : num;

  byte i = 0;
  while ((i < MINIPACK_FLOAT_MAX_SCALAR) && (num * MINIPACK_FLOAT_SCALAR_TABLE[i+1] < MINIPACK_FLOAT_MAX_MANTISSA))
  {
    i++;
  }
  
  uint32_t inum = num*MINIPACK_FLOAT_SCALAR_TABLE[i];

  packet[index+2] = Bits2Chr( ((inum & 0x3) << 4) | (neg << 3) | i );
  inum >>= 2;
  packet[index+1] = Bits2Chr( inum & 0x3F );
  inum >>= 6;
  packet[index+0] = Bits2Chr( inum & 0x3F );
  index += 3;
}

char* MinipackOutput::EndPacket()
{
  packet[index] = MINIPACK_MESSAGE_END;
  packet[index + 1] = 0;

  return packet;
}


char MinipackOutput::Bits2Chr(byte bits)
{
  return bits + MINIPACK_MESSAGE_ZERO;
}














