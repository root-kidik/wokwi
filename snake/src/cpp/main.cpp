#include <FastLED.h>

#include "ArduinoClock.hpp"
#include "Game.hpp"

#define GRID_SIZE    64
#define LED_TYPE     WS2812B
#define DATA_PIN     8
#define GAME_TICK_MS 500

ArduinoClock    clock;
Game<GRID_SIZE> game{clock};

CRGB m_leds[GRID_SIZE];

void RotateLeft()
{
    game.OnEvent(Direction::Left);
}

void RotateRight()
{
    game.OnEvent(Direction::Right);
}

void setup()
{
    pinMode(static_cast<uint8_t>(Direction::Left), INPUT_PULLUP);
    pinMode(static_cast<uint8_t>(Direction::Right), INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(static_cast<uint8_t>(Direction::Left)), RotateLeft, FALLING);
    attachInterrupt(digitalPinToInterrupt(static_cast<uint8_t>(Direction::Right)), RotateRight, FALLING);

    FastLED.addLeds<LED_TYPE, DATA_PIN, GRB>(m_leds, GRID_SIZE);
}

int Vector2iToGrid(Vector2i pos)
{
    return 7 - pos.y + pos.x * 8;
}

void Draw()
{
    FastLED.clear();

    const auto& snake{game.GetSnake()};
    const auto& apple_spawner{game.GetAppleSpawner()};
    const auto& head_position{snake.GetHead().GetPosition()};

    m_leds[Vector2iToGrid(head_position)] = CRGB::Gold;
    for (const auto& tail : snake.GetTails())
        if (!tail.IsHead())
            m_leds[Vector2iToGrid(tail.GetPosition())] = CRGB::Red;

    for (auto apple_position : apple_spawner.GetApplePositions())
        m_leds[Vector2iToGrid(apple_position)] = CRGB::Aqua;

    FastLED.show();

    delay(GAME_TICK_MS);
}

void loop()
{
    noInterrupts();
    game.Update();
    interrupts();
    Draw();
}
