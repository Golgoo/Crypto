#ifndef __RSA_HPP__
#define __RSA_HPP__

#include <vector>
#include <gmp.h>
#include <string>
#include "Crypter/coder.hpp"

namespace rsa{
  typedef unsigned char uchar;

  struct RSA_Key{
    mpz_t n ;
    mpz_t e ;
    mpz_t d ;
  };

  class RSA: public crypter::Encoder, public crypter::Decoder
  {
  public:
    RSA(rsa::RSA_Key key);
    ~RSA();
  private:
    RSA_Key _key ;
    mpz_t _mpz_block ;
    void convert_vector_into_mpz(mpz_t& mpz_dst, std::vector<uchar>& src_vector);
    void convert_mpz_into_vector(std::vector<uchar>& dst_vector, mpz_t& mpz_src);
  public:
    void encode(std::vector<uchar> &block) override ;
    void decode(std::vector<uchar> &block) override ;
  };


  struct RSA_Key create_initialize_rsa_key();
  void clear_rsa_key(RSA_Key rsa_key);


  class Key_Factory{
  public:
    Key_Factory();
    ~Key_Factory();
  private:
    gmp_randstate_t _alea ;
  public:
    struct RSA_Key createRandomKey(int precision);
    struct RSA_Key createWithFixedE(std::string e, int precision);
    static int createDefaultPrecision();
    static bool est_probablement_premier(mpz_t n, int precision);
    static int trouve_nombre_premier(gmp_randstate_t alea, mpz_t& x, int nb_octets, int precision);
  };

};


#endif
