#include <SFML/Graphics.hpp>
#include <string>

#include "constants.h"
#include "game.h"

using namespace std::string_literals;

int main()
{
    Game game({constants::window_width, constants::window_height}, "Breakout V1.7"s);

    game.loop();
}
