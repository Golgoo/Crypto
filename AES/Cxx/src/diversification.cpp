#include "diversification.hpp"

using namespace AES ;
using namespace std ;

#include <iostream>
#include <cstring>
#include "util.hpp"

KeyExtender::KeyExtender(char * key, size_t len): key_len(len)
{
  computeShortKey(key);
  std::cout << "Key len :: " << this->key_len ;
  crypt_util::print_key(this->key, this->key_len);
  init();
}

KeyExtender::KeyExtender(uchar * key, size_t len): key(key), key_len(len)
{
  init();
}

void KeyExtender::init()
{
  if (this->key_len == 16){
    Nr = 10; Nk = 4;
  } else if (this->key_len == 24){
    Nr = 12; Nk = 6;
  } else {
    Nr = 14; Nk = 8;
  }
  this->extended_key_len = 4*(4*(Nr+1));
  computeExtendedKey();
}

void KeyExtender::computeShortKey(char * clef_en_hexa)
{
  int a,b ;
  int len = strlen(clef_en_hexa);
  for(int i = 0, j = 0 ; i < len ; i += 2, j++ ){
    a = crypt_util::CharToHex(clef_en_hexa[i]);
    b = crypt_util::CharToHex(clef_en_hexa[i + 1]);
    if(a > 15 || b > 15){
      std::cerr << "La clée doit être saisie en hexédécimale :\n" ;
      if(a > 15){
        std::cerr << clef_en_hexa[i] << endl ;
      }
      if(b > 15){
        std::cerr << clef_en_hexa[i+1] << endl ;
      }
      std::cerr << " n'est pas en hexadécimale\n" ;
      exit(EXIT_FAILURE);
    }
    this->key[j] = a << 4 ;
    this->key[j] += b ;
  }
}

void KeyExtender::computeExtendedKey()
{
  uchar tmp[4] ;
  for(int i = 0 ; i < this->key_len ; i ++){
    this->extended_key[i] = this->key[i];
  }
  for(int i = this->key_len ; i < this->extended_key_len ; i+= 4)
  {
    //printf("\n------------\n");
    int index = i / 4 ;
    //printf("index : %d - i : %d\n", index, i);
    for(int j = 0 ; j < 4 ; j ++){
      tmp[j] = this->extended_key[(i-4) + j];
    }
    //printf("Clée tmp init : ");
    //crypt_util::print_key(tmp , 4);
    if( (index)%Nk == 0 ) {
      //std::cout << "Case i % Nk == 0" << endl;
      crypt_util::RotWord(tmp);
      //printf("After RotWord : ");
      //crypt_util::print_key(tmp , 4);
      crypt_util::SubWord(tmp);
      //printf("After SubWord : ");
      //crypt_util::print_key(tmp , 4);
      tmp[0] ^= crypt_util::Rcon[(index)/Nk - 1];
      //XorRCon(tmp, (index)/Nk - 1);
      //printf("After XorRCon : ");
      //crypt_util::print_key(tmp, 4);
    }else if(Nk > 6 && (index)%Nk == 4){
      crypt_util::SubWord(tmp);
    }

    crypt_util::XOR(tmp, this->extended_key + ( index - Nk) * 4, 4);
    //XorW(tmp, (index - Nk) * 4);
    //printf("After XorW : ");
    //crypt_util::print_key(tmp , 4);
    for(int j = 0 ; j < 4 ; j ++){
      this->extended_key[i + j] = tmp[j];
    }
  }
}

uchar * KeyExtender::getExtendedKey()
{
  return this->extended_key ;
}

size_t KeyExtender::getExtendedKeyLen()
{
  return this->extended_key_len ;
}

uchar * KeyExtender::getShortKey()
{
  return this->key ;
}

size_t KeyExtender::getShortKeyLen()
{
  return this->key_len ;
}

std::vector<unsigned char> KeyExtender::getRound(int i)
{
  std::vector<unsigned char> v;
  uchar * ptr = this->extended_key + i * 16 ;
  for(int k = 0 ; k < 16 ; k ++){
    v.push_back(ptr[k]);
  }
  return v;
}

size_t KeyExtender::getNbRound()
{
  return this->Nr + 1 ;
}
