#include "diversification.hpp"

using namespace AES ;
using namespace std ;

#include <iostream>
#include <iomanip>
#include <cstring>
#include "util.hpp"

KeyExtender::KeyExtender(char * key, size_t len): key_len(len)
{
  this->key = (uchar*)malloc(sizeof(uchar) * len);
  computeShortKey(key);

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

#define COL_SIZE 4

void KeyExtender::computeExtendedKey()
{
  uchar tmp[COL_SIZE] ;
  for(int i = 0 ; i < this->key_len ; i ++){
    this->extended_key[i] = this->key[i];
  }
  for(int i = this->key_len ; i < this->extended_key_len ; i+= COL_SIZE)
  {
    //printf("\n------------\n");
    int index = i / COL_SIZE ;
    //printf("index : %d - i : %d\n", index, i);
    for(int j = 0 ; j < COL_SIZE ; j ++){
      tmp[j] = this->extended_key[(i-COL_SIZE) + j];
    }
    //printf("Clée tmp init : ");
    //crypt_util::print_key(tmp , 4);
    if( (index)%Nk == 0 ) {
      //std::cout << "Case i % Nk == 0" << endl;
      crypt_util::RotWord(tmp, COL_SIZE);
      //printf("After RotWord : ");
      //crypt_util::print_key(tmp , 4);
      crypt_util::SubWord(tmp, COL_SIZE);
      //printf("After SubWord : ");
      //crypt_util::print_key(tmp , 4);
      tmp[0] ^= crypt_util::Rcon[(index)/Nk - 1];
      //XorRCon(tmp, (index)/Nk - 1);
      //printf("After XorRCon : ");
      //crypt_util::print_key(tmp, 4);
    }else if(Nk > 6 && (index)%Nk == COL_SIZE){
      crypt_util::SubWord(tmp, COL_SIZE);
    }

    crypt_util::XOR(tmp, this->extended_key + ( index - Nk) * COL_SIZE, COL_SIZE);
    //XorW(tmp, (index - Nk) * 4);
    //printf("After XorW : ");
    //crypt_util::print_key(tmp , 4);
    for(int j = 0 ; j < COL_SIZE ; j ++){
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

void KeyExtender::printRounds()
{
  std::array<unsigned char, 16> key ;
  for(int i = 0 ; i < this->Nr + 1; i ++)
  {
    std::cout << "Round (" << i << ") : " ;
    key = this->getRound(i);
    for (auto it = key.begin() ; it < key.end() ; it ++){
      std::cout << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << (int)(*it);
    }
    std::cout << std::endl ;
  }
}

size_t KeyExtender::getShortKeyLen()
{
  return this->key_len ;
}

array<uchar, 16> KeyExtender::getRound(int i)
{
  array<uchar, 16> key_round;
  uchar * ptr = this->extended_key + i * 16 ;
  for(int k = 0 ; k < 16 ; k ++){
    key_round[k] = ptr[k];
  }
  return key_round;
}

size_t KeyExtender::getNbRound()
{
  return this->Nr + 1 ;
}
