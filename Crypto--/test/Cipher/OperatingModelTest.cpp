#include "test/Cipher/ECB_test.hpp"

#include <cppunit/TextTestRunner.h>

#include <ctime>

/***************************************************/

int main(void)
{
  srand(time(NULL));
  CppUnit::TextTestRunner runner;

  runner.addTest( ECB_Test::suite() );

  runner.run();
}
