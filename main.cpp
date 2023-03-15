#include "raylib.h"
#include "player.h"

//------------------------------------------------------------------------------------
// VARIABLES
//------------------------------------------------------------------------------------

// Colores

Color VERDE = Color{48,232,115,255};
Color VERDE_OSCURO = Color{47,220,110,255};

// Juego
int speedsY[8] = {0,5,-5, 5, -5, 0, 6, -6};
const int screenWidth = 800;
const int screenHeight = 450;
const int paddleHeight = 120;
const int playerSpeed = 10;
// Objetos creados en 'player.h' y luego importados
Ball ball = Ball(400.0, 225.0, 15, 5, 0);
Player player = Player(10, screenHeight/2 - paddleHeight/2, playerSpeed, 25, paddleHeight);
Cpu cpu = Cpu(screenWidth -35, screenHeight/2 - paddleHeight/2, playerSpeed, 25, paddleHeight);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------

    InitWindow(screenWidth, screenHeight, "Pong By : @BotPY in youtube");
    int cpuReactionTime = (screenWidth/3)*2;
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        ball.update();
        player.update();
        cpu.move(ball.y, ball.x, screenWidth, screenHeight, paddleHeight, cpuReactionTime);
        
        if(ball.cpu_score+2 <= ball.player_score){
            cpuReactionTime = screenWidth/2;
        } else{
            cpuReactionTime = (screenWidth/3)*2;
        }
        if((ball.cpu_score >= ball.player_score)){
            cpu.speed = 8;
        } else{
            cpu.speed = 10;
        }
        
        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height}))
        {
            if(ball.speedx>=-12){
                ball.speedx = ball.speedx - 1;
            }
            ball.speedx *= -1;
            // ball.speedy = speedsY[GetRandomValue(0, 7)];
            ball.directionAfterCollisionWithPlayer(player.y, +2);
        }
        

        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height}))
        {   if(ball.speedx<=12){
                ball.speedx = ball.speedx + 1;
            }
            ball.speedx *= -1;
            ball.directionAfterCollisionWithPlayer(cpu.y, -2);
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            // Draws
            ClearBackground(VERDE);
            for(int i = 0; i<16; i++){
                if(i%2 != 0){
                    DrawRectangle(50*i, 0, 50, 450, VERDE_OSCURO); 
                }  
            } 
            DrawCircleLines(screenWidth/2, screenHeight/2, 80, WHITE);
            DrawLine(screenWidth/2, 0, screenWidth/2, screenHeight, WHITE);
            player.draw();
            ball.draw();
            cpu.draw();
            DrawText(TextFormat("%i", ball.cpu_score), 3 * screenWidth / 4 - 20, 20, 80, WHITE);
            DrawText(TextFormat("%i", ball.player_score), screenWidth / 4 - 20, 20, 80, WHITE );            
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

