#include <random>

#include "brick.h"
#include "constants.h"

std::vector<sf::Texture> Brick::textures_{sf::Texture{"brick01.png"}, sf::Texture{"brick02.png"}, sf::Texture{"brick03.png"}};

const sf::Color brick_colour3{0, 255, 0, 255}; // Bright Green
const sf::Color brick_colour2{0, 255, 0, 170}; // Medium Green
const sf::Color brick_colour1{0, 255, 0, 80};  // Dull Green

static std::random_device rd;
static std::mt19937 mt(rd());
static std::uniform_int_distribution<int> ud(0, 2);

Brick::Brick(float x, float y, bool random_colour) : Entity(textures_[0])
{
  if (random_colour)
  {
    if (auto idx = ud(mt); idx > 0)
      sprite_ = sf::Sprite(textures_[idx]);
  }

  sprite_.setPosition({x, y});
  sprite_.setOrigin(centre());
}

void Brick::draw(sf::RenderWindow &window) const
{
  window.draw(sprite_);
}

void BashableBrick::update()
{
  switch (strength_)
  {
  case 3:
    sprite_.setColor(brick_colour3);
    break;

  case 2:
    sprite_.setColor(brick_colour2);
    break;

  case 1:
    sprite_.setColor(brick_colour1);
    break;
  }
}
