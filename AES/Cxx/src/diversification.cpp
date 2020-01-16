#include "diversification.hpp"

using namespace AES ;

KeyExtender::KeyExtender(uchar * key, size_t len): key(key), key_len(len)
{

}


uchar * KeyExtender::getExtendedKey()
{
  return this->W ;
}

size_t KeyExtender::getExtendedKeyLen()
{
  return this->extended_key_len ;
}
