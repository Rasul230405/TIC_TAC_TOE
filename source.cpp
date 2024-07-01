
/*
    This is unbeatable Tic Tac Toe game written using minimax algorithm. 

    It has simple GUI and Player can choose whether to play with X or O.

    We have 2 boards: Logic Board and Graphics Board
    Logic board is used in minimax algorithm to determine the best move for computer.
    Graphics Board, as name implies, is used for GUI.

    Logic Board is a vector of 3 3-character-long strings each represents a row in tic tac toe board, intialized to '.'
    Intial Board:

                012          
               0...     
               1...     
               2...     

    After each move we update board. For example:

                012         
               0..O     
               1.X.     
               2...   

    Graphics board is a vector of 9 squares(they can be rectangles as well but I chose them to be squares in my code).

    I implemented mousePosToIndex() function that takes the mouse position in Graphics Board as a parameter and convert it to 
    the corresponding index which is crucial for updating logic board after player makes a move by clicking mouse. So we have
    bridge between Graphics board and Logic board.

*/
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> 
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Button.h"

#define M_PI 3.14

std::vector<std::string> board = { "...", "...", "..." };
std::vector<sf::RectangleShape> graphic_board;

const char DRAW = '-';
enum class Turn { Player, Computer };

void game_loop(sf::RenderWindow& window);

int main()
{
    float length = 600.f;
    float width = 600.f;
    sf::RenderWindow window(sf::VideoMode(length, width), "TIC TAC TOE");

    game_loop(window);

    return 0;

}



float radian_to_degree(float rad)
{
    return rad * 180.0 / M_PI;
}

bool is_endgame()
{
    for (int row = 0; row < 3; ++row) {
        if ((board[row][0] == 'X' && board[row][1] == 'X' && board[row][2] == 'X') || 
            (board[row][0] == 'O' && board[row][1] == 'O' && board[row][2] == 'O')) {
            return true;
        }
    }

    // Check columns
    for (int col = 0; col < 3; ++col) {
        if ((board[0][col] == 'X' && board[1][col] == 'X' && board[2][col] == 'X') ||
            (board[0][col] == 'O' && board[1][col] == 'O' && board[2][col] == 'O')) {
            return true;
        }
    }

    // Check diagonals
    if ((board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X') ||
        (board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == 'O')) {
        return true;
    }
    if ((board[0][2] == 'X' && board[1][1] == 'X' && board[2][0] == 'X') ||
        (board[0][2] == 'O' && board[1][1] == 'O' && board[2][0] == 'O')) {
        return true;
    }

    // check draw
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == '.') return false;
        }
    }

    return true;
}

char check_winner() {
    /*
    returns the figure of winner.If there is no winner returns '-'
    */

    // Check rows for winner
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2] && board[row][0] != '.') {
            return board[row][0];
        }
    }

    // Check columns for winner
    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col] && board[0][col] != '.') {
            return board[0][col];
        }
    }

    // Check diagonals for winner
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '.') {
        return board[0][0];
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != '.') {
        return board[0][2];
    }
    
    return DRAW;
}


void draw_x(int i, int j, sf::RenderWindow& window)
{
    float window_length = window.getSize().x;
    float window_width = window.getSize().y;

    sf::Color color(176, 113, 79);

    //draw first half of X
    float shorten = 20.f;
    float diagonal = sqrt((window_length / 3) * (window_length / 3) + (window_width / 3) * (window_width / 3));


    sf::RectangleShape line(sf::Vector2f(diagonal - (shorten * 2), 10.f));
    line.setFillColor(color);
    line.setPosition(j * (window_length / 3) + (shorten / 2), i * (window_width / 3) + (shorten / 2));

    // found rotation angle
    float angle = asin((window_width / 3) / diagonal);
    line.rotate(radian_to_degree(angle));

    window.draw(line);

    // draw second half of X
    sf::RectangleShape line2(sf::Vector2f(diagonal - shorten * 2, 10.f));
    line2.setFillColor(color);
    line2.setPosition(j * (window_length / 3) + (shorten / 2), (i + 1) * (window_width / 3) - (shorten / 2));
    
    float angle2 = asin((window_width / 3) / diagonal);
    line2.rotate(-(radian_to_degree(angle2)));

    window.draw(line2);
    
}

void draw_o(int i, int j, sf::RenderWindow& window)
{
    float window_length = window.getSize().x;
    float window_width = window.getSize().y;

    float radius_margin = 20.f;
    sf::CircleShape circle(((window_width / 3) / 2) - radius_margin);

    circle.setOutlineColor(sf::Color(215, 204, 188));
    circle.setOutlineThickness(10);

    float margin = 20.f;
    float x = j * (window_length / 3) + margin;
    float y = i * (window_width / 3) + margin;
    circle.setPosition(x, y);
   
    window.draw(circle);
    
}

void update_logic_board(char fig, int i, int j)
{
    board[i][j] = fig;
}

void update_graphics_board(char fig, int i, int j, sf::RenderWindow& window)
{
    if (fig == 'X') draw_x(i, j, window);
    if (fig == 'O') draw_o(i, j, window);
}


