#include <iostream>
#include "Crypter/RSA/rsa.hpp"
#include "Crypter/AES/aes.hpp"
#include "Cipher/ecb_model.hpp"
#include "Crypter/coder.hpp"
#include "Padder/Padder.hpp"
#include "Padder/PKCS_5.hpp"

#include <fstream>

int main(int argc, char*argv[])
{
  rsa::RSA_Key _key ;
  crypter::Encoder *rsa_encoder = new rsa::RSA(_key);
  crypter::Decoder *rsa_decoder = new rsa::RSA(_key);
  crypter::Coder coder(rsa_encoder, rsa_decoder);

  std::cout << "Programme 1" << std::endl;
  {
    Ecb_Model op_m (coder);
    std::ifstream in_s(argv[1]);
    std::ofstream out_s("tmp.txt");
    op_m.set_stream(&in_s, &out_s);
    op_m.encode_file();
    in_s.close();
    out_s.close();
    delete rsa_encoder ;
  }


  //std::cout << "Programme 2" << std::endl;
  {
    Ecb_Model op_m_d(coder);
    std::ofstream out_s(argv[1]);
    std::ifstream in_s("tmp.txt");
    op_m_d.set_stream(&in_s, &out_s);
    op_m_d.decode_file();
    in_s.close();
    out_s.close();
    delete rsa_decoder;
  }

  return EXIT_SUCCESS;
}
