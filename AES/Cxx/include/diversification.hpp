#ifndef __DIVERSIFICATION_HPP__
#define __DIVERSIFICATION_HPP__

typedef unsigned char uchar ;

#include <array>

namespace AES{
  class KeyExtender{
    public :
      KeyExtender(char * key, size_t len);
      KeyExtender(uchar *key, size_t key_len);
      uchar * getExtendedKey();
      size_t getExtendedKeyLen();
      uchar * getShortKey();
      size_t getShortKeyLen();
      std::array<uchar, 16> getRound(int i);
      size_t getNbRound();
      void printRounds();
    private :
      uchar * key ;
      size_t key_len ;
      size_t extended_key_len ;
      uchar extended_key[240];
      uchar short_key[32];
      int Nk, Nr ;
      void init();
      void computeExtendedKey();
      void computeShortKey(char *);
  };
};

#endif
