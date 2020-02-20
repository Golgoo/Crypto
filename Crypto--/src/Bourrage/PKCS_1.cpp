#include "Bourrage/PKCS_1.hpp"

#include <algorithm>

#include <ctime>

PKCS_1::PKCS_1(): Jammer()
{
  srand(time(NULL));
}
PKCS_1::~PKCS_1()
{

}

#include <iostream>

void PKCS_1::jam(std::vector<uchar> &vector, size_t block_size)
{
  if(vector.size() <= block_size - 3){
    int ps_length = ( block_size - 3 ) - vector.size() ;
    vector.insert(vector.begin(), 0x00);
    std::vector<uchar> ps(ps_length);
    for(int i = 0 ; i < ps_length ; i ++){
      ps[i] = (rand()% (0xFF)) + 1 ;
    }
    vector.insert(vector.begin(), ps.rbegin(), ps.rend());
    vector.insert(vector.begin(), 0x02);
    vector.insert(vector.begin(), 0x00);
  }
}

void PKCS_1::unjam(std::vector<uchar> &vector)
{
  std::reverse(vector.begin(), vector.end());
  auto it = vector.back();
  if((it) == 0x00){
    vector.pop_back();
    it = vector.back();
    if(it == 0x02){
      while(vector.back() != 0x00 ){
        vector.pop_back();
      }
      vector.pop_back();
    }
  }
  std::reverse(vector.begin(), vector.end());
}
