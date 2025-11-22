#include "game.h"
#include "background.h"
#include "ball.h"
#include "brick.h"
#include "interactions.h"
#include "paddle.h"

using namespace std::string_literals;

sf::Font Game::font_("arial.ttf");

Game::Game(sf::Vector2u size, std::string title) : window_(sf::VideoMode(size), title), text_lives_(font_)
{
  window_.setFramerateLimit(60);

  text_lives_.setPosition({constants::window_width - 65.0, 2});
  text_lives_.setCharacterSize(12);

  reset();
}

void Game::reset()
{
  lives_ = constants::player_lives;

  text_lives_.setString("Lives: "s + std::to_string(lives_));
  state_ = State::unstarted;

  emanager_.clear();

  emanager_.create<Background>(0.0f, 0.0f);
  emanager_.create<Ball>(constants::window_width / 2.0f, constants::window_height / 2.0f - 60.0f);
  emanager_.create<Paddle>(constants::window_width / 2.0f - constants::paddle_width / 2.0f, constants::window_height - constants::paddle_height);

  for (auto i = 0; i < constants::brick_columns; ++i)
  {
    for (auto j = 0; j < constants::brick_rows; ++j)
    {
      float x = constants::brick_offset + (i + 1) * constants::brick_width;
      float y = (j + 2) * constants::brick_height;

      if (j == constants::brick_rows - 1) // Last Row
        emanager_.create<BashableBrick>(x, y);
      else
        emanager_.create<Brick>(x, y);
    }
  }
}

void Game::loop()
{
  int frame_num = 0;

  while (window_.isOpen())
  {
    ++frame_num;

    // Process events
    while (const std::optional event = window_.pollEvent())
    {
      // Close window: exit
      if (event->is<sf::Event::Closed>())
        window_.close();
    }

    process_keyboard();

    // Clear screen
    window_.clear(sf::Color::Black);

    // Draw the window
    emanager_.draw(window_);

    window_.draw(text_lives_);

    if (state_ != State::running)
      show_text(frame_num);
    else
    {
      if (emanager_.all<Ball>().empty())
      {
        emanager_.create<Ball>(constants::window_width / 2.0f, constants::window_height / 2.0f - 60.0f);

        --lives_;
        state_ = State::paused;
        text_lives_.setString("Lives: "s + std::to_string(lives_));
      }

      if (emanager_.all<Brick>().empty() && emanager_.all<BashableBrick>().empty())
        state_ = State::player_won;

      if (lives_ <= 0)
        state_ = State::game_over;

      // Update all the entities
      emanager_.update();

      emanager_.apply<Ball>([this](auto &ball)
                            { emanager_.apply<Paddle>([&ball](auto &paddle)
                                                      { handle_collision(paddle, ball); }); });

      emanager_.apply<Ball>([this](auto &ball)
                            { emanager_.apply<BashableBrick>([&ball](auto &brick)
                                                             { handle_collision(ball, brick); }); });

      emanager_.apply<Ball>([this](auto &ball)
                            { emanager_.apply<Brick>([&ball](auto &brick)
                                                     { handle_collision(ball, brick); }); });

      emanager_.refresh();
    }

    window_.display();
  }
}

void Game::process_keyboard()
{
  static bool pause_key_active{false};

  // ESCape closes
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
    window_.close();

  if (state_ != State::unstarted)
  {
    // P Pauses
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
    {
      if (!pause_key_active)
      {
        if (state_ == State::paused)
          state_ = State::running;
        else
          state_ = State::paused;
      }

      pause_key_active = true;
    }
    else
      pause_key_active = false;

    // R Resets
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
      reset();
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    state_ = State::running;
}

void Game::show_text(int frame_num)
{
  std::string str;

  switch (state_)
  {
  case State::paused:
    str = "Paused";
    break;

  case State::unstarted:
    str = "Press S to Start";
    break;

  case State::player_won:
    str = "Player Wins";
    break;

  case State::game_over:
    str = "Game Over";
    break;

  default:
    break;
  }

  sf::Text text(font_, str, 24);

  // Measure and centre the text slightly below the ball starting point
  auto bound = text.getLocalBounds();
  float left = constants::window_width / 2.0f - bound.size.x / 2.0f;
  float top = constants::window_height / 2.0f + bound.size.y / 2.0f;
  auto opacity = cosf((frame_num % 64) * M_PI / 31.5f) * 64.0f;

  text.setPosition({left, top});
  text.setFillColor({255, 255, 255, static_cast<uint8_t>(191 + opacity)});
  window_.draw(text);
}
