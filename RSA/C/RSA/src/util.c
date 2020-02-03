#include "util.h"

#include <time.h>

int m_log(char *nbr, int nbr_base, char * log_base)
{
  mpz_t n;
  mpz_init(n);
  mpz_set_str(n, nbr, nbr_base);
  mpz_t q ;
  mpz_init(q);
  mpz_t d ;
  mpz_init(d);
  mpz_set_str(d,log_base,nbr_base);
  int i = 0 ;
  while(mpz_cmp_d(n, 1) > 0){
    mpz_tdiv_q(n, n, d);
    i++;
  }
  mpz_clear(n);
  mpz_clear(q);
  mpz_clear(d);
  return i ;
}

bool est_probablement_premier(mpz_t n, int precision)
{
  return(mpz_probab_prime_p(n, precision) > 0);
}

//mpz_urandomm (mpz_t rop, gmp_randstate_t state, const mpz_t n)

int trouve_nombre_premier(gmp_randstate_t alea, mpz_t * x, int nb_octets, int precision)
{
  int i = 0 ;
  do{
    mpz_rrandomb(*x, alea, nb_octets);

    if(mpz_odd_p(*x)==0){
      mpz_add_ui(*x, *x, 1);
    }
    i ++ ;
  }while(! est_probablement_premier(*x, precision));
  return i ;
}

rsa_key_s fabrique(int precision){
  gmp_randstate_t alea;
  gmp_randinit_default(alea);
  gmp_randseed_ui(alea, time(NULL));

  rsa_key_s rsa_key;
  mpz_inits(rsa_key.d, rsa_key.e, rsa_key.n, (void*)NULL);

  mpz_t p, q ;
  mpz_inits(p, q, (void*)NULL);

  trouve_nombre_premier(alea, &p, 1024, precision);
  trouve_nombre_premier(alea, &q, 1024, precision);

  mpz_mul(rsa_key.n, p, q);

  mpz_t w ; mpz_init(w);
  mpz_sub_ui(p, p, 1);
  mpz_sub_ui(q, q, 1);
  mpz_mul(w , p, q);


  mpz_t tmp, wprime, l ;
  mpz_inits(tmp, wprime, l, (void*)NULL);
  mpz_sub_ui(wprime, w, 1); // w' <- w - 1
  do{
    mpz_urandomm(rsa_key.d, alea, wprime); // d <- [0, w-2]
    mpz_add_ui(rsa_key.d, rsa_key.d, 1); // d <- [1 , w-1]
    mpz_gcdext(tmp, l, rsa_key.e, w, rsa_key.d); // tmp = pgcd ( w , d) & e*d + l*w = tmp
  }while(mpz_cmp_d(tmp, 1) != 0);
  if(mpz_sgn(rsa_key.e)<0){
    mpz_add(rsa_key.e, rsa_key.e, w);
  }
  mpz_clears(tmp, wprime, l, (void*)NULL);

  mpz_clear(w);
  mpz_clears(p, q, (void*)NULL);

  return rsa_key ;
}

rsa_key_s fabrique_RFC_4871(int precision){
  gmp_randstate_t alea;
  gmp_randinit_default(alea);
  gmp_randseed_ui(alea, time(NULL));

  rsa_key_s rsa_key;
  mpz_inits(rsa_key.d, rsa_key.e, rsa_key.n, (void*)NULL);
  mpz_set_str(rsa_key.e, "65537", 10);

  mpz_t p, q ;
  mpz_t l ;
  mpz_inits(l, (void*)NULL);
  mpz_inits(p, q, (void*)NULL);
  mpz_t w ; mpz_init(w);
  mpz_t tmp ; mpz_init(tmp);
  do{
    trouve_nombre_premier(alea, &p, 1024, precision);
    trouve_nombre_premier(alea, &q, 1024, precision);
    mpz_mul(rsa_key.n, p, q);
    mpz_sub_ui(p, p, 1);
    mpz_sub_ui(q, q, 1);
    mpz_mul(w , p, q);
    mpz_gcdext(tmp, l, rsa_key.d, w, rsa_key.e);
  }while(mpz_cmp_d(tmp, 1)!=0);

  if(mpz_sgn(rsa_key.d) < 0){
    mpz_add(rsa_key.d, rsa_key.d, w);
  }

  mpz_clears(tmp, l, (void*)NULL);

  mpz_clear(w);
  mpz_clears(p, q, (void*)NULL);

  return rsa_key ;
}
