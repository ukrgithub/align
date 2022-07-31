/**
 * @file align.c
 * @author Karthick Rajkumar (ukarthickrajkumar@gmail.com)
 * @brief  align implementation
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
#include "align.h"
#include "bitstream.h"

/**
 * -----------------------------------------------------------
 * Defines
 * -----------------------------------------------------------
 */

/**
 * -----------------------------------------------------------
 * Typedefs
 * -----------------------------------------------------------
 */

/**
 * -----------------------------------------------------------
 * Prototypes
 * -----------------------------------------------------------
 */

/**
 * -----------------------------------------------------------
 * Data
 * -----------------------------------------------------------
 */
static unsigned char align_sequence[] = 
{
    0x00, 0x00, 0x00, 0x00, 0x80
};
/**
 * -----------------------------------------------------------
 * Functions
 * -----------------------------------------------------------
 */

/**
 * @brief to read aligned bytes from raw data
 * 
 * @param raw 
 * @param rawlen 
 * @param buf 
 * @param buflen 
 * @return unsigned 
 */
unsigned readAlignedBytes(const unsigned char* raw, unsigned rawlen, unsigned char* buf, unsigned buflen)
{
    BIT_STREAM     stream;
    BIT_STREAM     pattern;
    unsigned       stream_length  = rawlen << 3;
    unsigned       pattern_length = sizeof(align_sequence) << 3;
    unsigned       found_at = 0;
    unsigned       search_from = 0;
    unsigned       data_start = stream_length + 1;
    unsigned       data_length = 0;

    bitStreamInit(&stream, raw, stream_length);
    bitStreamInit(&pattern, align_sequence, pattern_length);

    while (true)
    {
        found_at = bitStreamSearch(&stream, search_from, stream_length, &pattern);
        
        if (found_at > stream_length)
        {
            break;
        }

        search_from = found_at + pattern_length;
        data_start = search_from;

    } while (found_at < stream_length);
    

    if (data_start < stream_length)
    {
        data_length = (stream_length - data_start) >> 3;

        if (data_length > buflen)
        {
            data_length = buflen;
        }

        bitStreamSeek(&stream, data_start);
        unsigned i = 0;
        while (i < data_length)
        {
            buf[i++] = bitStreamGet(&stream);
        }
    }

    return data_length;
}

/** EOF */
