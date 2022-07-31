/**
 * @file align.h
 * @author Karthick Rajkumar (ukarthickrajkumar@gmail.com)
 * @brief Interface for Align
 * @version 0.1
 * @date 2022-07-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __ALIGN_H__
#define __ALIGN_H__

#ifdef __cplusplus
extern "C" {
#endif

extern unsigned readAlignedBytes(const unsigned char* raw, unsigned rawlen, unsigned char* buf, unsigned buflen);

#ifdef __cplusplus
}
#endif

#endif /*!__ALIGN_H__*/
