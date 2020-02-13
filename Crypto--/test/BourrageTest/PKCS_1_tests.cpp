#include "test/Bourrage/PKCS_1_test.hpp"

#include <algorithm>

void PKCS_1_Test::emptyVectorTest()
{
  std::vector<uchar> v(0);
  pkcs_1_jam.jam(v, 64);
  CPPUNIT_ASSERT_EQUAL(64, static_cast<int>(v.size()));
  CPPUNIT_ASSERT_EQUAL(0x00, int(v[0]));
  CPPUNIT_ASSERT_EQUAL(0x02, int(v[1]));
  for(auto it = v.begin() + 2 ; it < v.end() - 1 ; it ++){
    CPPUNIT_ASSERT((*it) != 0x00);
  }
  CPPUNIT_ASSERT_EQUAL(0x00, int(*v.end()));
}
void PKCS_1_Test::fullVectorTest()
{
  std::vector<uchar> v(125);
  std::fill(v.begin(), v.end(), 0xFF);
  pkcs_1_jam.jam(v, 128);
  CPPUNIT_ASSERT_EQUAL(0x00, int(v[0]));
  CPPUNIT_ASSERT_EQUAL(0x02, int(v[1]));
  CPPUNIT_ASSERT_EQUAL(0x00, int(v[2]));
  for(auto it = v.begin() + 3 ; it < v.end() ; it ++){
    CPPUNIT_ASSERT_EQUAL(0xFF, int(*it));
  }
}
void PKCS_1_Test::normalVectorTest()
{
  std::vector<uchar> v(112);
  std::fill(v.begin(), v.end(), 0xFF);
  pkcs_1_jam.jam(v, 128);
  CPPUNIT_ASSERT_EQUAL(0x00, int(v[0]));
  CPPUNIT_ASSERT_EQUAL(0x02, int(v[1]));
  for(int i = 2 ; i < 128 - 113 ; i ++){
    CPPUNIT_ASSERT(v[i] != 0x00);
  }
  CPPUNIT_ASSERT_EQUAL(0x00, int(v[128-113]));
  for(int i = 128 - 112 ; i < 128 ; i ++){
    CPPUNIT_ASSERT_EQUAL(0xFF, int(v[i]));
  }
}

void PKCS_1_Test::toBigVectorTest()
{
  std::vector<uchar> v(126);
  std::fill(v.begin(), v.end(), 0xFF);
  pkcs_1_jam.jam(v, 128);
  CPPUNIT_ASSERT_EQUAL(static_cast<int>(v.size()), 126);
  for(auto it = v.begin(); it < v.end() ; it ++){
    CPPUNIT_ASSERT_EQUAL(0xFF, int(*it));
  }
}

void PKCS_1_Test::unjamEmpty()
{
  std::vector<uchar> v(0);
  pkcs_1_jam.jam(v, 64);
  pkcs_1_jam.unjam(v);
  CPPUNIT_ASSERT_EQUAL(0, static_cast<int>(v.size()));
}
void PKCS_1_Test::unjamFull()
{
  std::vector<uchar> v(61);
  std::fill(v.begin(), v.end(), 0xDD);
  pkcs_1_jam.jam(v, 64);
  pkcs_1_jam.unjam(v);
  CPPUNIT_ASSERT_EQUAL(61, static_cast<int>(v.size()));
  for(uchar b : v){
    CPPUNIT_ASSERT_EQUAL(0xDD, int(b));
  }
}
void PKCS_1_Test::unjamNormal()
{
  std::vector<uchar> v(52);
  std::fill(v.begin(), v.end(), 0xDD);
  pkcs_1_jam.jam(v, 64);
  pkcs_1_jam.unjam(v);
  CPPUNIT_ASSERT_EQUAL(52, static_cast<int>(v.size()));
  for(uchar b : v){
    CPPUNIT_ASSERT_EQUAL(0xDD, int(b));
  }
}