// update both logic and graphics board
void update_board(char fig, int i, int j, sf::RenderWindow& window)
{
    update_logic_board(fig, i, j);
    update_graphics_board(fig, i, j, window);
}

std::pair<int, int> mousePosToIndex(sf::Vector2f mousePos)
{
    // take mouse position and return corresponding index of board
    if (graphic_board[0].getGlobalBounds().contains(mousePos)) {
        return std::make_pair(0, 0);
    }
    else if (graphic_board[1].getGlobalBounds().contains(mousePos)) {
        return std::make_pair(0, 1);
    }
    else if (graphic_board[2].getGlobalBounds().contains(mousePos)) {
        return std::make_pair(0, 2);
    }
    else if (graphic_board[3].getGlobalBounds().contains(mousePos)) {
        return std::make_pair(1, 0);
    }
    else if (graphic_board[4].getGlobalBounds().contains(mousePos)) {
        return std::make_pair(1, 1);
    }
    else if (graphic_board[5].getGlobalBounds().contains(mousePos)) {
        return std::make_pair(1, 2);
    }
    else if (graphic_board[6].getGlobalBounds().contains(mousePos)) {
        return std::make_pair(2, 0);
    }
    else if (graphic_board[7].getGlobalBounds().contains(mousePos)) {
        return std::make_pair(2, 1);
    }
    else if (graphic_board[8].getGlobalBounds().contains(mousePos)) {
        return std::make_pair(2, 2);
    }
}

void player_move(char fig, sf::RenderWindow& window, bool& isMoveComplete)
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        // Handle player's move when left mouse button is pressed
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i localPosition = sf::Mouse::getPosition(window);

            sf::Vector2f mousePosF = sf::Vector2f(float(localPosition.x), float(localPosition.y));

            std::pair<int, int> board_index = mousePosToIndex(mousePosF);

            update_board(fig, board_index.first, board_index.second, window);

            isMoveComplete = true;
            return;
        }
    }
       
}


bool is_possible(int row, int col)
{
    if (board[row][col] != '.') return false;
    return true;
}


std::pair<int, std::pair<int, int>> minimax(char player, char comp, char user, bool max_player)
{
    /*
        This algorithm returns (value, index(i, j)). Computer need index to be able to make its move.
        Computer will always be maximizing player.
    */
    if (is_endgame()) {
        char w = check_winner();
        if (w == DRAW) return { 0, {-1, -1} };
        else if (w == comp) return { 1, {-1, -1} };
        else return {-1, {-1, -1}};
    }

    char next_player = (player == 'X' ? 'O' : 'X');
    std::pair<int, int> index;

    if (max_player) {
        int val = INT_MIN;

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (is_possible(i, j)) {
                    board[i][j] = player;
                    
                    std::pair<int, std::pair<int, int>> p = minimax(next_player, comp, user, false);
                    
                    if (val < p.first) {
                        val = p.first;
                        index = { i, j };
                    }
                    board[i][j] = '.';
                }
            }
        }

        return { val, index };
    }

    // min player
    else {
        int val = INT_MAX;

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (is_possible(i, j)) {
                    board[i][j] = player;
                    
                    std::pair<int, std::pair<int, int>> p = minimax(next_player, comp, user, true);
                  
                    if (val > p.first) {
                        val = p.first;
                        index = { i, j };
                    }
                    board[i][j] = '.';
                    
                }
            }
        }


        return { val, index };
    }

}

void computer_move(char fig, sf::RenderWindow& window, bool& isMoveComplete)
{
    
    char user = (fig == 'X' ? 'O' : 'X');

    std::pair<int, std::pair<int, int>> pos = minimax(fig, fig, user, true);

    update_board(fig, pos.second.first, pos.second.second, window);
    isMoveComplete = true;
}


void refresh()
{
    board = { "...", "...", "..." };
}


void draw_board(sf::RenderWindow& window)
{
    /*
        Board is a vector of 9 squares or rectangles
    */
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        // create squares(rectangles)
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                sf::RectangleShape rect(sf::Vector2f(window.getSize().x / 3, window.getSize().y / 3));
                rect.setOutlineColor(sf::Color::Black);
                rect.setOutlineThickness(5);
                rect.setPosition(j * (window.getSize().x / 3), i * (window.getSize().y / 3));
                graphic_board.push_back(rect);
            }
        }

        // draw squares(rectangles)
        for (sf::RectangleShape rect : graphic_board) {
            window.draw(rect);
        }

        // draw 'X's or 'O's
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == 'X')
                    draw_x(i, j, window);

                if (board[i][j] == 'O')
                    draw_o(i, j, window);
            }
        }

        // finally display
        window.display();

        return;
    }
    
}

