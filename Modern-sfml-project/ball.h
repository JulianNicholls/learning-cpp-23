#ifndef BALL_H
#define BALL_H

#include "entity.h"

class Ball : public MovingEntity
{
public:
  Ball(float x, float y);

  void update() override;
  void draw(sf::RenderWindow &window) const override;

  void move_up() noexcept override;
  void move_down() noexcept override;
  void move_left() noexcept override;
  void move_right() noexcept override;

private:
  static sf::Texture texture_;
};

#endif // BALL_H
