#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <iomanip>

#include "util.hpp"
#include "diversification.hpp"
#include "aes.hpp"

int main(int argc, char * argv[]){
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

  using namespace AES ;

  KeyExtender keyExtender(argv[1], longueur_de_la_clef);
  keyExtender.printRounds();

  return EXIT_SUCCESS;
}
