#include <iostream>
#include <map>
#include <string>

using std::cout, std::endl;
using std::map, std::string;

using LevelMap = map<int, string>;
using GameMap = map<int, LevelMap>;

void print_game(const GameMap &game)
{
  cout << "Game Map";

  for (auto [index, level] : game)
  {
    cout << "\n  Level " << index << " Map" << endl;
    for (auto [position, object] : level)
    {
      cout << "    " << position << ": " << object << endl;
    }
  }
}

void nested_map()
{
  LevelMap level_one = {
      {1, "player"},
      {10, "door"}};

  LevelMap level_two = {
      {5, "player"},
      {10, "balrog"}};

  GameMap game = {
      {1, level_one},
      {2, level_two}};

  print_game(game);

  // Insert another entity into level 2
  auto level2 = game.find(2);

  if(level2 != game.end()) {
    level2->second.emplace(3, "magic wand");  // Emplace calls the constructor, removing the need for a copy
  }

  cout << "\nAfter item insertion\n";
  print_game(game);

  // Insert another level
  LevelMap level3 = {
    {7, "player"},
    {8, "bomb"}
  };

  game.emplace(3, level3);

  cout << "\nAfter level insertion\n";
  print_game(game);

  // Remove the balrog from level 2
  auto& lmap = level2->second;
  auto ten = lmap.find(10);

  if(ten != lmap.end())
    lmap.erase(ten);

  cout << "\nAfter monster removal\n";
  print_game(game);
}

int main()
{
  nested_map();
}
