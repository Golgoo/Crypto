#include "util.hpp"

#include <iostream>

void crypt_util::print_key(uchar *clef, int longueur){
  for (int i=0; i<longueur; i++) { std::cout << std::hex << (int)clef[i] ; }
  std::cout << std::endl;
}

uchar crypt_util::CharToHex( char c )
{
    switch( c ) {
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        case 'a': case 'A': return 10;
        case 'b': case 'B': return 11;
        case 'c': case 'C': return 12;
        case 'd': case 'D': return 13;
        case 'e': case 'E': return 14;
        case 'f': case 'F': return 15;
    }
    return 16;
}

void crypt_util::XOR(uchar * dst, uchar * src, size_t len)
{
  for(ssize_t i = 0 ; i < len ; i ++){
    dst[i] ^= src[i];
  }
}

void crypt_util::RotWord(uchar *tab)
{
  uchar tmp ;
  tmp = tab[0];
  for(int i = 0 ; i < 3 ; i ++){
    tab[i] = tab[i+1];
  }
  tab[3] = tmp ;
}

void crypt_util::SubWord(uchar *tab)
{
  for(int i = 0 ; i < 4 ; i ++){
    tab[i] = crypt_util::SBox[tab[i]];
  }
}
