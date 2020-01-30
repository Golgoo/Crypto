#include "aes.hpp"
#include "util.hpp"
#include <cstring>

AES::AES::AES(uchar * key, size_t key_len)
{
  //Vérifier longueur clef valide.
  //Si non valide => throw exception
  this->keyExtender = new KeyExtender(key, key_len);
  this->keyExtender->printRounds();
  transposeRounds();
  //this->keyExtender->printRounds();
}

AES::AES::AES(char * key)
{
  //Vérifier longueur clef valide.
  //Si non valide => throw exception
  this->keyExtender = new KeyExtender(key, strlen(key) >> 1);
  this->keyExtender->printRounds();
  transposeRounds();
  //this->keyExtender->printRounds();
}

void AES::AES::transposeRounds()
{
  uchar * tmp_rounds = this->keyExtender->getExtendedKey();
  for(int i = 0 ; i < this->keyExtender->getNbRound() ; i ++){
    crypt_util::reverse(tmp_rounds, 4, 4);
    tmp_rounds += 16 ;
  }
}

AES::AES::~AES()
{
  delete keyExtender;
}
