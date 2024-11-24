#include <stdio.h>
#include<time.h>
#include<stdlib.h>
#include <conio.h>
#include "raylib.h"

#define L1_WIDTH 13
#define L1_HEIGHT 15
#define L2_WIDTH 15
#define L2_HEIGHT 17
#define L3_WIDTH 23
#define L3_HEIGHT 23
#define L4_WIDTH 28
#define L4_HEIGHT 28

int playerX, playerY;
int enemyX, enemyY, enemy2X, enemy2Y, enemy3X, enemy3Y, enemy4X, enemy4Y;
int mazeWidth, mazeHeight;
int isL1_Mode = 0;
int isL2_Mode = 0;
int isL3_Mode = 0;
int isL4_Mode = 0;
int isL5_Mode = 0;

int moveUpPressed = 0;
int moveDownPressed = 0;
int moveLeftPressed = 0;
int moveRightPressed = 0;

long enemyMoveCounter1 = 0;  // Counter for enemy1 movement delay
long enemyMoveCounter2 = 0;  // Counter for enemy2 movement delay
long enemyMoveCounter3 = 0;  // Counter for enemy3 movement delay
long enemyMoveCounter4 = 0;  // Counter for enemy4 movement delay

// Adjust this value to control how often the enemies move (higher value = slower movement)
long moveDelay = 180;  // Move every 180 frames

Music backgroundMusic;
char maze[L4_HEIGHT][L4_WIDTH];

void initializeMaze() {
	for (int i = 0; i < mazeHeight; i++) {
		for (int j = 0; j < mazeWidth; j++) {
			maze[i][j] = '#';
		}
	}
		for (int i = 1; i < mazeHeight - 1; i++) {
			for (int j = 0; j < 20; j++) {
				int randX = rand() % (L4_HEIGHT - 2) + 1;
				int randY = rand() % (L4_WIDTH - 2) + 1;
				maze[randX][randY] = '#';
			}
			maze[i][1] = ' ';
			maze[i][mazeWidth - 2] = ' ';
			if (i % 2 == 0) {
				for (int j = 1; j < mazeWidth - 1; j++) {
					maze[i][j] = ' ';
				}
			}
		}
		for (int j = 1; j < mazeWidth - 1; j += 4) {
			for (int i = 1; i < mazeHeight - 1; i++) {
				maze[i][j] = ' ';
			}
		
		maze[1][1] = ' ';
		maze[mazeHeight - 2][mazeWidth - 2] = 'E';


	}
}void printMaze() {
    for (int i = 0; i < mazeHeight; i++) {
        for (int j = 0; j < mazeWidth; j++) {
            if (i == playerX && j == playerY) {
                printf("P ");
            } else if ((isL2_Mode || isL3_Mode || isL4_Mode || isL5_Mode) && i == enemyX && j == enemyY) {
                printf("M ");
            } else if ((isL3_Mode || isL4_Mode || isL5_Mode) && i == enemy2X && j == enemy2Y) {
                printf("M ");
            } else if ((isL4_Mode || isL5_Mode) && i == enemy3X && j == enemy3Y) {
                printf("M ");
            } else if (isL5_Mode && i == enemy4X && j == enemy4Y) {
                printf("M ");
            } else if (maze[i][j] == 'E') {  // Check for the exit point
                printf("E "); // Print 'E' for exit
            } else {
                printf("%c ", maze[i][j]);
            }
        }
        printf("\n");
    }
}
void moveEnemy1() {
    enemyMoveCounter1++;  // Increment the counter each frame
    if (enemyMoveCounter1 >= moveDelay) {  // Move only when the counter reaches moveDelay
        enemyMoveCounter1 = 0;  // Reset the counter
        // Move one step towards the player
        
        // Check if "W" is pressed to move right
        if (IsKeyPressed(KEY_W) && maze[enemyX][enemyY + 1] != '#') {
            enemyY++;  // Move right
        } else {
            // Normal movement towards the player
            if (playerX < enemyX && maze[enemyX - 1][enemyY] != '#') {
                enemyX--;  // Move up one tile
            } else if (playerX > enemyX && maze[enemyX + 1][enemyY] != '#') {
                enemyX++;  // Move down one tile
            } else if (playerY < enemyY && maze[enemyX][enemyY - 1] != '#') {
                enemyY--;  // Move left one tile
            } else if (playerY > enemyY && maze[enemyX][enemyY + 1] != '#') {
                enemyY++;  // Move right one tile
            }
        }
    }
}

void moveEnemy2() {
    enemyMoveCounter2++;  // Increment the counter each frame
    if (enemyMoveCounter2 >= moveDelay) {  // Move only when the counter reaches moveDelay
        enemyMoveCounter2 = 0;  // Reset the counter
        
		if (playerX < enemy2X && maze[enemy2X - 1][enemy2Y] != '#') {
			enemy2X--;
		} else if (playerX > enemy2X && maze[enemy2X + 1][enemy2Y] != '#') {
			enemy2X++;
		} else if (playerY < enemy2Y && maze[enemy2X][enemy2Y - 1] != '#') {
			enemy2Y--;
		} else if (playerY > enemy2Y && maze[enemy2X][enemy2Y + 1] != '#') {
			enemy2Y++;
		}

}
    }
