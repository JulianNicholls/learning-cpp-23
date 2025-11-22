#include "entity.h"

sf::FloatRect Entity::bounding_box() const noexcept
{
  return sprite_.getGlobalBounds();
}

sf::Vector2f Entity::centre() const noexcept
{
  auto box = bounding_box();
  return {box.size.x / 2.0f, box.size.y / 2.0f};
}

float Entity::x() const noexcept
{
  return sprite_.getPosition().x;
}

float Entity::y() const noexcept
{
  return sprite_.getPosition().y;
}

float Entity::left() const noexcept
{
  auto box = bounding_box();

  return x() - box.size.x / 2.0f;
}

float Entity::right() const noexcept
{
  auto box = bounding_box();

  return x() + box.size.x / 2.0f;
}

float Entity::top() const noexcept
{
  auto box = bounding_box();

  return y() - box.size.y / 2.0f;
}

float Entity::bottom() const noexcept
{
  auto box = bounding_box();

  return y() + box.size.y / 2.0f;
}

void Entity::destroy() noexcept
{
  destroyed_ = true;
}
