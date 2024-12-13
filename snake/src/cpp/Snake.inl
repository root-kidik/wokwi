#include "Snake.hpp"
template <uint8_t MaxTails>
Snake<MaxTails>::Snake() 
{
    Init();
}

template <uint8_t MaxTails>
void Snake<MaxTails>::Reset()
{
    Init();
}

template <uint8_t MaxTails>
void Snake<MaxTails>::ChangeDirection(Direction direction)
{
    m_head.value().get().ChangeDirection(direction);
}

template <uint8_t MaxTails>
void Snake<MaxTails>::Update()
{
    m_head.value().get().MoveForward();

    if (m_tails.front().IsHead())
        FollowToParent(m_tails.begin(), m_tails.end());
    else
        FollowToParent(m_tails.rbegin(), m_tails.rend());
}

template <uint8_t MaxTails>
void Snake<MaxTails>::Eat()
{
    auto& last_tail{m_tails.back()};
    auto  last_tail_pos{last_tail.GetPosition()};
    m_tails.emplace_back(Vector2i{last_tail_pos.x - 1, last_tail_pos.y}, etl::ref<Body>(last_tail));
}

template <uint8_t MaxTails>
inline const Body& Snake<MaxTails>::GetHead() const
{
    return m_head.value().get();
}

template <uint8_t MaxTails>
inline const etl::vector<Body, MaxTails>& Snake<MaxTails>::GetTails() const
{
    return m_tails;
}

template <uint8_t MaxTails>
void Snake<MaxTails>::SwapHeadWithTail()
{
    assert(m_tails.size() >= 2);

    if (m_tails.front().IsHead())
        ChangeParents(m_tails.begin(), m_tails.end(), m_tails.rbegin());
    else
        ChangeParents(m_tails.rbegin(), m_tails.rend(), m_tails.begin());
}

template <uint8_t MaxTails>
void Snake<MaxTails>::Init()
{
    m_tails.clear();
    m_tails.emplace_back(Vector2i{0, 6});
    m_head = etl::ref<Body>(*m_tails.begin());
    m_tails.emplace_back(Vector2i{0, 7}, m_head.value());
}

template <uint8_t MaxTails>
template <typename BeginIt, typename EndIt, typename NewHeadIt>
inline void Snake<MaxTails>::ChangeParents(BeginIt begin_it, EndIt end_it, NewHeadIt new_head_it)
{
    for (; begin_it != end_it - 1; begin_it++)
        begin_it->SetParent(*(begin_it + 1));
    m_head = etl::ref<Body>(*new_head_it);
    m_head.value().get().UnsetParent();
}

template <uint8_t MaxTails>
template <typename BeginIt, typename EndIt>
inline void Snake<MaxTails>::FollowToParent(BeginIt begin_it, EndIt end_it)
{
    for (; begin_it != end_it; begin_it++)
        if (!begin_it->IsHead())
            begin_it->FollowToParent();
}
