#ifndef __AES_HPP__
#define __AES_HPP__

#include "diversification.hpp"
#include <cstdlib>


/**
 *    TODO : Identifier les fonction commune entre Encoder / Decoder
 *            => Les factoriser à l'abstraction
 *        -> Pq pas utiliser ptr sur fonction pour inv_MixColumn, etc.. ( si vraiment besoin pour éviter de dupliquer bêtement )
 */

namespace AES{
  class AES{
  public:
    AES(uchar *key, size_t key_len);
    AES(char * key);
    void transposeRounds();
    ~AES();
  protected:
    KeyExtender * keyExtender ;
  };
  class Encoder : public AES{
  public :
    Encoder(uchar * key, size_t key_len);
    Encoder(char * key);
    void encode(uchar * current_state);
    void encode_file(char * src_filename, char * dst_filename);
  };
  class Decoder : public AES{
  public:
    Decoder(uchar * key, size_t key_len);
    Decoder(char * key);
    void decode(uchar * current_state);
    void decode_file(char * src_filename, char *dst_filename);
  };
};

#endif
