#ifndef PADDLE_H
#define PADDLE_H

#include "entity.h"

class Paddle : public MovingEntity
{
public:
  Paddle(float x, float y);

  void update() override;
  void draw(sf::RenderWindow &window) const override;

  void move_up() noexcept override {};
  void move_down() noexcept override {};
  void move_left() noexcept override;
  void move_right() noexcept override;

private:
  void process_input();

  static sf::Texture texture_;
};

#endif // PADDLE_H
