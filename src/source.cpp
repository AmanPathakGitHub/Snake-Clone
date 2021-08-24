#include "raylib.h"
#include <vector>
#include <time.h>
#include <random>

const int screenWidth = 800;
const int screenHeight = 450;

struct Snake
{
    enum Direction
    {
        LEFT, 
        RIGHT,
        UP,
        DOWN
    };

    Snake(int x, int y)
        : x(x), y(y)
    {
    }

    int x, y;
    Direction direction;
};

struct Apple
{
    int x, y;

    void randomPos()
    {
        x = rand() % ((screenWidth - 16) / 16);
        y = rand() % ((screenHeight - 16) / 16);
    }
};

void handleMovement(Snake& snake)
{
    if(snake.direction == Snake::Direction::LEFT || snake.direction == Snake::Direction::RIGHT)
    {
        if(IsKeyPressed(KEY_UP)) snake.direction = Snake::Direction::UP;
        else if(IsKeyPressed(KEY_DOWN)) snake.direction = Snake::Direction::DOWN;
    }
    
    if(snake.direction == Snake::Direction::UP || snake.direction == Snake::Direction::DOWN)
    {    
        if(IsKeyPressed(KEY_LEFT)) snake.direction = Snake::Direction::LEFT;
        if(IsKeyPressed(KEY_RIGHT)) snake.direction = Snake::Direction::RIGHT;
    }
    
    if(snake.direction == Snake::Direction::LEFT) snake.x--;
    else if(snake.direction == Snake::Direction::RIGHT) snake.x++;
    else if(snake.direction == Snake::Direction::UP) snake.y--;
    else if(snake.direction == Snake::Direction::DOWN) snake.y++;
}

int main()
{

    srand(time(NULL));
    // Initialization
    //--------------------------------------------------------------------------------------
   

    InitWindow(screenWidth, screenHeight, "snek");

    SetTargetFPS(15);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    
    Snake snake = {15, 15};
    snake.direction = Snake::Direction::DOWN;

    Apple apple;
    apple.randomPos();

    std::vector<Snake> body;
  
    int tailSize = 5;

    char score[10];
      
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);
        
        handleMovement(snake);

        if(snake.x < 0)
            snake.x = (screenWidth - 16) / 16;
        
        else if (snake.x > (screenWidth - 16) / 16)
            snake.x = 0;

        else if(snake.y < 0)
            snake.y = (screenHeight) / 16;
        
        else if (snake.y > (screenHeight) / 16)
            snake.y = 0;
    


        for(Snake part : body)
        {
            DrawRectangle(part.x * 16, part.y * 16, 14, 14, GREEN);

            if(apple.x == part.x && apple.y == part.y)
                apple.randomPos();

            if(snake.x == part.x && snake.y == part.y)
                tailSize = 5;
        }

        if(apple.x == snake.x && apple.y == snake.y)
        {
            tailSize++;
            apple.randomPos();
        }
        
        body.push_back(snake);

        while(body.size() > tailSize)
        {
            body.erase(body.begin());
        }

        DrawRectangle(snake.x * 16, snake.y * 16, 14, 14, GREEN);
        DrawRectangle(apple.x * 16, apple.y * 16, 14, 14, RED);

        sprintf(score, "Score: %i", tailSize - 5);

        DrawText(score, 10, 20, 20, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}