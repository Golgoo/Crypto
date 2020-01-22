#ifndef __AES_HPP__
#define __AES_HPP__

#include <cstdlib>

#include "diversification.hpp"

namespace AES{
  class Encoder{
    public :
      Encoder(KeyExtender keyExtender);
      uchar * encode(uchar *content);
    private :
      uchar current_state[16];
      size_t key_len ;
      KeyExtender keyExtender ;
      void addRoundKey(); // XOR(current_state, roundKey, 16);
  };
  class Decoder{

  };
}

#endif
