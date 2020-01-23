#ifndef __AES_HPP__
#define __AES_HPP__

#include "diversification.hpp"

namespace AES{
  class Encoder{
    public :
      Encoder();
      ~Encoder();
      uchar * encode(uchar *content, char *key);
      uchar * encode(uchar * content, uchar * key, size_t len);
    private :
      uchar *current_state;
      size_t key_len ;
      KeyExtender * keyExtender ;
      void encode_algo();
  };
  class Decoder{
    
  };
}

#endif
