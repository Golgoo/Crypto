

#include "Crypter/AES/aes.hpp"

using namespace aes;

#define NDEBUG
#include <cassert>

void AES::encode(std::vector<uchar>& block)
{
  assert(block.size() == 16);

}

void AES::decode(std::vector<uchar>& block)
{
  assert(block.size() == 16);
}
