#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity
{
public:
  Entity(const sf::Texture &texture) : sprite_{texture} {};
  virtual ~Entity() {}

  virtual void update() = 0;
  virtual void draw(sf::RenderWindow &window) const = 0;

  sf::FloatRect bounding_box() const noexcept;
  sf::Vector2f centre() const noexcept;

  float x() const noexcept;
  float y() const noexcept;

  float left() const noexcept;
  float right() const noexcept;
  float top() const noexcept;
  float bottom() const noexcept;

  void destroy() noexcept;
  bool destroyed() const { return destroyed_; }

protected:
  sf::Sprite sprite_;
  bool destroyed_{false};
};

class MovingEntity : public Entity
{
public:
  MovingEntity(const sf::Texture &texture) : Entity{texture} {};

  virtual void move_up() noexcept = 0;
  virtual void move_down() noexcept = 0;
  virtual void move_left() noexcept = 0;
  virtual void move_right() noexcept = 0;

protected:
  sf::Vector2f velocity_;
};

#endif // ENTITY_H
