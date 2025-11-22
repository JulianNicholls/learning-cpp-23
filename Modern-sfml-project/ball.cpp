#include "constants.h"
#include "ball.h"

sf::Texture Ball::texture_{"ball.png"};

Ball::Ball(float x, float y) : MovingEntity{texture_}
{
  sprite_.setPosition({x, y});
  sprite_.setOrigin(centre());

  velocity_ = { constants::ball_speed, constants::ball_speed };
}

void Ball::update()
{
  sprite_.move(velocity_);

  // Adjust the velocity at the L&R screen edges
  if(x() < 0 || x() > constants::window_width) velocity_.x = -velocity_.x;

  // Bounce at the top
  if(y() < 0 ) velocity_.y = -velocity_.y;

  // Fail at the bottom
  if(y() > constants::window_height) destroy();
}

void Ball::draw(sf::RenderWindow& window) const
{
  window.draw(sprite_);
}

void Ball::move_up() noexcept
{
  velocity_.y = -constants::ball_speed;
}

void Ball::move_down() noexcept
{
  velocity_.y = constants::ball_speed;
}

void Ball::move_left() noexcept
{
  velocity_.x = -constants::ball_speed;
}

void Ball::move_right() noexcept
{
  velocity_.x = constants::ball_speed;
}
