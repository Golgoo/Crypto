#include <MiniMimeMailer.hpp>

#include <string.h>
#include <iterator>
#include <cstdio>
#include <sstream>

Mailer::Mailer(std::string email_path)
{
  this->email_path = email_path;
  this->fxx =  ifstream(email_path) ;
  if(! this->fxx){
    std::cerr << "Unable to read : \"" << email_path << '\"' << std::endl ;
  }
}

Mailer::~Mailer()
{
  this->fxx.close();
}

std::string Mailer::readCorpse()
{
  std::string corpse;
  if(this->fxx.is_open()){
    char tmp [1024] ;
    do{
      this->fxx.getline(tmp, 1024);
      //std::cout << "s - " << strlen(tmp) << " : " << tmp << std::endl;
    }while((!this->fxx.eof()) && (strchr(tmp,':')));
    while(true){
      this->fxx.getline(tmp, 1024);
      if(this->fxx.eof()) break;
      //std::cout << "s - " << strlen(tmp) << " : " << tmp << std::endl;
      corpse += tmp ;
      corpse += "\n";
    }
  }else{
    std::cerr << "Cannot read corpse ( file : \"" << email_path << "\" wasn't readable )" << '\n' << std::endl;
  }

  return corpse;
}

void copy_headers(FILE* src, FILE* dst)
{
  char *buffer = (char*)malloc(sizeof(char)*1024);
  size_t size  ;
  int returned ;
  do{
    returned = getline(&buffer, &size, src);
    fprintf(dst,"%s", buffer);
  }while(returned!=EOF && strchr(buffer, ':')!=NULL);
  free(buffer);
}

void copy_rest(FILE*src, FILE*dst)
{
  char c ;
  while((c = fgetc(src)) != EOF){
    fprintf(dst,"%c", c);
  }
}

void Mailer::addHeader(string name, string value)
{
    FILE * file = fopen(this->email_path.c_str(),"r+");
    FILE * tmp = fopen("tmp.tmp.tmp","w+");
    rewind(file);
    copy_headers(file, tmp);
    fseek(tmp, -1, SEEK_CUR);
    fprintf(tmp, "%s: %s\n", name.c_str(), value.c_str());
    fprintf(tmp,"\n");
    copy_rest(file, tmp);
    fseek(tmp, 0, SEEK_SET);
    fseek(file, 0, SEEK_SET);
    copy_rest(tmp, file);
    fclose(tmp);
    fclose(file);
}

string Mailer::getHeaderValue(string field_name)
{
  this->fxx.close();
  this->fxx =  ifstream(this->email_path) ;

  char tmp [1024] ;
  std::string str ;
  do{
    this->fxx.getline(tmp, 1024);
    //std::cout << "s - " << strlen(tmp) << " : " << tmp << std::endl;
    if(strchr(tmp,':')){
      std::string line(tmp);
      std::istringstream iss(line);
      if (std::getline(iss, str, ':')){
        if(str == field_name){
          std::getline(iss, str);
          str = str.substr(1, str.size() - 1);
          return str ;
        }
      }
    }
  }while((!this->fxx.eof()) && (strlen(tmp) != 0));

  return "";
}
