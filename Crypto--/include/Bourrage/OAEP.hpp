#include "Bourrage/Jammer.hpp"

#include <vector>

class OAEP: public Jammer
{
public:
  OAEP();
  ~OAEP();
public:
  void jam(std::vector<uchar> &vector, size_t block_size) override ;
  void unjam(std::vector<uchar> &vector) override;
private:
  std::vector<uchar> MGF(std::vector<uchar>& seed, size_t final_length);
};
