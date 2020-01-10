#define _GNU_SOURCE
#ifndef __HMAC_H__
#define __HMAC_H__

#include <stdio.h>

void seek_f_to_corpse(FILE * fichier);

unsigned char * md5_string(char * string);

char * mail_hash_func(FILE *fichier);

char * mail_hash_func_RFC_2104(FILE *fichier);

char * generate_secret();

char * load_header_value(FILE* fichie, char * field_value);

void write_x_auth(char* filename, char* value);

char * convert_md5_to_string(unsigned char * str);

#endif
