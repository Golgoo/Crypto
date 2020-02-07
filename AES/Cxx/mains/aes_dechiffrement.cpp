#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <iomanip>

#include "util.hpp"
#include "aes.hpp"
#include "block.hpp"

typedef unsigned char uchar ;


uchar State[16] = {
  0x66, 0xE9, 0x4B, 0xD4,
  0xEF, 0x8A, 0x2C, 0x3B,
  0x88, 0x4C, 0xFA, 0x59,
  0xCA, 0x34, 0x2B, 0x2E
};

int longueur_du_bloc = 16 ;

uchar K[16] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} ;

int longueur_de_la_clef = 16 ;

int main(void){
  //Always use this line to init crypt_util::InvSBox ( note the tab Sbox^-1 isn't hard code)
  crypt_util::computeInvSBox();

  using namespace AES ;

  Block StateBlock(4, 4, State);
  std::cout << "Bloc d'entrée :" << std::endl ;
  StateBlock.printBlock();
  Decoder d(K, longueur_de_la_clef);
  d.decode(StateBlock);
  std::cout << "Decrypted :" << std::endl ;
  StateBlock.printBlock();
  //crypt_util::print_key(State, 16);

  return EXIT_SUCCESS;
}
