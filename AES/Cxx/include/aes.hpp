#ifndef __AES_HPP__
#define __AES_HPP__

#include "diversification.hpp"
#include "block.hpp"
#include "util.hpp"
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
    ~AES();
  protected:
    KeyExtender * keyExtender ;
    Block _SBlock;
    Block _CBlock;
    Block _InvCBlock;
    Block _InvSBlock;
  };
  class Encoder : public AES{
  public :
    Encoder(uchar * key, size_t key_len);
    Encoder(char * key);
    void encode(Block& current_state);
    void encode_file(char * src_filename, char * dst_filename, Block &initBlock, bool concat_init_vector );
  };
  class Decoder : public AES{
  public:
    Decoder(uchar * key, size_t key_len);
    Decoder(char * key);
    void decode(Block& current_state);
    void decode_file(char * src_filename, char *dst_filename);
  };
};

#endif
