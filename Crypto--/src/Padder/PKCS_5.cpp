#include "Padder/PKCS_5.hpp"

#include <algorithm>

PKCS_5::PKCS_5(): CipherPadder()
{

}
PKCS_5::~PKCS_5()
{

}

void PKCS_5::jam(std::vector<uchar> &vector, size_t block_size)
{
  int vector_size = vector.size();
  if(vector_size < block_size){
    uchar length = block_size - vector_size;
    vector.resize(block_size);
    if(vector_size == 0) std::fill(vector.begin(), vector.end(), block_size);
    else std::fill(vector.begin() + vector_size, vector.end(), length);
  }
}
void PKCS_5::unjam(std::vector<uchar> &vector)
{
  uchar ja = vector.back();
  if((int)ja <= vector.size()){
    vector.erase(vector.end() - (int)ja, vector.end());
  }
}
