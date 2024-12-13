template <uint8_t MaxApples, uint8_t MaxTails>
AppleSpawner<MaxApples, MaxTails>::AppleSpawner(const Snake<MaxTails>& snake) : m_snake{snake}
{
}

template <uint8_t MaxApples, uint8_t MaxTails>
void AppleSpawner<MaxApples, MaxTails>::SpawnApple()
{
    if (m_apples.size() == MaxApples) return;

    while (true)
    {
        Vector2i spawn_position{rand() % 8, rand() % 8};
        bool is_spawnable_position{true};

        for (auto tail : m_snake.GetTails())
            if (spawn_position == tail.GetPosition())
            {
                is_spawnable_position = false;
                break;
            }

        if (!is_spawnable_position)
            continue;

        if (m_apples.size() > 1)
            m_apples.erase(*m_apples.begin());
        
        m_apples.insert(spawn_position);
        return;
    }
}

template <uint8_t MaxApples, uint8_t MaxTails>
void AppleSpawner<MaxApples, MaxTails>::EatApple(
    etl::iunordered_set<Vector2i, etl::hash<Vector2i>, etl::equal_to<Vector2i>>::const_iterator it)
{
    if (it != m_apples.end())
        m_apples.erase(it);
}

template <uint8_t MaxApples, uint8_t MaxTails>
inline const etl::unordered_set<Vector2i, MaxApples>& AppleSpawner<MaxApples, MaxTails>::GetApplePositions() const
{
    return m_apples;
}

template <uint8_t MaxApples, uint8_t MaxTails>
void AppleSpawner<MaxApples, MaxTails>::Reset()
{
    m_apples.clear();
}