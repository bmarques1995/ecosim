#include <cstdint>
#include "Entity.hpp"

class Board
{
public:
    Board(uint32_t dimension);
    ~Board();
private:
    uint32_t m_Dimension;
    uint8_t** m_Samples;
};