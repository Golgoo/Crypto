#pragma once

#include "Padder/CipherPadder.hpp"

typedef unsigned char uchar ;

class PKCS_5 : public CipherPadder
{
public:
  PKCS_5();
  ~PKCS_5();
  void jam(std::vector<uchar> &vector, size_t block_size) override;
  void unjam(std::vector<uchar> &vector) override;
};
