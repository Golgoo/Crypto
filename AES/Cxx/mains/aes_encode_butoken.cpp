#include "util.hpp"
#include "aes.hpp"
#include "block.hpp"
#include <iostream>

uchar K[16] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} ;

int longueur_de_la_clef = 16 ;

uchar InitV[16] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} ;

int main(int argc, char *argv[]){
  using namespace AES ;

  if(argc < 3){
    std::cerr << "Usage ... " << argv[0] << " src dst " << '\n';
    return EXIT_FAILURE;
  }

  cout << "Clef : " ;
  crypt_util::print_key(K, longueur_de_la_clef);


  srand(time(NULL));
/*  for(int i = 0 ; i < 16 ; i ++){
    InitV[i] = rand()%256;
  }
*/
  Block InitBloc(4, 4, InitV);

  cout << "Vecteur initialisation : "<< endl;
  InitBloc.printBlock();

  Encoder encoder(K, longueur_de_la_clef);
  encoder.encode_file(argv[1], argv[2], InitBloc, false);

  return EXIT_SUCCESS ;
}
