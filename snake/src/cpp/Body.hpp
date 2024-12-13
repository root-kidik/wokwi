#pragma once

#define ETL_NO_STL 1
#include <etl/functional.h>
#include <etl/optional.h>
#undef ETL_NO_STL

#include "Vector2.hpp"

#include "Direction.hpp"

/*
Sorry, but no dynimac_cast, no new, can not make best code
Just crash your arduino and buy stm32 4$:)

class Head : virtual public Body
{...}

class Tail : virtual public Body
{...}

class HeadTail : public Head, public Tail
{...}
*/
class Body
{
public:
    Body(Vector2i spawn_position, etl::optional<etl::reference_wrapper<Body>> parent = etl::nullopt);

    inline Vector2i GetPosition() const;
    inline bool IsHead() const;

    void SetParent(Body& parent);
    void UnsetParent();

private:
    Vector2i m_position;
    bool m_is_head{};

// Head
public:
    void ChangeDirection(Direction direction);
    void MoveForward();

private:
    Vector2i m_direction{kUp};

// Tail
public:
    void FollowToParent();

private:
    etl::optional<etl::reference_wrapper<Body>> m_parent;
    Vector2i m_previous_parent_position;
    Vector2i m_previous_self_position;
};

#include "Body.inl"