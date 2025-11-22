#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <map>
#include <memory>
#include <typeinfo>
#include <vector>

#include "entity.h"

using EntityVector = std::vector<std::unique_ptr<Entity>>;
using AliasVector = std::vector<Entity *>;

class EntityManager
{
public:
  template <typename T, typename... Args> T &create(Args &&...args)
  {
    static_assert(std::is_base_of<Entity, T>::value, R"("T" Type parameter to create() myst be derived from "Entity")");

    // Make a unique_ptr and forward the arguments
    auto ptr{std::make_unique<T>(std::forward<Args>(args)...)};

    // Make an alias
    auto ptr_alias = ptr.get();

    // Get the hash code to use as the key in the map
    auto hash = typeid(T).hash_code();

    all_entities_.emplace_back(std::move(ptr));
    grouped_entities_[hash].emplace_back(ptr_alias);

    return *ptr_alias;
  }

  void refresh();

  void clear();

  template <typename T> auto &all()
  {
    return grouped_entities_[typeid(T).hash_code()];
  }

  template<typename T, typename Func> void apply(const Func& func)
  {
    auto& group{all<T>()};

    for(auto ptr : group)
      func(*dynamic_cast<T*>(ptr));
  }

  void update();

  void draw(sf::RenderWindow& window);

private:
  EntityVector all_entities_;
  std::map<size_t, AliasVector> grouped_entities_;
};

#endif // ENTITY_MANAGER_H
