#include "Util/util.hpp"

#include <algorithm>

void operation::XOR(std::vector<uchar>& dst, std::vector<uchar>& other, int other_start)
{
  if(dst.size() <= other.size() - other_start){
    for(int i = 0 ; i < dst.size() ; i ++){
      dst[i] ^= other[i + other_start];
    }
  }
}

void operation::RotWord(std::vector<uchar> &v, int shift)
{
  std::rotate(v.begin(), v.begin() + shift, v.end());
}

void operation::SubWord(std::vector<uchar> &v)
{
  for(auto it = v.begin() ; it < v.end() ; it++){
    *it = constantes::SBox[*it];
  }
}

void operation::RCon(std::vector<uchar> &v, int rIndex)
{
  if( (!v.empty()) && (rIndex < 10)){
    v[0] ^= constantes::Rcon[rIndex];
  }
}

uchar operation::gmul(uchar a, uchar b)
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

#include <openssl/sha.h>
std::vector<uchar> hash::_SHA1(std::vector<uchar>& v)
{
  uchar* casted = &v[0];
  uchar resume_sha1[SHA_DIGEST_LENGTH];
  SHA1(casted, v.size(), resume_sha1);

  std::vector<uchar> hashed(resume_sha1, resume_sha1 + SHA_DIGEST_LENGTH);
  return hashed;
}

#include <iostream>
#include <iomanip>
void out::display_block(const std::vector<uchar> &block)
{
  std::cout << std::uppercase << std::hex ;
  for (auto bite : block) {
    std::cout << std::setfill('0') << std::setw(2)
              << (int)bite <<'-' ;
  }
  std::cout << std::endl;
}

void out::display_block(const uchar* block, size_t block_len)
{
  int brake = 16 ;
  std::cout << std::uppercase << std::hex ;
  for(int i = 0 ; i < block_len ; i ++){
    if(i%brake == 0 ) std::cout << std::endl;
    std::cout << "0x"  << std::setfill('0') << std::setw(2) << (int)block[i] <<", " ;
  }
  std::cout << std::endl;
}

uchar convert::CharToHex( char c )
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
