#ifndef __AES_HPP__
#define __AES_HPP__

#include <vector>
#include "Crypter/coder.hpp"

namespace aes{

  typedef unsigned char uchar ;

  class AES : public crypter::Encoder, public crypter::Decoder
  {
  public:
    void encode(std::vector<uchar>& block) override ;
    void decode(std::vector<uchar>& block) override ;
  };


};


#endif
