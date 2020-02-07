#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <iomanip>

#include "util.hpp"
#include "diversification.hpp"
#include "aes.hpp"
#include <time.h>

uchar State[16] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} ;

int longueur_du_bloc = 16 ;

uchar K[16] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} ;

uchar InitV[16] =
{
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

int longueur_de_la_clef = 16 ;

int main(int argc, char *argv[]){
  using namespace AES ;

  /*
  if(argc !=2){
    printf("Usage: %s <clef en hexadécimal>", argv[0]);
    exit(EXIT_FAILURE);
  }
  int longueur_de_la_clef = strlen(argv[1]) >> 1; // Il faut 2 caractères hexadécimaux pour un octet
  if((longueur_de_la_clef != 16) && (longueur_de_la_clef != 24) && (longueur_de_la_clef != 32)){
    printf("Usage: %s clef en hexadécimal (formée de 128, 192 ou 256 bits)\n", argv[0]);
    printf("\t Une clef AES est formée de 32, 48, ou 64 caractères hexadécimaux,\n");
    printf("\t c'est-à-dire 128, 192, ou 256 bits.\n");
    exit(EXIT_FAILURE);
  }
  Encoder encoder(argv[1]);
  */

  Block SBlock (4, 4, State);
  Block InitBloc(4,4, InitV);

  Encoder encoder(K, longueur_de_la_clef);
  cout << "Clef : " ;
  crypt_util::print_key(K, longueur_de_la_clef);
  cout << "Bloc d'entrée  : " << endl ;
  crypt_util::print_key(State, longueur_du_bloc);
  cout << "Vecteur d'initialisation" << std::endl ;

  encoder.encode(SBlock) ;
  cout << "Bloc de sortie : " << endl ;
  for(int i = 0 ; i < 4 ; i ++){
    for(int j = 0 ; j < 4 ; j ++){
      std::cout << std::setfill('0') << std::setw(2)
                << std::uppercase << std::hex << (int)SBlock.get(i,j) << ' ' ;
    }
    std::cout << std::endl ;
  }

  return EXIT_SUCCESS ;
}
