#pragma once

#include "Bourrage/Jammer.hpp"

typedef unsigned char uchar ;

class PKCS_5 : public Jammer
{
public:
  PKCS_5();
  ~PKCS_5();
  void jam(std::vector<uchar> &vector, size_t block_size) override;
  void unjam(std::vector<uchar> &vector) override;
};
