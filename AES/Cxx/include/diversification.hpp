#ifndef __DIVERSIFICATION_HPP__
#define __DIVERSIFICATION_HPP__

typedef unsigned char uchar ;

#include <cstdlib>

namespace AES{
  class KeyExtender{
    public :
      KeyExtender(uchar *key, size_t key_len);
      uchar * getExtendedKey();
      size_t getExtendedKeyLen();
    private :
      uchar * key ;
      size_t key_len ;
      size_t extended_key_len ;
      uchar W[240];
      void computeExtendedKey();
  };
};

#endif
