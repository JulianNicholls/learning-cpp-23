#ifndef INTERACTIONS_H
#define INTERACTIONS_H

#include "ball.h"
#include "paddle.h"
#include "brick.h"

void handle_collision(const Paddle& p, Ball& b);
void handle_collision(Ball& ball, Brick& brick);
void handle_collision(Ball& ball, BashableBrick& brick);

bool is_interacting(const Entity& a, const Entity& b);

#endif  // INTERACTIONS_H
