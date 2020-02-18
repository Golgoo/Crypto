#pragma once

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "Crypter/AES/aes.hpp"

typedef unsigned char uchar ;

class Key_Extender_Test : public CppUnit::TestCase
{
  public:
    CPPUNIT_TEST_SUITE( Key_Extender_Test );
      CPPUNIT_TEST( TP_Test );
    CPPUNIT_TEST_SUITE_END();

  public :
    void TP_Test();
};
