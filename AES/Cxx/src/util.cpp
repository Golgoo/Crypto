#include "util.hpp"

#include <iostream>
#include <iomanip>

void crypt_util::print_key(uchar *clef, int longueur){
  for (int i=0; i<longueur; i++) {
    std::cout << std::setfill('0') << std::setw(2)
              << std::uppercase << std::hex
              << (int)clef[i] ;
  }
  std::cout << std::endl;
}

//https://stackoverflow.com/questions/33982870/how-to-convert-char-array-to-hexadecimal
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
  for(int i = 0 ; i < len ; i ++){
    dst[i] ^= src[i];
  }
}

void crypt_util::RotWord(uchar *tab, size_t len, int shift)
{
  if(len <= 0 ) return ;
  if(shift < 0 ) return ;
  uchar * tmp = (uchar*)malloc(sizeof(unsigned char) * shift) ;
  for(int i = 0 ; i < shift ; i ++){
    tmp[i] = tab[i];
  }
  for(int i = 0 ; i < len - shift ; i ++){
    tab[i] = tab[i+shift];
  }
  if(shift)
  for(int i = len - shift, j = 0 ; i < len ; i ++, j++){
    tab[i] = tmp[j] ;
  }
  free(tmp);
}

void crypt_util::SubWord(uchar *tab, size_t len)
{
  for(int i = 0 ; i < len ; i ++){
    tab[i] = crypt_util::SBox[tab[i]];
  }
}

uchar crypt_util::gmul(uchar a, uchar b)
{
  uchar p = 0;
  uchar hi_bit_set;
  for(int i = 0; i < 8; i++) {
    if((b & 1) == 1) p ^= a;
    hi_bit_set = (a & 0x80);
    a <<= 1;
    if(hi_bit_set == 0x80) a ^= 0x1b;
    b >>= 1;
  }
  return p & 0xFF;
}

void crypt_util::MixColumns(uchar *tab)
{
  int il ; uchar tmp [4] ;
  for(int col = 0 ; col < 4 ; col ++){
    il = 0 ;
    for(int j = 0 ; j < 4 ; j ++){
      tmp[j] = 0 ;
      for(int l = col ; l <=col + 12 ; l += 4){
        tmp[j] ^= crypt_util::gmul(tab[l], crypt_util::CBox[il++]);
      }
    }
    for(int j = 0 ; j < 4 ; j ++){
      tab[j * 4 + col] = tmp[j] ;
    }
  }
}
