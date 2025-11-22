#ifndef CREATURE_H
#define CREATURE_H

#include <SFML/Graphics.hpp>
#include <random>

class Creature
{
public:
  Creature(float x, float y)
  {
    velocity_ = {vx_, vy_};

    circle_.setPosition({x, y});

    circle_.setRadius(5.0f);
    circle_.setFillColor(sf::Color::Red);
  }

  void draw(sf::RenderWindow &window) const
  {
    window.draw(circle_);
  }

  void update()
  {
    vx_ = bd(mt) ? vx_ : -vx_;
    vy_ = bd(mt) ? vy_ : -vy_;

    circle_.move({vx_, vy_});
  }

private:
  // Random number generators
  static std::mt19937 mt;
  static std::bernoulli_distribution bd;

  float vx_{4.0f};
  float vy_{4.0f};
  sf::Vector2f velocity_;
  sf::CircleShape circle_;
};

std::mt19937 Creature::mt;
std::bernoulli_distribution Creature::bd;

#endif // CREATURE_H
