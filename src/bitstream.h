/**
 * @file bit_stream.h
 * @author Karthick Rajkumar (ukarthickrajkumar@gmail.com)
 * @brief Interface for bit stream
 * @version 0.1
 * @date 2022-07-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __BITSTREAM_H__
#define __BITSTREAM_H__

#include <stdbool.h>

typedef struct tagBitStream
{
    const unsigned char  *stream;
    unsigned              stream_length;        /**< length in bits */
    unsigned              bit_offset;
    unsigned              byte_offset;

}BIT_STREAM;

void bitStreamInit(BIT_STREAM* bit_stream, const unsigned char *stream, unsigned stream_length);
void bitStreamSeek(BIT_STREAM* bit_stream, unsigned bit_offset);
unsigned char bitStreamGet(BIT_STREAM* bit_stream);
bool endOfBitStream(BIT_STREAM* bit_stream);
unsigned bitStreamSearch(BIT_STREAM* bit_stream, unsigned offset, unsigned end, BIT_STREAM* pattern);

#endif /*!__BITSTREAM_H__*/
