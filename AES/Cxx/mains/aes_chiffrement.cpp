#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <iomanip>

#include "util.hpp"
#include "diversification.hpp"
#include "aes.hpp"


uchar State[16] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} ;

int longueur_du_bloc = 16 ;

uchar K[16] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} ;

int longueur_de_la_clef = 16 ;

int main(void){
  using namespace AES ;

  Encoder encoder;
  cout << "Clef : " ;
  crypt_util::print_key(K, longueur_de_la_clef);
  cout << "Bloc d'entrée  : " ;
  crypt_util::print_key(State, longueur_du_bloc);
  encoder.encode(State, K, longueur_de_la_clef);
  cout << "Bloc de sortie : " ;
  crypt_util::print_key(State, longueur_du_bloc);

  return EXIT_SUCCESS ;
}
