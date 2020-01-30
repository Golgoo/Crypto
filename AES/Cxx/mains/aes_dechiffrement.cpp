#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <iomanip>

#include "util.hpp"
#include "diversification.hpp"
#include "aes.hpp"

typedef unsigned char uchar ;

uchar State[16] = {
  0x66, 0xEF, 0x88, 0xCA, 0xE9, 0x8A, 0x4C, 0x34, 0x4B, 0x2C, 0xFA, 0x2B, 0xD4, 0x3B, 0x59, 0x2E
};

int longueur_du_bloc = 16 ;

uchar K[16] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} ;

int longueur_de_la_clef = 16 ;

int main(void){
  //Always use this line to init crypt_util::InvSBox ( note the tab Sbox^-1 isn't hard code)
  crypt_util::computeInvSBox();

  using namespace AES ;

  Decoder d(K, longueur_de_la_clef);
  d.decode(State);
  std::cout << "Decrypted :" << std::endl ;
  crypt_util::print_key(State, 16);

  return EXIT_SUCCESS;
}
