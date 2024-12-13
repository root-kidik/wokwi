#pragma once

#define ETL_NO_STL 1
#include <etl/vector.h>
#undef ETL_NO_STL

#include "Body.hpp"

template <uint8_t MaxTails>
class Snake
{
public:
    Snake();

    void Update();

    void Reset();
    void ChangeDirection(Direction direction);
    void Eat();

    inline const Body&                        GetHead() const;
    inline const etl::vector<Body, MaxTails>& GetTails() const;

    void SwapHeadWithTail();

private:
    void Init();

    etl::optional<etl::reference_wrapper<Body>> m_head;
    etl::vector<Body, MaxTails>                 m_tails;

    template<typename BeginIt, typename EndIt, typename NewHeadIt>
    void ChangeParents(BeginIt begin_it, EndIt end_it, NewHeadIt new_head_it);

    template<typename BeginIt, typename EndIt>
    void FollowToParent(BeginIt begin_it, EndIt end_it);
};

#include "Snake.inl"
