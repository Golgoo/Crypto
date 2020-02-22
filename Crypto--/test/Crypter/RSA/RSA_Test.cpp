#include "test/RSA/Rsa_Test.hpp"

#include <cppunit/TextTestRunner.h>

#include <ctime>

/***************************************************/

int main(void)
{
  srand(time(NULL));
  CppUnit::TextTestRunner runner;

  runner.addTest( RSA_Test::suite() );

  runner.run();
}

#include <Crypter/coder.hpp>

const int nb_test = 0 ;

void RSA_Test::default_block_test()
{
  int precision = rsa::Key_Factory::createDefaultPrecision();

  rsa::Key_Factory key_factory;

  mpz_t code, code_chiffre, code_dechiffre ;
  mpz_inits(code, code_chiffre, code_dechiffre, (void*)NULL);

  mpz_set_str(code, "4b594f544f", 16);
  gmp_printf("Code clair        : %Zd\n", code);

  std::cout << "Precision : " << precision << std::endl;
  int nb_fails = 0 ;
  for(int i = 0 ; i < nb_test ;i ++){
    rsa::RSA_Key key = key_factory.createRandomKey(precision);

    /* Affichage des clefs utilisées à l'aide de la fonction gmp_printf() */
    gmp_printf("Clef publique (n) : %Zd\n", key.n);
    gmp_printf("Clef publique (e) : %Zd\n", key.e);
    gmp_printf("Clef privée (d)   : %Zd\n", key.d);

    mpz_powm(code_chiffre, code, key.e, key.n);
    gmp_printf("Code chiffré      : %Zd\n", code_chiffre);

    mpz_powm(code_dechiffre, code_chiffre, key.d, key.n);
    gmp_printf("Code déchiffré    : %Zd\n", code_dechiffre);

    CPPUNIT_ASSERT_EQUAL(0, mpz_cmp(code, code_dechiffre));
    rsa::clear_rsa_key(key);
  }

  mpz_clears(code, code_chiffre, code_dechiffre, (void*)NULL);
}

#include "Util/util.hpp"
void RSA_Test::encode_test()
{
  int precision = rsa::Key_Factory::createDefaultPrecision();

  rsa::Key_Factory key_factory;
  std::vector<uchar> block(6) ;
  //mpz_set_str(code, "4b594f544f", 16);
  block[0] = 0x4B;
  block[1] = 0x59;
  block[2] = 0x4F;
  block[3] = 0x54;
  block[5] = 0x4F;
  std::vector<uchar> copy = block;

  int nb_fails = 0 ;
  for(int i = 0 ; i < 1000 ; i ++){
    rsa::RSA_Key key = key_factory.createRandomKey(precision, "5001923");

    std::cout << "Code clair :" << std::endl;
    out::display_block(copy);

    rsa::RSA rsa_coder(key);

    rsa_coder.encode(block);
    rsa_coder.decode(block);
    rsa::clear_rsa_key(key);

    /*std::cout << "Code déchiffré :" << std::endl;
    out::display_block(block);
*/
/*    for(int i = 0 ; i < block.size() ; i++){
      if()
    }*/
    if(copy != block) {
      nb_fails++;
      break;
    }
  }
  CPPUNIT_ASSERT_EQUAL(0, nb_fails);
}










//
