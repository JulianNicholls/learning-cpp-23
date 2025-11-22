#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "constants.h"
#include "entity.h"

class Background : public Entity
{
public:
  Background(float x, float y);

  void update() override;
  void draw(sf::RenderWindow &window) const override;

private:
  static sf::Texture texture_;
};

#endif // BACKGROUND_H
