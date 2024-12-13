template <uint8_t GridSize>
Game<GridSize>::Game(const IClock& clock) : m_apple_spawner{m_snake}, m_clock{clock}
{
}

template <uint8_t GridSize>
void Game<GridSize>::Update()
{
    HandleInput();

    m_snake.Update();

    if (IsGameOver())
        RestartGame();

    HandleAppleCollision();

    static std::size_t i{1};
    if (i++ % m_apple_spawn_period == 0)
        m_apple_spawner.SpawnApple();

    if (i % m_apple_spawn_period == 0)
        m_snake.SwapHeadWithTail();
}

template <uint8_t GridSize>
void Game<GridSize>::OnEvent(Direction direction)
{
    if (direction == Direction::Left)
        m_is_rotate_left_pressed = true;
    else if (direction == Direction::Right)
        m_is_rotate_right_pressed = true;
}

template <uint8_t GridSize>
inline const Snake<Game<GridSize>::MaxTails>& Game<GridSize>::GetSnake() const
{
    return m_snake;
}

template <uint8_t GridSize>
inline const AppleSpawner<Game<GridSize>::MaxApples, Game<GridSize>::MaxTails>& Game<GridSize>::GetAppleSpawner() const
{
    return m_apple_spawner;
}

template <uint8_t GridSize>
void Game<GridSize>::HandleInput()
{
    HandleButton(m_is_rotate_left_pressed, Direction::Left);
    HandleButton(m_is_rotate_right_pressed, Direction::Right);
}

template <uint8_t GridSize>
void Game<GridSize>::HandleButton(volatile bool& event_flag, Direction direction)
{
    if (event_flag && m_clock.GetTick() - m_last_rotate_tick > m_turn_delay)
    {
        m_snake.ChangeDirection(direction);
        m_last_rotate_tick = m_clock.GetTick();
    }

    event_flag = false;
}

template <uint8_t GridSize>
void Game<GridSize>::HandleAppleCollision()
{
    const auto& apple_positions{m_apple_spawner.GetApplePositions()};
    if (auto it = apple_positions.find(m_snake.GetHead().GetPosition()); it != apple_positions.end())
    {
        m_snake.Eat();
        m_apple_spawner.EatApple(it);
    }
}

template <uint8_t GridSize>
bool Game<GridSize>::IsOutsideGrid(Vector2i pos)
{
    return false;
    // return (pos.x > 7 || pos.x < 0) || (pos.y > 7 || pos.y < 0);
}

template <uint8_t GridSize>
bool Game<GridSize>::IsGameOver()
{
    auto& tails = m_snake.GetTails();

    return etl::find_if(tails.begin(),
                        tails.end(),
                        [this](const Body& tail) -> bool { return IsOutsideGrid(tail.GetPosition()); }) != tails.end() ||
           etl::find_if(tails.begin(),
                        tails.end(),
                        [this](const Body& tail) -> bool
                        { return !tail.IsHead() && m_snake.GetHead().GetPosition() == tail.GetPosition(); }) != tails.end();
}

template <uint8_t GridSize>
void Game<GridSize>::RestartGame()
{
    m_snake.Reset();
    m_apple_spawner.Reset();
}
