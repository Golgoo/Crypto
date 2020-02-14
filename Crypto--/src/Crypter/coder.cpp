#include "Crypter/coder.hpp"

using namespace crypter;


Decoder::Decoder()
{

}

Decoder::~Decoder()
{

}


Encoder::Encoder()
{

}


Encoder::~Encoder()
{

}

Coder::Coder(Encoder *encoder, Decoder *decoder): _encoder(encoder), _decoder(decoder)
{

}
