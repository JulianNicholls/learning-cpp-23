#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <string>

#include "constants.h"
#include "entity_manager.h"

class Game
{
public:
  Game(sf::Vector2u size, std::string title);

  void loop();
  void reset();

private:
  void process_keyboard();
  void show_text(int frame_num);

  EntityManager emanager_;
  sf::RenderWindow window_;
  static sf::Font font_;

  sf::Text text_lives_;

  int lives_{constants::player_lives};

  enum class State
  {
    unstarted,
    paused,
    running,
    game_over,
    player_won
  };

  State state_{State::unstarted};
};

#endif // GAME_H
