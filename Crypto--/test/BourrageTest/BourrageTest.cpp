#include "test/Bourrage/PKCS_5_test.hpp"
#include "test/Bourrage/PKCS_1_test.hpp"

#include <cppunit/TextTestRunner.h>

#include <ctime>

/***************************************************/

int main(void)
{
  srand(time(NULL));
  CppUnit::TextTestRunner runner;

  runner.addTest( PKCS_5_Test::suite() );
  runner.addTest( PKCS_1_Test::suite() );

  runner.run();
}
