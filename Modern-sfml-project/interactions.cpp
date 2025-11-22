#include "interactions.h"

namespace {
  void update_ball(Ball &ball, const Brick &brick)
  {
    float left_overlap = ball.right() - brick.left();
    float right_overlap = brick.right() - ball.left();

    float top_overlap = ball.bottom() - brick.top();
    float bottom_overlap = brick.bottom() - ball.top();

    bool from_left = abs(left_overlap) < abs(right_overlap);
    bool from_top = abs(top_overlap) < abs(bottom_overlap);

    float min_x_overlap = from_left ? left_overlap : right_overlap;
    float min_y_overlap = from_top ? top_overlap : bottom_overlap;

    if (abs(min_x_overlap) < abs(min_y_overlap))
    {
      if (from_left)
        ball.move_left();
      else
        ball.move_right();
    }
    else
    {
      if (from_top)
        ball.move_up();
      else
        ball.move_down();
    }
  }
};

bool is_interacting(const Entity &a, const Entity &b)
{
  auto boxa = a.bounding_box();
  auto boxb = b.bounding_box();

  return boxa.findIntersection(boxb) != std::nullopt;
}

void handle_collision(const Paddle &p, Ball &b)
{
  if (is_interacting(p, b))
  {
    b.move_up();

    if (b.x() < p.x())
      b.move_left();
    else
      b.move_right();
  }
}

void handle_collision(Ball &ball, Brick &brick)
{
  // Bail out if no interaction is happening
  if (!is_interacting(ball, brick))
    return;

  brick.destroy();

  update_ball(ball, brick);
}

void handle_collision(Ball &ball, BashableBrick &brick)
{
  // Bail out if no interaction is happening
  if (!is_interacting(ball, brick))
    return;

  brick.weaken();

  if(brick.too_weak()) brick.destroy();

  update_ball(ball, brick);
}
