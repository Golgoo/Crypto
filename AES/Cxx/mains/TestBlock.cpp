#include <iostream>

#include <iomanip>
#include "block.hpp"

typedef unsigned char uchar ;

#include "util.hpp"

/*
0E 0B 0D 09
09 0E 0B 0D
0D 09 0E 0B
0B 0D 09 0E
*/

/*
uchar State[16] = {
  0x0E, 0x09, 0x0D, 0x0B, 0x0B, 0x0E, 0x09, 0x0D,
  0x0D, 0x0B, 0x0E, 0x09, 0x09, 0x0D, 0x0B, 0x0E} ;
*/

/*
00 00 00 00
01 01 01 01
02 02 02 02
03 03 03 03

63 63 63 63
7C 7C 7C 7C
77 77 77 77
7B 7B 7B 7B
*/
uchar State[16] = {
  0x63, 0x7C, 0x77, 0x7B, 0x63, 0x7C, 0x77, 0x7B,
  0x63, 0x7C, 0x77, 0x7B, 0x63, 0x7C, 0x77, 0x7B} ;

  /*
  62 62 62 62
  63 63 63 63
  63 63 63 63
  63 63 63 63
  */
uchar Round[16] = {
  0x62, 0x63, 0x63, 0x63,
  0x62, 0x63, 0x63, 0x63,
  0x62, 0x63, 0x63, 0x63,
  0x62, 0x63, 0x63, 0x63
};

int longueur_du_bloc = 16 ;

uchar K[16] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} ;

int longueur_de_la_clef = 16 ;

int main(int argc, char *argv[]){
  crypt_util::computeInvSBox();
  Block C(4, 4, crypt_util::CBox);
  Block IC(4, 4, crypt_util::InvCBox);

  for(int i = 0 ; i < 4 ; i ++){
    C.MulCol(i, IC);
  }

  C.printBlock();
/*
  for(int i = 0 ; i < 4 ; i ++){
    for(int j = 0 ; j < 4 ; j ++){
      std::cout << std::setfill('0') << std::setw(2)
                << std::uppercase << std::hex << (int)b.get(i,j) << ' ' ;
    }
    std::cout << std::endl ;
  }
*/
  return EXIT_SUCCESS ;
}
