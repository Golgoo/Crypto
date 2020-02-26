#include "test/AES/AES_Encoder_test.hpp"


#include <vector>

#include "Crypter/AES/aes.hpp"

#include "Util/util.hpp"

void AES_Encoder_Test::TP_Test()
{
  std::vector<uchar> block = {
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00
  };
  std::vector<uchar> key = {
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00
  };
  std::vector<uchar> expected = {
    0x66, 0xE9, 0x4B, 0xD4,
    0xEF, 0x8A, 0x2C, 0x3B,
    0x88, 0x4C, 0xFA, 0x59,
    0xCA, 0x34, 0x2B, 0x2E
  };
  aes::AES encoder(key);

  encoder.encode(block);

  CPPUNIT_ASSERT(expected == block);
}

#include "Cipher/cbc_model.hpp"
#include "Padder/PKCS_5.hpp"
#include "Padder/PKCS_5.hpp"
#include "Crypter/AES/aes.hpp"
#include "Crypter/coder.hpp"

void AES_Encoder_Test::Butokuden()
{
  std::vector<uchar> key = {
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00
  };
  crypter::Encoder * encoder = new aes::AES(key);
  crypter::Decoder * decoder = new aes::AES(key);
  crypter::Coder coder(encoder, decoder);

  Padder * jammer = new PKCS_5 ;
  std::ifstream src_stream("butokuden.jpg");
  std::ofstream dst_stream("cbc-secret.jpg");
  Cbc_Model cipher(coder, jammer);
  cipher.set_stream(&src_stream, &dst_stream);
  cipher.encode_file();

  src_stream.close();
  dst_stream.close();
  delete encoder;
  delete decoder;
  delete jammer;
}