void moveEnemy3() {
    enemyMoveCounter3++;  // Increment the counter each frame
    if (enemyMoveCounter3 >= moveDelay) {  // Move only when the counter reaches moveDelay
        enemyMoveCounter3 = 0;  // Reset the counter
        // Move one step towards the player
        if (playerX < enemy3X && maze[enemy3X - 1][enemy3Y] != '#') {
            enemy3X--;  // Move up one tile
        } else if (playerX > enemy3X && maze[enemy3X + 1][enemy3Y] != '#') {
            enemy3X++;  // Move down one tile
        } else if (playerY < enemy3Y && maze[enemy3X][enemy3Y - 1] != '#') {
            enemy3Y--;  // Move left one tile
        } else if (playerY > enemy3Y && maze[enemy3X][enemy3Y + 1] != '#') {
            enemy3Y++;  // Move right one tile
        }
    }
}

void moveEnemy4() {
    enemyMoveCounter4++;  // Increment the counter each frame
    if (enemyMoveCounter4 >= moveDelay) {  // Move only when the counter reaches moveDelay
        enemyMoveCounter4 = 0;  // Reset the counter
        // Move one step towards the player
        if (playerX < enemy4X && maze[enemy4X - 1][enemy4Y] != '#') {
            enemy4X--;  // Move up one tile
        } else if (playerX > enemy4X && maze[enemy4X + 1][enemy4Y] != '#') {
            enemy4X++;  // Move down one tile
        } else if (playerY < enemy4Y && maze[enemy4X][enemy4Y - 1] != '#') {
            enemy4Y--;  // Move left one tile
        } else if (playerY > enemy4Y && maze[enemy4X][enemy4Y + 1] != '#') {
            enemy4Y++;  // Move right one tile
        }
    }
}
void movePlayer() {
    if (IsKeyPressed(KEY_W) && moveUpPressed == 0 && maze[playerX - 1][playerY] != '#') {
        playerX--;  // Move up
        moveUpPressed = 1;
        
    }
    if (IsKeyPressed(KEY_S) && moveDownPressed == 0 && maze[playerX + 1][playerY] != '#') {
        playerX++;  // Move down
        moveDownPressed = 1;
    }
    if (IsKeyPressed(KEY_A) && moveLeftPressed == 0 && maze[playerX][playerY - 1] != '#') {
        playerY--;  // Move left
        moveLeftPressed = 1;
    }
    if (IsKeyPressed(KEY_D) && moveRightPressed == 0 && maze[playerX][playerY + 1] != '#') {
        playerY++;  // Move right
        moveRightPressed = 1;
    }
    // Reset movement flags when key is released
    if (IsKeyReleased(KEY_W)) moveUpPressed = 0;
    if (IsKeyReleased(KEY_S)) moveDownPressed = 0;
    if (IsKeyReleased(KEY_A)) moveLeftPressed = 0;
    if (IsKeyReleased(KEY_D)) moveRightPressed = 0;
}



Texture2D boxTexture;
void gameLoop(Texture2D background, Texture2D playerTexture, Texture2D enemyTexture) {
    while (!WindowShouldClose()) { // Main game loop
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the background image
        DrawTexture(background, 0,0, WHITE);

        // Draw maze walls and destructible blocks
        for (int i = 0; i < mazeHeight; i++) {
            for (int j = 0; j < mazeWidth; j++) {
                int x = j * 30;  // Scaling factor for grid
                int y = i * 30;

                if (maze[i][j] == '#') {
                    // Draw the box image instead of a rectangle
                    DrawTexture(boxTexture, x, y, WHITE); // Wall replaced with the box image
                }
            }
        }

        // Draw the player using the player texture
        DrawTexture(playerTexture, playerY * 30, playerX * 30, WHITE);  // Draw player texture

        // Draw enemies using the enemy texture
        if (isL2_Mode) {
            DrawTexture(enemyTexture, enemyY * 30, enemyX * 30, WHITE);  // Draw enemy texture
        }
        if (isL3_Mode) {
            DrawTexture(enemyTexture, enemyY * 30, enemyX * 30, WHITE);  // Draw enemy 1 texture
            DrawTexture(enemyTexture, enemy2Y * 30, enemy2X * 30, WHITE);  // Draw enemy 2 texture
        }
        if (isL4_Mode) {
            DrawTexture(enemyTexture, enemyY * 30, enemyX * 30, WHITE);  // Draw enemy 1 texture
            DrawTexture(enemyTexture, enemy2Y * 30, enemy2X * 30, WHITE);  // Draw enemy 2 texture
            DrawTexture(enemyTexture, enemy3Y * 30, enemy3X * 30, WHITE);  // Draw enemy 3 texture
        }
        if (isL5_Mode) {
            DrawTexture(enemyTexture, enemyY * 30, enemyX * 30, WHITE);  // Draw enemy 1 texture
            DrawTexture(enemyTexture, enemy2Y * 30, enemy2X * 30, WHITE);  // Draw enemy 2 texture
            DrawTexture(enemyTexture, enemy3Y * 30, enemy3X * 30, WHITE);  // Draw enemy 3 texture
            DrawTexture(enemyTexture, enemy4Y * 30, enemy4X * 30, WHITE);  // Draw enemy 4 texture
        }

        // Draw the exit point (E)
        if (maze[mazeHeight - 2][mazeWidth - 2] == 'E') {
            DrawRectangle((mazeWidth - 2) * 30, (mazeHeight - 2) * 30, 30, 30, GREEN); // Draw the exit as a green block
        }

        movePlayer();
        // Enemy movement
        if(isL2_Mode) moveEnemy1();
        if (isL3_Mode) { moveEnemy1(); moveEnemy2(); }
        if (isL4_Mode) { moveEnemy1(); moveEnemy2(); moveEnemy3(); }
        if (isL5_Mode) { moveEnemy1(); moveEnemy2(); moveEnemy3(); moveEnemy4(); }

        // Check for collision
        if ((playerX == enemyX && playerY == enemyY) ||
            ((isL3_Mode || isL4_Mode || isL5_Mode) && playerX == enemy2X && playerY == enemy2Y) ||
            ((isL4_Mode || isL5_Mode) && playerX == enemy3X && playerY == enemy3Y) ||
            (isL5_Mode && playerX == enemy4X && playerY == enemy4Y)) {
            printf("You were caught by an enemy! Game over!\n");
            break;
        }
        if (maze[playerX][playerY] == 'E') {
            printf("Congratulations! You reached the exit!\n");
            break;
        }

        if (!IsMusicStreamPlaying(backgroundMusic)) {
            PlayMusicStream(backgroundMusic);  // Play the music if it's not already playing
        }
        UpdateMusicStream(backgroundMusic);

        // Exit condition
        if (IsKeyPressed(KEY_Q)) {
            printf("Game exited by the player.\n");
            break;
        }

        EndDrawing();
    }
}

