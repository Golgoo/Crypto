#include "test/AES/Key_Extender_test.hpp"
#include "test/AES/AES_Encoder_test.hpp"

#include <cppunit/TextTestRunner.h>

/***************************************************/

int main(void)
{
  CppUnit::TextTestRunner runner;

  runner.addTest( Key_Extender_Test::suite() );
  runner.addTest( AES_Encoder_Test::suite() );

  runner.run();
}
