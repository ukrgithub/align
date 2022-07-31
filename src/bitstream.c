/**
 * @file bitstream.c
 * @author Karthick Rajkumar (ukarthickrajkumar@gmail.com)
 * @brief  bitstream implementation
 * @version 0.1
 * @date 2022-07-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/**
 * -----------------------------------------------------------
 * Include
 * -----------------------------------------------------------
 */
#include <stdio.h>
#include "bitstream.h"

/**
 * -----------------------------------------------------------
 * Defines
 * -----------------------------------------------------------
 */
#define BYTES_TO_BITS(__NUM_BYTES__)      ((__NUM_BYTES__) << 3)
#define BITS_TO_BYTES(__NUM_BITS__)       (((__NUM_BITS__) >> 3))

#define BITS_IN_BYTES                     (8)
#define BITS_REMAINING(__NUM_BITS__)      ((__NUM_BITS__) & 0x07)

/**
 * -----------------------------------------------------------
 * Typedefs
 * -----------------------------------------------------------
 */

typedef unsigned char (*BYTE_EXTRACTOR)(unsigned char byte1, unsigned char byte2);

/**
 * -----------------------------------------------------------
 * Prototypes
 * -----------------------------------------------------------
 */
static unsigned char extractFromBit0(unsigned char byte1, unsigned char byte2);
static unsigned char extractFromBit1(unsigned char byte1, unsigned char byte2);
static unsigned char extractFromBit2(unsigned char byte1, unsigned char byte2);
static unsigned char extractFromBit3(unsigned char byte1, unsigned char byte2);
static unsigned char extractFromBit4(unsigned char byte1, unsigned char byte2);
static unsigned char extractFromBit5(unsigned char byte1, unsigned char byte2);
static unsigned char extractFromBit6(unsigned char byte1, unsigned char byte2);
static unsigned char extractFromBit7(unsigned char byte1, unsigned char byte2);
/**
 * -----------------------------------------------------------
 * Data
 * -----------------------------------------------------------
 */
static BYTE_EXTRACTOR       extractors[] = 
{
    extractFromBit0,
    extractFromBit1,
    extractFromBit2,
    extractFromBit3,
    extractFromBit4,
    extractFromBit5,
    extractFromBit6,
    extractFromBit7
};

/**
 * -----------------------------------------------------------
 * Functions
 * -----------------------------------------------------------
 */

/**
 * @brief to extract a byte value from bit 0
 * 
 * returns the first byte as such and ignores second byte
 *
 * @param byte1  first byte
 * @param byte2  second byte
 * @return unsigned char 
 */
static unsigned char extractFromBit0(unsigned char byte1, unsigned char byte2 __attribute__((unused)))
{
    return (byte1);
}

/**
 * @brief to extract a byte value from bit 1
 *
 * takes 1 bit from second byte and 7 bits from the first byte
 * and forms a byte
 *
 * @param byte1  first byte
 * @param byte2  second byte
 * @return unsigned char 
 */
static unsigned char extractFromBit1(unsigned char byte1, unsigned char byte2)
{
    return ((byte1 << 1) | ((byte2 & 0x80) >> 7));
}

/**
 * @brief to extract a byte value from bit 2
 *
 * takes 2 bits from second byte and 6 bits from the first byte
 * and forms a byte
 *
 * @param byte1  first byte
 * @param byte2  second byte
 * @return unsigned char 
 */
static unsigned char extractFromBit2(unsigned char byte1, unsigned char byte2)
{
    return ((byte1 << 2) | ((byte2 & 0xC0) >> 6));
}

/**
 * @brief to extract a byte value from bit 3
 *
 * takes 3 bits from second byte and 5 bits from the first byte
 * and forms a byte
 *
 * @param byte1  first byte
 * @param byte2  second byte
 * @return unsigned char 
 */
static unsigned char extractFromBit3(unsigned char byte1, unsigned char byte2)
{
    return ((byte1 << 3) | ((byte2 & 0xE0) >> 5));
}

/**
 * @brief to extract a byte value from bit 4
 *
 * takes 4 bits from second byte and 4 bits from the first byte
 * and forms a byte
 *
 * @param byte1  first byte
 * @param byte2  second byte
 * @return unsigned char 
 */
static unsigned char extractFromBit4(unsigned char byte1, unsigned char byte2)
{
    return ((byte1 << 4) | ((byte2 & 0xF0) >> 4));
}

