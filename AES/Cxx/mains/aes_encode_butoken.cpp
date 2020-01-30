#include "util.hpp"
#include "aes.hpp"
#include <iostream>

uchar K[16] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} ;

int longueur_de_la_clef = 16 ;

int main(int argc, char *argv[]){
  using namespace AES ;

  if(argc < 3){
    std::cerr << "Usage ... " << argv[0] << " src dst " << '\n';
    return EXIT_FAILURE;
  }

  Encoder encoder(K, longueur_de_la_clef);
  cout << "Clef : " ;
  crypt_util::print_key(K, longueur_de_la_clef);

  encoder.encode_file(argv[1], argv[2]);

  return EXIT_SUCCESS ;
}
