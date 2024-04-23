#include "Board.hpp"
#include <cstdlib>
#include <iostream>
#include <random>

Board::Board(uint32_t dimension, uint32_t numOfPlants, uint32_t numOfHerbivores, uint32_t numOfCarnivores) : 
    m_Stride(dimension), m_CurrentCycle(0)
{
    m_CurrentID = 1;
    std::cout << "\n\n" << numOfPlants << " " << numOfHerbivores << " " << numOfCarnivores<< "\n\n\n";
    size_t squareDimension = m_Stride * m_Stride;
    m_Samples = new uint32_t[squareDimension];
    for(size_t i = 0; i < squareDimension; ++i)
        m_Samples[i] = 0;

    m_SerializedEntities.assign(dimension, std::vector<BoardSerializer>(dimension, { empty, 0, 0}));
    for(size_t i=0; i < numOfPlants; ++i)
        CreatePlant();
    for(size_t i=0; i < numOfHerbivores; ++i)
        CreateHerbivore();
    for(size_t i=0; i < numOfCarnivores; ++i)
        CreateCarnivore();
}

const std::vector<std::vector<BoardSerializer>>& Board::Serialize()
{
    return m_SerializedEntities;
}

Board::~Board()
{
    delete[] m_Samples;
}

uint16_t Board::SelectRandomPos()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> dis(0, (m_Stride - 1));
    return dis(gen);
}

void Board::CreatePlant()
{
    
    pos_t startPos = {SelectRandomPos(), SelectRandomPos()};
    while(m_Samples[startPos.i * m_Stride + startPos.j] != 0)
        startPos = {SelectRandomPos(), SelectRandomPos()};
    std::shared_ptr<Plant> p;
    p.reset(new Plant(startPos, m_CurrentID));
    m_PlantsMap[m_CurrentID] = p;
    uint32_t entityID = m_CurrentID;
    AdvanceID();
    m_SerializedEntities[startPos.i][startPos.j] = m_PlantsMap[entityID]->Serialize();
    m_Samples[startPos.i * m_Stride + startPos.j] = entityID;
}

void Board::CreateHerbivore()
{
    pos_t startPos = {SelectRandomPos(), SelectRandomPos()};
    while(m_Samples[startPos.i * m_Stride + startPos.j] != 0)
        startPos = {SelectRandomPos(), SelectRandomPos()};
    std::shared_ptr<Herbivore> h;
    h.reset(new Herbivore(startPos, m_CurrentID));
    m_HerbivoresMap[m_CurrentID] = h;
    uint32_t entityID = m_CurrentID;
    AdvanceID();
    m_SerializedEntities[startPos.i][startPos.j] = m_HerbivoresMap[entityID]->Serialize();
    m_Samples[startPos.i * m_Stride + startPos.j] = entityID;
}

void Board::CreateCarnivore()
{
    pos_t startPos = {SelectRandomPos(), SelectRandomPos()};
    while(m_Samples[startPos.i * m_Stride + startPos.j] != 0)
        startPos = {SelectRandomPos(), SelectRandomPos()};
    std::shared_ptr<Carnivore> c;
    c.reset(new Carnivore(startPos, m_CurrentID));
    //problema
    m_CarnivoresMap[m_CurrentID] = c;
    uint32_t entityID = m_CurrentID;
    AdvanceID();
    m_SerializedEntities[startPos.i][startPos.j] = m_CarnivoresMap[entityID]->Serialize();
    m_Samples[startPos.i * m_Stride + startPos.j] = entityID;
}

//docker compose up

void Board::AdvanceID()
{
    m_CurrentID %= 361;
    m_CurrentID++;
}

void Board::Advance()
{
    for (auto r : m_PlantsMap)
    {
        r.second->AdvanceAge();
        m_SerializedEntities[r.second->GetCurrentPos().i][r.second->GetCurrentPos().j] = r.second->Serialize();
    }
    for (auto r : m_HerbivoresMap)
    {
        r.second->AdvanceAge();
        m_SerializedEntities[r.second->GetCurrentPos().i][r.second->GetCurrentPos().j] = r.second->Serialize();
    }
    for (auto r : m_CarnivoresMap)
    {
        r.second->AdvanceAge();
        m_SerializedEntities[r.second->GetCurrentPos().i][r.second->GetCurrentPos().j] = r.second->Serialize();
    }
}
