/*
 * Copyright (C) 2014 Allwinner Ltd. 
 *
 * Author:
 *	Ryan Chen <ryanchen@allwinnertech.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, version 2 of the
 * License.
 *
 * File: fima.h
 *	File Integrity Measurement Architecture definitions
 */

#ifndef __LINUX_FIMA_H
#define __LINUX_FIMA_H

#include <linux/types.h>
#include <linux/crypto.h>
#include <linux/security.h>
#include <linux/hash.h>

/*FIMV LKM debug mode*/
//#define FIVM_LKM_DEBUG
//#define FIVM_DEBUG_TIMMNG /*To summary the time consume*/

extern int fivm_debug ;
#undef dprintk
#define dprintk(format, arg...)        \
	do { \
		if (fivm_debug) \
		printk(KERN_DEBUG "%s: " format, \
				__FUNCTION__, ## arg);  \
	}while(0)

#define fprintk(format, arg...)        \
	do { \
		if (fivm_debug) \
		printk(format, ## arg);    \
	}while(0)


#define derr(format, arg...)        \
	do { \
		printk(KERN_ERR "%s: " format, \
				__FUNCTION__, ## arg);  \
	}while(0)


#define SHA256_DIGEST_LENGTH	32 
#define SHA512_DIGEST_LENGTH	64
#define SHA_DIG_MAX				SHA512_DIGEST_LENGTH	

#define RSA2048_SIG_LENGTH		256
#define RSA3072_SIG_LENGTH		384
#define RSA_SIG_MAX				RSA3072_SIG_LENGTH

#define FILE_NAME_LEN			512
#define DIR_MAX_FILE_NUM		10000 
#define DIR_BITMAP_BYTES		(DIR_MAX_FILE_NUM/8)
#define  BLK_SIZE				4096 
#define FILE_SIG_MAGIC          0x78381729 

struct FILE_LIST_HEAD{
	unsigned int magic;
	unsigned int version ;
	unsigned char sha_alg[8] ;
	unsigned char sig[RSA_SIG_MAX];
	unsigned char root_dir[64];
	unsigned int  file_cnt ;
	unsigned int  file_name_len ;
	unsigned int  reserved[4];
};

struct FILE_SIG_HEAD{
	unsigned char sig[RSA_SIG_MAX];
	unsigned int magic ;
	char sha_alg[8];
	char rsa_alg[8];
	unsigned char root_dir[64];
	unsigned int total_len;
	unsigned int actual_cnt ; /*actual file count*/
};
struct FILE_SIG{
	unsigned int crc ; /*name crc*/
	unsigned int flag ;
	unsigned char sha[SHA_DIG_MAX];
	unsigned int  name_len;
	unsigned char name[FILE_NAME_LEN];
};


enum{

	FIVM_FULL_PATH =1,
	FIVM_PART_PATH,
	FIVM_FAIL_PATH ,
};

struct fivm_path{
	char *path;
	int flag ;
};

#define MAX_NAME_LEN 64

int fivm_init(void);
int fivm_cleanup(void);
int fivm_enable(void);
int fivm_set(unsigned long);
int fivm_disable(void);

int fivm_calc_hash(struct file *file, char *digest);
int fivm_cleanup(void);
#endif
