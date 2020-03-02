/** Lib **/
#include <cryptom>
/********/

#include <iostream>
#include <vector>
#include <ostream>
#include <random>
#include <algorithm>
#include <iterator>
#include <functional>
#include <iomanip>
#include <fstream>

#define PKCS_1_SIZE 128

void print_usage(std::ostream &os)
{
  os << "Usage : pocito_app <src_path> " << std::endl;
  os << "<src_path> is the path to the file to encode" << std::endl;
  os << "Pocito will display the encryption in the standart output" << std::endl;
}

typedef unsigned char uchar;
int main(int argc, char *argv[])
{
  if(argc < 2){
    print_usage(std::cerr);
    return EXIT_FAILURE;
  }

  /**INITIALISATION **************************/
  std::string input_stream_string = argv[1];
  std::ifstream is(input_stream_string);
  if(!is.is_open()){
    std::cerr << "Impossible d'ouvrir le fichier : " << argv[1] << std::endl;
    return EXIT_FAILURE;
  }

  std::vector<uchar> aes_key(16);

  /** https://stackoverflow.com/questions/21516575/fill-a-vector-with-random-numbers-c **/
  std::random_device rnd_device;
  std::mt19937 mersenne_engine {rnd_device()};  // Generates random integers
  std::uniform_int_distribution<int> dist {0, 255};

  auto gen = [&dist, &mersenne_engine](){
                 return dist(mersenne_engine);
             };

  generate(begin(aes_key), end(aes_key), gen);
  /***************************************************************************************/

  /*** Chiffrement de la clef courte AES avec RSA **/
  {
    rsa::RSA_Key rsa_key = rsa::create_initialize_rsa_key();

    rsa_key.set_e("44bb1ff6c2b674798e09075609b7883497ae2e2d7b06861ef9850e26d1456280523319021062c8743544877923fe65f85111792a98e4b887de8ffd13aef18ff7f6f736c821cfdad98af051e7caaa575d30b54ed9a6ee901bb0ffc17e25d444f8bfc5922325ee2ef94bd4ee15bede2ea12eb623ad507d6b246a1f0c3cc419f155");
    rsa_key.set_n("94f28651e58a75781cfe69900174b86f855f092f09e3da2ad86b4ed964a84917e5ec60f4ee6e3adaa13962884e5cf8dae2e0d29c6168042ec9024ea11176a4ef031ac0f414918b7d13513ca1110ed80bd2532f8a7aab0314bf54fcaf621eda74263faf2a5921ffc515097a3c556bf86f2048a3c159fccfee6d916d38f7f23f21");

    crypter::Encoder *rsa_encoder = new rsa::RSA(rsa_key);
    PKCS_1 padder ;

    std::vector<uchar> aes_key_copy = aes_key ;
    padder.jam(aes_key_copy, PKCS_1_SIZE);

    rsa_encoder->encode(aes_key_copy);
    for(auto byte : aes_key_copy)
      std::cout << byte;

    delete rsa_encoder;
    rsa::clear_rsa_key(rsa_key);
  }

  /** Chiffrement du fichier source vers stdout **/
  {
    std::vector<uchar> init_v(16);
    generate(begin(init_v), end(init_v), gen);
    for(auto byte : init_v)
      std::cout << byte;

    crypter::Encoder *aes_encoder = new aes::AES(aes_key);
    CipherPadder * padder = new PKCS_5;

    //Nous n'essayons pas de déchiffrer ( 2ème argument <=> NULL)
    crypter::Coder coder(aes_encoder, NULL);
    Cbc_Model block_ciphering(coder, padder);
    block_ciphering.set_input_stream(&is);
    block_ciphering.encode_file();

    delete padder;
    delete aes_encoder;
  }

  is.close();
  return EXIT_SUCCESS;
}
