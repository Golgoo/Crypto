#pragma once

#include "Bourrage/Jammer.hpp"

typedef unsigned char uchar ;

class PKCS_1 : public Jammer
{
public:
  PKCS_1();
  ~PKCS_1();
  void jam(std::vector<uchar> &vector, size_t block_size) override;
  void unjam(std::vector<uchar> &vector) override;
};
