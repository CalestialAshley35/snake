# Snake Game

Welcome to the Snake Game! This is a classic snake game implemented using C and the ncurses library. The objective of the game is to control the snake and eat the food that appears on the screen. Each time the snake eats food, it grows longer, and the game continues until the snake collides with itself or the border.

## Features

- **Smooth Gameplay:** The game provides smooth and responsive gameplay using the ncurses library.
- **Score Tracking:** The game keeps track of the player's score, which is based on the length of the snake.
- **Food Generation:** Random food generation ensures a unique and challenging experience every time.
- **Game Over Screen:** Displays the final score and a game over message when the snake collides with itself or the border.

## Requirements

- **GCC:** You need GCC installed to compile the game.
- **ncurses:** The game uses the ncurses library and output.

## Installation

To install the game, follow these steps:

1. Clone the repository:
   ```bash
   git clone https://github.com/CalestialAshley35/snake.git
   ```
2. Navigate to the project directory:
   ```bash
   cd snake
   ```
3. Compile the game using GCC:
   ```bash
   gcc -o snake snake.c -lncurses
   ```

## How to Play

1. Run the game:
   ```bash
   ./snake
   ```
2. Use the arrow keys to control the snake:
   - **Up:** Move up
   - **Down:** Move down
   - **Left:** Move left
   - **Right:** Move right
3. The goal is to eat the food (`*`) that appears on the screen. Each time the snake eats food, it grows longer.
4. Avoid colliding with the borders (`#`) or with yourself. When the snake collides, the game is over, and the final score is displayed.

## Game Logic

The game consists of the following main functions:

- **init():** Initializes the ncurses library and sets up the game environment.
- **draw_border():** Draws the game border on the screen.
- **draw_snake:** Draws the snake on the screen based on its current position and length.
- **move_snake:** Moves the snake in the current direction and checks for collisions with the food.
- **collision:** Checks if the snake has collided with the border or itself.
- **generate_food:** Generates food at a random position on the screen.
- **game_over(int score):** Displays the game over screen with the final score.

## License

This project is licensed under the GNU General Public License v3.0. See the [LICENSE](https://www.gnu.org/licenses/gpl-3.0.html) file for details.
