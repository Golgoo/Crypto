#include "Bourrage/OAEP.hpp"
#include <vector>

#include "Util/util.hpp"
#include <iostream>


int main(void)
{
    std::vector<uchar> block = {0x4B, 0x59, 0x4F, 0x54, 0x4F};
    //out::display_block(block);
    OAEP oaep ;
    oaep.jam(block, 128);
    //std::cout << "Block size : " << block.size() <<std::endl;
    //out::display_block(block);

    exit(EXIT_SUCCESS);
}
