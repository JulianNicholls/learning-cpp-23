#include "background.h"

sf::Texture Background::texture_{"background.jpg"};

Background::Background(float x, float y) : Entity{texture_}
{
  sprite_.setTexture(texture_);
  sprite_.setPosition({x, y});
}

void Background::update() {
  // Nothing
}

void Background::draw(sf::RenderWindow& window) const
{
  window.draw(sprite_);
}
