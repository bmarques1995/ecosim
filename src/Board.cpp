#include "Board.hpp"
#include <cstdlib>

Board::Board(uint32_t dimension) : 
    m_Dimension(dimension)
{
    m_Samples = new uint8_t* [m_Dimension];
    for(size_t i=0; i < m_Dimension; ++i)
        m_Samples[i] = new uint8_t[m_Dimension];
}

Board::~Board()
{
    for(size_t i=0; i < m_Dimension; ++i)
        delete[] m_Samples[i];
    delete[] m_Samples;
}