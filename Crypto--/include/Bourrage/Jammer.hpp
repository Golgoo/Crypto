#pragma once

#include <vector>


typedef unsigned char uchar ;

class Jammer
{
public:
  Jammer();
  virtual ~Jammer() = 0;
  virtual void jam(std::vector<uchar> &vector, size_t block_size) = 0;
  virtual void unjam(std::vector<uchar> &vector) = 0 ;
};
