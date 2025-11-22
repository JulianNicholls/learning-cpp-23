#include "entity_manager.h"

using std::remove_if, std::begin, std::end;

void EntityManager::refresh()
{
  // The aliases need to be removed first, otherwise they will be danglers.
  for (auto &[type, alias_vec] : grouped_entities_)
  {
    alias_vec.erase(remove_if(begin(alias_vec), end(alias_vec),
                              [](const auto &b)
                              { return b->destroyed(); }),
                    end(alias_vec));
  }

  // Then we can remove the actual entities.
  all_entities_.erase(remove_if(begin(all_entities_), end(all_entities_),
                                [](const auto &p)
                                { return p->destroyed(); }),
                      end(all_entities_));
}

void EntityManager::clear()
{
  grouped_entities_.clear();
  all_entities_.clear();
}

void EntityManager::update()
{
  for (auto &e : all_entities_)
    e->update();
}

void EntityManager::draw(sf::RenderWindow &window)
{
  for (auto &e : all_entities_)
    e->draw(window);
}