int main() {
    int level;
    printf("Choose a level to play (1-5): ");
    scanf("%d", &level);
    InitAudioDevice();
    // Initialize the maze based on level choice
    if (level == 1) {
        isL1_Mode = 1;
        playerX = 1;
        playerY = 1;
        mazeWidth = L1_WIDTH;
        mazeHeight = L1_HEIGHT;
        enemyX = L1_HEIGHT - 2;
        enemyY = L1_WIDTH - 2;
    } else if (level == 2) {
        isL2_Mode = 1;
        playerX = 1;
        playerY = 1;
        mazeWidth = L2_WIDTH;
        mazeHeight = L2_HEIGHT;
        enemyX = L2_HEIGHT - 2;
        enemyY = L2_WIDTH - 2;
    } else if (level == 3) {
        isL3_Mode = 1;
        playerX = 1;
        playerY = 1;
        mazeWidth = L3_WIDTH;
        mazeHeight = L3_HEIGHT;
        enemyX = L3_HEIGHT - 2;
        enemyY = L3_WIDTH - 2;
        enemy2X = 1;
        enemy2Y = L3_WIDTH - 2;
    } else if (level == 4) {
        isL4_Mode = 1;
        playerX = 1;
        playerY = 1;
        mazeWidth = L3_WIDTH;
        mazeHeight = L3_HEIGHT;
        enemyX = L3_HEIGHT - 2;
        enemyY = L3_WIDTH - 2;
        enemy2X = 1;
        enemy2Y = L3_WIDTH - 2;
        enemy3X = L3_WIDTH - 2;
        enemy3Y = 5;
    } else if (level == 5) {
        isL5_Mode = 1;
        playerX = 1;
        playerY = 1;
        mazeWidth = L4_WIDTH;
        mazeHeight = L4_HEIGHT;
        enemyX = L4_HEIGHT - 2;
        enemyY = L4_WIDTH - 2;
        enemy2X = 4;
        enemy2Y = L3_WIDTH - 2;
        enemy3X = L4_HEIGHT - 2;
        enemy3Y = 8;
        enemy4X = L4_HEIGHT - 10;
        enemy4Y = 9;
    } else {
        printf("Invalid level!\n");
        return 1;
    }
    initializeMaze();
    InitWindow(mazeWidth * 30, mazeHeight * 30, "Maze Game");
backgroundMusic = LoadMusicStream("background_music.mp3");  // Load your background music

    // Load the background, player, and enemy images
    Texture2D background = LoadTexture("bgg.png");
    Texture2D playerTexture = LoadTexture("player.png");  // Load the player image
    Texture2D enemyTexture = LoadTexture("enemy.png");  // Load the enemy image
 boxTexture = LoadTexture("box.png"); 
 
    gameLoop(background, playerTexture, enemyTexture);

    UnloadTexture(background);
    UnloadTexture(playerTexture);  // Don't forget to unload the player texture
    UnloadTexture(enemyTexture);   // Don't forget to unload the enemy texture
    UnloadMusicStream(backgroundMusic);  // Unload music stream
 UnloadTexture(boxTexture); 
    CloseWindow();

    return 0;
}


