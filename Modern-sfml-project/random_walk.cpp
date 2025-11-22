#include <SFML/Graphics.hpp>
#include <string>

#include "constants.h"
#include "creature.h"

using namespace std::string_literals;

int main()
{
  Creature adam(constants::window_width / 2, constants::window_height / 2);

  // Create the main window
  sf::RenderWindow game_window(sf::VideoMode({constants::window_width, constants::window_height}), "Random Walk"s);

  game_window.setFramerateLimit(60);

  while (game_window.isOpen())
  {
    // Clear screen
    game_window.clear(sf::Color::Black);

    // Process events
    while (const std::optional event = game_window.pollEvent())
    {
      // Close window: exit
      if (event->is<sf::Event::Closed>())
        game_window.close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
      game_window.close();

    // Updates here...

    adam.update();

    // Update the window
    adam.draw(game_window);
    game_window.display();
  }
}
