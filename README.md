#   **Unbeatable Tic Tac Toe Game**
   
## **Overview**

Welcome to the unbeatable Tic Tac Toe game, crafted with the powerful minimax algorithm. This project delves into game theory and decision-making algorithms, providing an excellent opportunity to understand the core principles behind these concepts.
Features

   Unbeatable AI: Uses the minimax algorithm to ensure optimal moves and a challenging opponent.
   Intuitive GUI: Choose to play as either X or O with a user-friendly graphical interface.
   Interactive Gameplay: Click-based interaction to make moves.

## **How It Works**

The game consists of two main components:

- Logic Board: This is the backbone of the game where the minimax algorithm operates to determine the best moves for the computer.
- Graphics Board: A simple yet effective graphical representation of the Tic Tac Toe board, facilitating player interaction.

Game Boards

   - Logic Board:
      - Implemented as a vector of three strings, each string contains three characters representing a row on the Tic Tac Toe board.
      - The board is initialized with . to represent empty cells.

      - Initial Board:
           012
          0...
          1...
          2...

   - The board updates after each move. For example:
   - Updated Board:
        012
       0..O
       1.X.
       2...

 - Graphics Board:

    - Implemented as a vector of nine squares.
    - It is responsible for the graphical representation and user interaction.

 ## *Bridging Logic and Graphics*
 The mousePosToIndex() function is crucial for the game's functionality. It converts mouse positions from the Graphics Board into corresponding indices on the Logic Board, allowing seamless integration between the visual and logical components of the game.

 ## *Getting Started*
### Prerequisites

   - A C++ compiler (e.g., GCC, MSVC)
   - Basic understanding of C++ and game development

## *Installation*

   Clone the Repository:
           '''bash
           git clone https://github.com/your-username/tic-tac-toe-minimax.git'
           cd tic-tac-toe-minimax
           '''
   Build the Project:
      Compile the source code using your preferred C++ compiler.
## *Usage*

   - Run the Game:
   - Execute the compiled program to start the game.

   - Play the Game:
        - Choose whether to play as X or O.
        - Click on the Graphics Board to make your moves.
## *Minimax Algorithm*

The minimax algorithm ensures that the AI makes optimal decisions to either win or draw the game. It recursively evaluates possible game states and selects the move that minimizes the opponent's maximum score.

Everyone is welcome to contribute to this project


