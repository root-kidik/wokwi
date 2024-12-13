#pragma once

#include "AppleSpawner.hpp"
#include "IClock.hpp"
#include "Snake.hpp"

template <uint8_t GridSize>
class Game
{
public:
    static constexpr uint8_t MaxTails{GridSize - 1};
    static constexpr uint8_t MaxApples{GridSize / 4};

    Game(const IClock& clock);

    void Update();

    void OnEvent(Direction direction);

    inline const Snake<MaxTails>&                   GetSnake() const;
    inline const AppleSpawner<MaxApples, MaxTails>& GetAppleSpawner() const;

private:
    const uint32_t m_turn_delay{500};
    const uint8_t  m_apple_spawn_period{7};
    uint32_t       m_last_rotate_tick{};

    Snake<MaxTails>                   m_snake;
    AppleSpawner<MaxApples, MaxTails> m_apple_spawner;

    volatile bool m_is_rotate_right_pressed{};
    volatile bool m_is_rotate_left_pressed{};

    const IClock& m_clock;

    void HandleInput();

    void HandleButton(volatile bool& event_flag, Direction direction);
    void HandleAppleCollision();

    bool IsOutsideGrid(Vector2i pos);
    bool IsGameOver();
    void RestartGame();
};

#include "Game.inl"