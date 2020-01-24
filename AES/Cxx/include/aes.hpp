#ifndef __AES_HPP__
#define __AES_HPP__

#include "diversification.hpp"

/**
 * TODO : Construction + initialisation abstraite +
 *        Utiliser le key extender à la construction / le libérer à la destruction
 *            => Même utilisation pour chaque tour de boucle
 *            + Reverse extendedKey() pour chaque bloc (inverser à chaque encodage / decodage change la clef).
 *        Identifier les fonction commune entre Encoder / Decoder
 *            => Les factoriser à l'abstraction
 *        -> Pq pas utiliser ptr sur fonction pour inv_MixColumn, etc.. ( si vraiment besoin pour éviter de dupliquer bêtement )
 */

namespace AES{
  class Encoder{
    public :
      Encoder();
      ~Encoder();
      uchar * encode(uchar *content, char *key);
      uchar * encode(uchar * content, uchar * key, size_t len);
    private :
      uchar *current_state;
      size_t key_len ;
      KeyExtender * keyExtender ;
      void encode_algo();
  };
  class Decoder{
  public:
    uchar * decode(uchar * content, char *key);
    uchar * decode(uchar * content, uchar *key, size_t len);
    Decoder();
    ~Decoder();
  private:
    uchar *current_state;
    size_t key_len ;
    KeyExtender * keyExtender ;
    void decode_algo();
  };
}

#endif
