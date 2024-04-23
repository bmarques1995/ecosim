#pragma once

#include <cstdint>
#include "Plant.hpp"
#include "Carnivore.hpp"
#include "Herbivore.hpp"
#include <vector>
#include <unordered_map>
#include <memory>

class Board
{
public:
    Board(uint32_t dimension, uint32_t numOfPlants, uint32_t numOfHerbivores, uint32_t numOfCarnivores);
    ~Board();

    const std::vector<std::vector<BoardSerializer>>& Serialize();

    void Advance();

private:
    uint16_t SelectRandomPos();

    void CreatePlant();
    void CreateHerbivore();
    void CreateCarnivore();
    void AdvanceID();

    uint32_t m_Stride;
    uint32_t m_CurrentCycle;
    uint32_t* m_Samples;
    uint32_t m_CurrentID;
    std::vector<std::vector<BoardSerializer>> m_SerializedEntities;

    std::unordered_map<uint32_t, std::shared_ptr<Plant>> m_PlantsMap;
    std::unordered_map<uint32_t, std::shared_ptr<Herbivore>> m_HerbivoresMap;
    std::unordered_map<uint32_t, std::shared_ptr<Carnivore>> m_CarnivoresMap;
};