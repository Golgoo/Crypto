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

#include "OperatingModel/cbc_model.hpp"
#include "Bourrage/PKCS_5.hpp"
#include "Bourrage/PKCS_5.hpp"
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

  Jammer * jammer = new PKCS_5 ;
  std::string src_path = "butokuden.jpg";
  Cbc_Model cipher(src_path, coder, jammer);

  std::string dst_path = "cbc-secret.jpg";
  cipher.encode_file(dst_path);

  delete encoder;
  delete decoder;
  delete jammer;
}