std::pair<char, char> get_figure_choice(sf::RenderWindow& window)
{
    /*
        draw X and O buttons. If X is pressed returns ('X', 'O') pair, otherwise ('O', 'X') pair
    */
    float window_length = window.getSize().x;
    float window_width = window.getSize().y;
    
    sf::Font font;
    font.loadFromFile("Roboto-Black.ttf");

    // parameters of X button
    float buttonx_length = window_length / 2.f;
    float buttonx_width = window_width;
    sf::Vector2f buttonx_position(0, 0);
    sf::Color buttonX_color (176, 113, 79);
    sf::Color text_colorX = sf::Color::White;
    

    // parameters of O button
    float buttonO_length = window_length / 2.f;
    float buttonO_width = window_width;
    sf::Vector2f buttonO_position(window_length / 2.f, 0);
    sf::Color buttonO_color(215, 204, 188);
    sf::Color text_colorO = sf::Color::White;
    

    // Create buttons
    Button buttonX(buttonx_length, buttonx_width, buttonx_position, buttonX_color,
        "X", font, text_colorX);
    Button buttonO(buttonO_length, buttonO_width, buttonO_position, buttonO_color,
        "O", font, text_colorO);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        window.clear(sf::Color::White);
        buttonX.render(window);
        buttonO.render(window);
        window.display();

        if (buttonX.is_clicked(window)) {
            
            return std::make_pair('X', 'O');
        }
        if (buttonO.is_clicked(window)) {
            
            return std::make_pair('O', 'X');
        }
        
    }
}


void draw_winner_message(sf::RenderWindow& window, std::string& mssg)
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        sf::Font font;
        font.loadFromFile("Roboto-Black.ttf");

        sf::Text text;
        text.setFont(font); 
        text.setString(mssg); 
        text.setCharacterSize(50); // in pixels
        text.setFillColor(sf::Color::Black); 

        // write the message on the center of window
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        text.setPosition(0.f + window.getSize().x / 2.0f, 0.f + window.getSize().y / 2.0f);

        window.draw(text);
        window.display();
        sf::sleep(sf::seconds(1));
        return;
    }
}

bool is_quit(sf::RenderWindow& window)
{
    /*
        Draw QUIT and PLAY AGAIN buttons. Returns true if QUIT button pressed and returns false if 
        PLAY AGAIN pressed.
    */
    sf::Font font;
    font.loadFromFile("Roboto-Black.ttf");

    // quite button parameters
    float quit_button_length = window.getSize().x / 2.f;
    float quit_button_width = window.getSize().y / 5.f;
    sf::Color quit_button_color = sf::Color::White;
    sf::Color quit_button_text_color = sf::Color::Black;
    sf::Vector2f quit_button_position(window.getSize().x / 2.5f - quit_button_length / 3.f, window.getSize().y / 2.5f - quit_button_width / 3.f);
    std::string quit_button_text = "QUIT";

    // Play again button parameters
    float play_again_length = window.getSize().x / 2.f;
    float play_again_width = window.getSize().y / 5.f;
    sf::Color play_again_color = sf::Color::White;
    sf::Color play_again_text_color = sf::Color::Black;
    sf::Vector2f play_again_position(window.getSize().x / 2.5f - play_again_length / 3.f, window.getSize().y / 1.5f - play_again_width / 3.f);
    std::string play_again_text = "PLAY AGAIN";

    // Create buttons
    Button quit_button(quit_button_length, quit_button_width, quit_button_position, quit_button_color, quit_button_text, 
        font, quit_button_text_color);

    Button play_again(play_again_length, play_again_width, play_again_position, play_again_color, play_again_text, font, 
        play_again_text_color);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        if (quit_button.is_clicked(window)) {

            return true;
        }
        if (play_again.is_clicked(window)) {

            return false;
        }

        window.clear(sf::Color::White);
        quit_button.render(window);
        play_again.render(window);
        window.display();
        
    }
    return false;
}

void game_loop(sf::RenderWindow& window)
{

    while (window.isOpen()) {

        std::pair<char, char> choice = get_figure_choice(window);
        char player = choice.first;
        char computer = choice.second;


        Turn currentTurn = Turn::Player;
        bool isPlayerMoveComplete = false;
        bool isComputerMoveComplete = false;

        // draw initial board
        draw_board(window);

        while (!is_endgame()) {
            

            if (currentTurn == Turn::Player) {

                player_move(player, window, isPlayerMoveComplete);

                if (isPlayerMoveComplete) {
                    currentTurn = Turn::Computer;
                    isPlayerMoveComplete = false; // Reset for next round
                }

            }

            else if (currentTurn == Turn::Computer) {

                sf::sleep(sf::milliseconds(500));

                computer_move(computer, window, isComputerMoveComplete);

                if (isComputerMoveComplete) {
                    currentTurn = Turn::Player;
                    isComputerMoveComplete = false; // Reset for next round
                }
            }

            // after each move draw board
            draw_board(window);
        }

        sf::sleep(sf::milliseconds(500));

        if (check_winner() == player) {
            std::string mssg = "YOU HAVE WON!";
            draw_winner_message(window, mssg);
        }
        else if (check_winner() == computer) {
            std::string mssg = "YOU HAVE LOST :(";
            draw_winner_message(window, mssg);
        }
        else {
            std::string mssg = "DRAW!";
            draw_winner_message(window, mssg);
        }
        
        if (is_quit(window)) break;
        else {
            refresh();
            sf::sleep(sf::milliseconds(500));
        }
    }

}

