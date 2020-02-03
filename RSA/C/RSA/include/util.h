#ifndef __UTIL_H__
#define __UTIL_H__

#include <gmp.h>
#include <stdbool.h>

struct rsa_key{
  mpz_t d ;
  mpz_t e ;
  mpz_t n ;
};
typedef struct rsa_key rsa_key_s ;

int m_log(char *nbr, int nbr_base, char * log_base);

int trouve_nombre_premier(gmp_randstate_t alea, mpz_t *x, int nb_octets, int precision);

bool est_probablement_premier(mpz_t n, int precision);

rsa_key_s fabrique(int precision);
rsa_key_s fabrique_RFC_4871(int precision);

#endif
