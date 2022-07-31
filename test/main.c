/**
 * @file main.c
 * @author Karthick Rajkumar (ukarthickrajkumar@gmail.com)
 * @brief  Application Entry point
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

/**
 * -----------------------------------------------------------
 * Defines
 * -----------------------------------------------------------
 */

#define TEST_OUTBUT_STREAM_LENGTH                 (4)

/**
 * -----------------------------------------------------------
 * Data
 * -----------------------------------------------------------
 */

static unsigned char         test_stream[] =
{
    0x65, 0x50, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x08, 0x10, 0x18
};

static unsigned char         output_stream[TEST_OUTBUT_STREAM_LENGTH];

/**
 * -----------------------------------------------------------
 * Functions
 * -----------------------------------------------------------
 */

/**
 * @brief Application Entry Point
 * 
 * @param argc number of command line arguments
 * @param argv command line arguments list
 * @return 0 on success, 1 on error
 */
int main (int argc __attribute__((unused)), char *argv[] __attribute__((unused)))
{
    unsigned    output_length = TEST_OUTBUT_STREAM_LENGTH;

    output_length = readAlignedBytes(test_stream,
                                sizeof(test_stream),
                                output_stream,
                                sizeof(output_stream));

    printf ("output length %u\n", output_length);

    unsigned int i = 0;


    while (i < output_length) 
    {
        printf (" 0x%02X", output_stream[i++]);
    }

    printf ("\n");

    return 0;
}

/** EOF */