/**
 * @brief to extract a byte value from bit 5
 *
 * takes 5 bits from second byte and 3 bits from the first byte
 * and forms a byte
 *
 * @param byte1  first byte
 * @param byte2  second byte
 * @return unsigned char 
 */
static unsigned char extractFromBit5(unsigned char byte1, unsigned char byte2)
{
    return ((byte1 << 5) | ((byte2 & 0xF8) >> 3));
}

/**
 * @brief to extract a byte value from bit 6
 *
 * takes 6 bits from second byte and 2 bits from the first byte
 * and forms a byte
 *
 * @param byte1  first byte
 * @param byte2  second byte
 * @return unsigned char 
 */
static unsigned char extractFromBit6(unsigned char byte1, unsigned char byte2)
{
    return ((byte1 << 6) | ((byte2 & 0xFC) >> 2));
}

/**
 * @brief to extract a byte value from bit 7
 *
 * takes 7 bits from second byte and 1 bits from the first byte
 * and forms a byte
 *
 * @param byte1  first byte
 * @param byte2  second byte
 * @return unsigned char 
 */
static unsigned char extractFromBit7(unsigned char byte1, unsigned char byte2)
{
    return ((byte1 << 7) | ((byte2 & 0xFE) >> 1));
}

/**
 * @brief to initialise a bit stream
 * 
 * @param bit_stream     bit stream instance
 * @param stream         raw bit stream
 * @param stream_length  stream length
 */
void bitStreamInit(BIT_STREAM* bit_stream, const unsigned char *stream, unsigned stream_length)
{
    bit_stream->stream        = stream;
    bit_stream->stream_length = stream_length;
    bit_stream->byte_offset   = 0;
    bit_stream->bit_offset    = 0;
}

/**
 * @brief to seek to a bit location in the bit stream
 * 
 * @param bit_stream     bit stream instance
 * @param bit_offset     bit offset
 */
void bitStreamSeek(BIT_STREAM* bit_stream, unsigned bit_offset)
{
    bit_stream->byte_offset   = BITS_TO_BYTES(bit_offset);
    bit_stream->bit_offset    = BITS_REMAINING(bit_offset);
}

/**
 * @brief to get a byte from the bit stream from the current offset
 * 
 * @param bit_stream     bit stream instance
 * @return unsigned char 
 */
unsigned char bitStreamGet(BIT_STREAM* bit_stream)
{
    unsigned char    value;

    value = extractors[bit_stream->bit_offset](bit_stream->stream[bit_stream->byte_offset], bit_stream->stream[bit_stream->byte_offset + 1]);

    ++bit_stream->byte_offset;

    return value;
}

/**
 * @brief to check end of stream is reached or not
 * 
 * @param bit_stream   bit stream
 * @return true if end of stream reached
 * @return false otherwise
 */
bool endOfBitStream(BIT_STREAM* bit_stream)
{
    return (bit_stream->stream_length <= (BYTES_TO_BITS(bit_stream->byte_offset) + bit_stream->bit_offset));
}

/**
 * @brief to search a pattern in a bit stream
 * 
 * @param bit_stream 
 * @param start 
 * @param end 
 * @param pattern 
 * @return unsigned 
 */
unsigned bitStreamSearch(BIT_STREAM* bit_stream, unsigned start, unsigned end, BIT_STREAM* pattern)
{
    unsigned       found_at = end + 1;

    if (bit_stream != NULL && pattern != NULL && start < end)
    {
        if (bit_stream->stream_length >= pattern->stream_length)
        {
            bool                pattern_found   = false;
            unsigned            searching_at    = start;

            while (((searching_at + pattern->stream_length) <= end) && (!pattern_found))
            {
                bitStreamSeek(bit_stream, searching_at);
                bitStreamSeek(pattern, 0);

                while (!pattern_found)
                {
                    unsigned char    stream_value  = bitStreamGet(bit_stream);
                    unsigned char    pattern_value = bitStreamGet(pattern);

                    if (stream_value != pattern_value)
                    {
                        break;
                    }
                    else
                    {
                        if (endOfBitStream(pattern))
                        {
                            found_at = searching_at;
                            pattern_found = true;
                            break;
                        }
                    }
                }

                searching_at++;
            }
        }
    }

    return found_at;
}

/** EOF */
