#ifndef __MINI_MIME_MAILER_H__
#define __MINI_MIME_MAILER_H__

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstddef>

using namespace std ;

class Mailer
{
  public :
    Mailer(string email_path);
    ~Mailer();
  private :
    ifstream fxx ;
    string email_path ;
  public :
    std::string readCorpse();
    string getFieldValue(string field_name);
    void addHeader(string name, string value);
    string getHeaderValue(string field_name);
};


#endif
