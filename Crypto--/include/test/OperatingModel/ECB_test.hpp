#pragma once

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "OperatingModel/ecb_model.hpp"

typedef unsigned char uchar ;

class ECB_Test : public CppUnit::TestCase
{
  public:
    CPPUNIT_TEST_SUITE( ECB_Test );
      CPPUNIT_TEST( emptyFileTest );
      CPPUNIT_TEST( sixteenBitsTest );
      CPPUNIT_TEST( standartTest );
    CPPUNIT_TEST_SUITE_END();

  public :
    void emptyFileTest();
    void sixteenBitsTest();
    void standartTest();
};
