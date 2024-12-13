#pragma once

#define ETL_NO_STL 1
#include <etl/unordered_set.h>
#undef ETL_NO_STL

#include "Snake.hpp"

template <uint8_t MaxApples, uint8_t MaxTails>
class AppleSpawner
{
public:
    AppleSpawner(const Snake<MaxTails>& snake);

    void SpawnApple();
    void EatApple(etl::iunordered_set<Vector2i, etl::hash<Vector2i>, etl::equal_to<Vector2i>>::const_iterator it);

    inline const etl::unordered_set<Vector2i, MaxApples>& GetApplePositions() const;

    void Reset();

private:
    etl::unordered_set<Vector2i, MaxApples> m_apples;
    const Snake<MaxTails>&                  m_snake;
};

#include "AppleSpawner.inl"