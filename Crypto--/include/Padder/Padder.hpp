#pragma once

#include <vector>


typedef unsigned char uchar ;

class Padder
{
public:
  Padder();
  virtual ~Padder() = 0;
  virtual void jam(std::vector<uchar> &vector, size_t block_size) = 0;
  virtual void unjam(std::vector<uchar> &vector) = 0 ;
};
