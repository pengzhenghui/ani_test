//  sgin.h
//  sgin
//
//  Created by apple on 2018/4/23.
//  Copyright 漏 2018骞� apple. All rights reserved.
//

#ifndef _Sgin_H
#define _Sgin_H

/*

class Sgin
{
public:
    static char* getSgin();
    static char* getKey();
};
*/
#include <jni.h>
#include <string>
#include <stddef.h> /* for size_t & NULL declarations */

#if defined(_MSC_VER)

typedef unsigned __int32 xxtea_long;

#else

#if defined(__FreeBSD__) && __FreeBSD__ < 5
/* FreeBSD 4 doesn't have stdint.h file */
#include <inttypes.h>
#else
#include <stdint.h>
#endif

typedef uint32_t xxtea_long;

#endif /* end of if defined(_MSC_VER) */



unsigned char *xxtea_encrypt(unsigned char *data, xxtea_long data_len, unsigned char *key, xxtea_long key_len, xxtea_long *ret_length);
unsigned char *xxtea_decrypt(unsigned char *data, xxtea_long data_len, unsigned char *key, xxtea_long key_len, xxtea_long *ret_length);

char* getSgin();
#endif

