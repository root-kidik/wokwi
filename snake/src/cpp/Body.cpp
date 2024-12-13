#include "Body.hpp"

Body::Body(Vector2i spawn_position, etl::optional<etl::reference_wrapper<Body>> parent) : m_position{spawn_position}, m_parent{parent}
{
    if (m_parent)
        m_previous_parent_position = m_parent.value().get().GetPosition();
    else
        m_is_head = true;
}


void Body::SetParent(Body& parent)
{
    m_parent = etl::ref<Body>(parent);
    m_previous_parent_position = m_parent.value().get().GetPosition();
    m_is_head = false;
}

void Body::UnsetParent()
{
    m_parent = etl::nullopt;
    m_is_head = true;
    m_direction = m_previous_self_position - m_position;
}

void Body::ChangeDirection(Direction direction)
{
    switch (direction)
    {
        case Direction::Left:
        {
            if (m_direction == kUp)
                m_direction = kLeft;
            else if (m_direction == kLeft)
                m_direction = kDown;
            else if (m_direction == kDown)
                m_direction = kRight;
            else
                m_direction = kUp;

            break;
        }
        case Direction::Right:
        {
            if (m_direction == kUp)
                m_direction = kRight;
            else if (m_direction == kRight)
                m_direction = kDown;
            else if (m_direction == kDown)
                m_direction = kLeft;
            else
                m_direction = kUp;

            break;
        }
        default:
        {
            // "You DUMB!"
            // std::abort();
        }
    }
}

void Body::MoveForward()
{
    m_previous_self_position = m_position; 
    m_position += m_direction;
}

void Body::FollowToParent()
{
    assert(m_parent);

    m_previous_self_position = m_position;
    m_position = m_previous_parent_position;
    m_previous_parent_position = m_parent.value().get().GetPosition();
};
