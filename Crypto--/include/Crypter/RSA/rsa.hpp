#ifndef __RSA_HPP__
#define __RSA_HPP__

#include <vector>

#include "Crypter/coder.hpp"


namespace rsa{
  typedef unsigned char uchar;

  class RSA: public crypter::Encoder, public crypter::Decoder
  {
  public:
    RSA();
    ~RSA();
  public:
    void encode(std::vector<uchar> &block) override ;
    void decode(std::vector<uchar> &block) override ;
  };

};


#endif
