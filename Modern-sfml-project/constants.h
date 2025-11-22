#ifndef CONSTANTS_H
#define CONSTANTS_H

struct constants
{
  static constexpr int    window_width{520};
  static constexpr int    window_height{450};

  static constexpr float  ball_speed{5.5f};

  static constexpr float  paddle_width{90.0f};
  static constexpr float  paddle_height{20.0f};
  static constexpr float  paddle_speed{10.0f};

  static constexpr float  brick_width{43.0f};
  static constexpr float  brick_height{20.0f};
  static constexpr float  brick_offset{brick_width / 2.0f};
  static constexpr int    brick_columns{10};
  static constexpr int    brick_rows{5};
  static constexpr int    brick_strength{3};

  static constexpr int    player_lives{3};
};

#endif // CONSTANTS_H
