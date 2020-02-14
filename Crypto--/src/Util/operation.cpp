#include "Util/operation.hpp"


void operation::XOR(std::vector<uchar>& dst, std::vector<uchar>& other)
{
  if(dst.size()==other.size()){
    for(int i = 0 ; i < dst.size() ; i ++){
      dst[i] = dst[i]^other[i];
    }
  }
}
