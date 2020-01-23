#include "test/test_util.hpp"

#include <cppunit/TextTestRunner.h>

#include <iostream>

/***************************************************/

int main(void)
{
  CppUnit::TextTestRunner runner;

  runner.addTest( testCryptUtil::suite() );

  runner.run();
}
