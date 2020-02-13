#include "test/Bourrage/PKCS_5_test.hpp"

#include <algorithm>

void PKCS_5_Test::emptyVectorTest()
{
  std::vector<uchar> v(0);
  pkcs_5_jam.jam(v, 16);
  CPPUNIT_ASSERT_EQUAL(static_cast<int>(v.size()), 16);
  for(uchar bite : v){
    CPPUNIT_ASSERT_EQUAL(0x10, int(bite));
  }
}
void PKCS_5_Test::fullVectorTest()
{
  std::vector<uchar> v(16);
  std::fill(v.begin(), v.end(), 0x01);
  pkcs_5_jam.jam(v, 16);
  for(uchar bite : v){
    CPPUNIT_ASSERT_EQUAL(0x01, int(bite));
  }
}
void PKCS_5_Test::normalVectorTest1()
{
  std::vector<uchar> v(12);
  std::fill(v.begin(), v.end(), 0x01);
  pkcs_5_jam.jam(v, 16);
  for(auto it = v.begin() + 12 ; it < v.end() ; it ++){
    CPPUNIT_ASSERT_EQUAL(0x04, int(*it));
  }
}
void PKCS_5_Test::normalVectorTest2()
{
  std::vector<uchar> v(4);
  std::fill(v.begin(), v.end(), 0x01);
  pkcs_5_jam.jam(v, 16);
  for(auto it = v.begin() + 4 ; it < v.end() ; it ++){
    CPPUNIT_ASSERT_EQUAL(0x0C, int(*it));
  }
}
void PKCS_5_Test::toBigVectorTest()
{
  std::vector<uchar> v(32);
  std::fill(v.begin(), v.end(), 0x01);
  pkcs_5_jam.jam(v, 16);
  for(auto it = v.begin(); it < v.end() ; it ++){
    CPPUNIT_ASSERT_EQUAL(0x01, int(*it));
  }
}

void PKCS_5_Test::unjamEmpty()
{
  std::vector<uchar> v(0);
  pkcs_5_jam.jam(v, 64);
  pkcs_5_jam.unjam(v);
  CPPUNIT_ASSERT_EQUAL(0, static_cast<int>(v.size()));
}
void PKCS_5_Test::unjamFull()
{
  std::vector<uchar> v(61);
  std::fill(v.begin(), v.end(), 0xDD);
  pkcs_5_jam.jam(v, 64);
  pkcs_5_jam.unjam(v);
  CPPUNIT_ASSERT_EQUAL(61, static_cast<int>(v.size()));
  for(uchar b : v){
    CPPUNIT_ASSERT_EQUAL(0xDD, int(b));
  }
}
void PKCS_5_Test::unjamNormal()
{
  std::vector<uchar> v(52);
  std::fill(v.begin(), v.end(), 0xDD);
  pkcs_5_jam.jam(v, 64);
  pkcs_5_jam.unjam(v);
  CPPUNIT_ASSERT_EQUAL(52, static_cast<int>(v.size()));
  for(uchar b : v){
    CPPUNIT_ASSERT_EQUAL(0xDD, int(b));
  }
}
