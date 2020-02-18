#include "Crypter/RSA/rsa.hpp"

using namespace rsa;

#include <ctime>

struct RSA_Key rsa::create_initialize_rsa_key()
{
  RSA_Key key ;
  mpz_inits(key.d, key.e, key.n, (void*)NULL);
  return key ;
}


void rsa::clear_rsa_key(RSA_Key rsa_key)
{
  mpz_clears(rsa_key.d, rsa_key.e, rsa_key.n, (void*)NULL);
}

#include <string>
int m_log(std::string nbr, int nbr_base, std::string log_base)
{
  mpz_t n;
  mpz_init(n);
  mpz_set_str(n, nbr.c_str(), nbr_base);
  mpz_t q ;
  mpz_init(q);
  mpz_t d ;
  mpz_init(d);
  mpz_set_str(d,log_base.c_str(),nbr_base);
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

int Key_Factory::createDefaultPrecision()
{
  return m_log("1000000000000000", 10, "4");
}

Key_Factory::Key_Factory()
{
  gmp_randinit_default(_alea);
  gmp_randseed_ui(_alea, time(NULL));
}

Key_Factory::~Key_Factory()
{

}

bool Key_Factory::est_probablement_premier(mpz_t n, int precision)
{
  return(mpz_probab_prime_p(n, precision) > 0);
}

int Key_Factory::trouve_nombre_premier(gmp_randstate_t alea, mpz_t& x, int nb_octets, int precision)
{
  int i = 0 ;
  do{
    mpz_rrandomb(x, alea, nb_octets);

    if(mpz_odd_p(x)==0){
      mpz_add_ui(x, x, 1);
    }
    i ++ ;
  }while(! est_probablement_premier(x, precision));
  return i ;
}

RSA_Key Key_Factory::createWithFixedE(std::string e, int precision)
{
  RSA_Key rsa_key;
  mpz_inits(rsa_key.d, rsa_key.e, rsa_key.n, (void*)NULL);
  mpz_set_str(rsa_key.e, "65537", 10);

  mpz_t p, q ;
  mpz_t l ;
  mpz_inits(l, (void*)NULL);
  mpz_inits(p, q, (void*)NULL);
  mpz_t w ; mpz_init(w);
  mpz_t tmp ; mpz_init(tmp);
  do{
    trouve_nombre_premier(_alea, p, 1024, precision);
    trouve_nombre_premier(_alea, q, 1024, precision);
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
