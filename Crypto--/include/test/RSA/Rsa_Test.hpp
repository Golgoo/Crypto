#pragma once

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "Crypter/RSA/rsa.hpp"

typedef unsigned char uchar ;

class RSA_Test : public CppUnit::TestCase
{
  public:
    CPPUNIT_TEST_SUITE( RSA_Test );
      CPPUNIT_TEST( default_block_test );
      CPPUNIT_TEST( encode_test );
    CPPUNIT_TEST_SUITE_END();

  public:
    void default_block_test();
    void encode_test();
};
