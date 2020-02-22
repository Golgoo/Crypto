#include "Padder/stub_jam.hpp"

StubJammer::StubJammer(): Jammer()
{

}
StubJammer::~StubJammer()
{

}
void StubJammer::jam(std::vector<uchar> &vector, size_t block_size)
{
  int vector_size = vector.size();
  vector.resize(block_size);
  vector[vector_size] = 0x01 ;
  std::fill(vector.begin() + vector_size + 1, vector.end(), 0x00);
}

void StubJammer::unjam(std::vector<uchar> &vector)
{
  if(vector.back() == 0x00){
    for(auto it = vector.end() - 1 ; it >= vector.begin() ; it--){
      vector.pop_back();
      if(*it == 0x01) break;
    }
  }

}
