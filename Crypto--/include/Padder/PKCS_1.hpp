#pragma once

#include "Padder/Padder.hpp"

typedef unsigned char uchar ;

class PKCS_1 : public Padder
{
public:
  PKCS_1();
  ~PKCS_1();
public:
  void jam(std::vector<uchar> &vector, size_t block_size) override;
  void unjam(std::vector<uchar> &vector) override;
};
