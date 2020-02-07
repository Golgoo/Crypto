#include "aes.hpp"
#include "util.hpp"
#include <cstring>

AES::AES::AES(uchar * key, size_t key_len): _SBlock(16, 16, crypt_util::SBox), _CBlock(4, 4, crypt_util::CBox),
                                            _InvSBlock(16, 16, crypt_util::InvSBox), _InvCBlock(4, 4, crypt_util::InvCBox)
{
  //Vérifier longueur clef valide.
  //Si non valide => throw exception
  this->keyExtender = new KeyExtender(key, key_len);
  this->keyExtender->printRounds();
  //this->keyExtender->printRounds();
}

AES::AES::AES(char * key): _SBlock(16, 16, crypt_util::SBox), _CBlock(4, 4, crypt_util::CBox),
                           _InvSBlock(16, 16, crypt_util::InvSBox), _InvCBlock(4, 4, crypt_util::InvCBox)
{
  //Vérifier longueur clef valide.
  //Si non valide => throw exception
  this->keyExtender = new KeyExtender(key, strlen(key) >> 1);
  this->keyExtender->printRounds();
  //this->keyExtender->printRounds();
}

AES::AES::~AES()
{
  delete keyExtender;
}
