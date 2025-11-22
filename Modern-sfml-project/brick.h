#ifndef BRICK_H
#define BRICK_H

#include <vector>

#include "constants.h"
#include "entity.h"

class Brick : public Entity
{
public:
  Brick(float x, float y, bool random_colour = true);

  void update() override {}
  void draw(sf::RenderWindow &window) const override;

private:
  static std::vector<sf::Texture> textures_;
};

class BashableBrick : public Brick
{
public:
  BashableBrick(float x, float y) : Brick(x, y, false) {} // Always Green

  void update() override;

  void set_strength(int s) noexcept { strength_ = s; }
  void weaken() noexcept { --strength_; }
  bool too_weak() const noexcept { return strength_ <= 0; };

private:
  int strength_{constants::brick_strength};
};

#endif // BRICK_H
