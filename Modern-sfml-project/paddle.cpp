#include "paddle.h"
#include "constants.h"

sf::Texture Paddle::texture_{"paddle.png"};

Paddle::Paddle(float x, float y) : MovingEntity{texture_}
{
  sprite_.setPosition({x, y});
  sprite_.setOrigin(centre());

  velocity_ = {0.0f, 0.0f};
}

void Paddle::update()
{
  process_input();

  sprite_.move(velocity_);
}

void Paddle::draw(sf::RenderWindow &window) const
{
  window.draw(sprite_);
}


void Paddle::move_left() noexcept
{
  velocity_.x = -constants::paddle_speed;
}

void Paddle::move_right() noexcept
{
  velocity_.x = constants::paddle_speed;
}

void Paddle::process_input()
{
  const auto width = constants::paddle_width;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && x() > width / 2)
    velocity_.x = -constants::paddle_speed;
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && x() <= constants::window_width - constants::paddle_width / 2)
    velocity_.x = constants::paddle_speed;
  else
    velocity_.x = 0.0f;
}
