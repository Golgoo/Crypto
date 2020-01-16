#include "util.hpp"

int main(void){
  unsigned char key [] = {0x22, 0xAB} ;
  crypt_util::print_key(crypt_util::Rcon, 10);
}
