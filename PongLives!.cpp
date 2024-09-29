/*
Name(s): Patrick Ekeu
Date: April 25, 2024
Project 3: Pong Lives!
Description: Create a 2-player version of Pong.
*/

#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <sstream>
#include <windows.h>

using namespace std;

// Define constants
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float PADDLE_WIDTH = 10.0f;
const float PADDLE_HEIGHT = 80.0f;
const float BALL_SIZE = 10.0f;
const float MAX_ANGLE = 60.0f; // Maximum departure angle in degrees
const float MIN_ANGLE = -60.0f; // Minimum departure angle in degrees

// Define global variables
float paddle1Y = WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2;
float paddle2Y = WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2;
float ballX = WINDOW_WIDTH / 2;
float ballY = WINDOW_HEIGHT / 2;
float ballSpeedX;
float ballSpeedY;
int paddle1Strikes = 0;
int paddle2Strikes = 0;
int currentLevel = 1; // 1: Easy, 2: Medium, 3: Hard
int scorePlayer1 = 0;
int scorePlayer2 = 0;
bool gameStarted = false;
bool gamePaused = false;

// Function to handle keyboard input
void handleKeypress(unsigned char key, int x, int y) {
    switch (key) {
        case 's':
            paddle1Y += 50.0f;
            break;
        case 'x':
            paddle1Y -= 50.0f;
            break;
        case 'e':
            currentLevel = 1; // Set difficulty to easy
            ballSpeedX = -5.0f;
            ballSpeedY = 2.0f;
            gameStarted = true;
            // Reset the score since mode chanced
            scorePlayer1 = 0;
            scorePlayer2 = 0;
            break;
        case 'm':
            currentLevel = 2; // Set difficulty to medium
            ballSpeedX = -10.0f;
            ballSpeedY = 4.0f;
            gameStarted = true;
            // Reset the score since mode chanced
            scorePlayer1 = 0;
            scorePlayer2 = 0;
            break;
        case 'h':
            currentLevel = 3; // Set difficulty to hard
            ballSpeedX = -15.0f;
            ballSpeedY = 8.0f;
            gameStarted = true;
            // Reset the score since mode chanced
            scorePlayer1 = 0;
            scorePlayer2 = 0;
            break;
        case 'r':
            // Reset the game
            paddle1Y = WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2;
            paddle2Y = WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2;
            ballX = WINDOW_WIDTH / 2;
            ballY = WINDOW_HEIGHT / 2;
            ballSpeedX = -1.0f;
            ballSpeedY = 1.0f;
            scorePlayer1 = 0;
            scorePlayer2 = 0;
            gameStarted = true;
            gamePaused = false;
            break;
        case 27: // 27 is the ASCII code for the escape key
            // Go back to the main menu
            gameStarted = false;
            gamePaused = false;
            // Reset the game
            paddle1Y = WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2;
            paddle2Y = WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2;
            ballX = WINDOW_WIDTH / 2;
            ballY = WINDOW_HEIGHT / 2;
            ballSpeedX;
            ballSpeedY;
            scorePlayer1 = 0;
            scorePlayer2 = 0;
            break;
        case 'p':
            // Pause or resume the game
            gamePaused = !gamePaused;
            break;

        case 'q':
            //Quit the game
            exit(0);
            break;
    }
}

// Function to handle special key input (arrow keys)
void handleSpecialKeypress(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            paddle2Y += 50.0f;
            break;
        case GLUT_KEY_DOWN:
            paddle2Y -= 50.0f;
            break;
    }
}

// Function to update game state
void update(int value) {
    if (gameStarted && !gamePaused) {
        // Update ball position
        ballX += ballSpeedX;
        ballY += ballSpeedY;

        // Check for collision with top and bottom walls
        if (ballY <= 0 || ballY >= WINDOW_HEIGHT - BALL_SIZE) {
            ballSpeedY = -ballSpeedY;
        }

        // Check for collision with paddles
        if (ballX <= PADDLE_WIDTH && ballY >= paddle1Y && ballY <= paddle1Y + PADDLE_HEIGHT) {
            // Calculate departure angle based on where the ball strikes the paddle
            float relativeIntersectY = (paddle1Y + PADDLE_HEIGHT / 2) - ballY;
            float normalizedRelativeIntersectY = relativeIntersectY / (PADDLE_HEIGHT / 2);
            float departureAngle = normalizedRelativeIntersectY * MAX_ANGLE;

            // Ensure departure angle lies within bounds
            if (departureAngle > MAX_ANGLE) departureAngle = MAX_ANGLE;
            if (departureAngle < MIN_ANGLE) departureAngle = MIN_ANGLE;

            ballSpeedX += cos(departureAngle * 3.14159 / 180) * 5.0f; // Ball speed magnitude remains constant
            ballSpeedY += sin(departureAngle * 3.14159 / 180) * 5.0f;

            paddle1Strikes++;
            if (paddle1Strikes % 4 == 0) {
                // Increase ball speed after every 4th strike
                if (ballSpeedX < 0)
                    ballSpeedX -= 1.0f;
                else
                    ballSpeedX += 1.0f;
                if (ballSpeedY < 0)
                    ballSpeedY -= 0.5f;
                else
                    ballSpeedY += 0.5f;
            }
        } else if (ballX >= WINDOW_WIDTH - PADDLE_WIDTH - BALL_SIZE && ballY >= paddle2Y && ballY <= paddle2Y + PADDLE_HEIGHT) {
            // Calculate angle based on where the ball strikes the paddle
            float relativeIntersectY = (paddle2Y + PADDLE_HEIGHT / 2) - ballY;
            float normalizedRelativeIntersectY = relativeIntersectY / (PADDLE_HEIGHT / 2);
            float departureAngle = normalizedRelativeIntersectY * MAX_ANGLE;

            if (departureAngle > MAX_ANGLE) departureAngle = MAX_ANGLE;
            if (departureAngle < MIN_ANGLE) departureAngle = MIN_ANGLE;

            ballSpeedX = -cos(departureAngle * 3.14159 / 180) * 5.0f; // Ball speed magnitude remains constant
            ballSpeedY = sin(departureAngle * 3.14159 / 180) * 5.0f;

            paddle2Strikes++;
            if (paddle2Strikes % 4 == 0) {
                // Increase ball speed after every 4th strike
                if (ballSpeedX < 0)
                    ballSpeedX -= 1.0f;
                else
                    ballSpeedX += 1.0f;
                if (ballSpeedY < 0)
                    ballSpeedY -= 0.5f;
                else
                    ballSpeedY += 0.5f;
            }
        }

        // Reset ball if it goes out of bounds and update scores
        if (ballX <= 0) {
            ballX = WINDOW_WIDTH / 2;
            ballY = WINDOW_HEIGHT / 2;
            ballSpeedX; // Reset ball speed
            ballSpeedY;
            scorePlayer2++;
        } else if (ballX >= WINDOW_WIDTH) {
            ballX = WINDOW_WIDTH / 2;
            ballY = WINDOW_HEIGHT / 2;
            ballSpeedX; // Reset ball speed
            ballSpeedY;
            scorePlayer1++;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

// Function to render objects
void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    if (!gameStarted) {
        // Draw main menu
        glColor3f(0.0f, 1.0f, 0.0f);
        glRasterPos2i(300, 400);
        string instructions = " PRESS LETTER FOR DIFFICULTY ";
        string easy = " (E) EASY ";
        string medium = " (M) MEDIUM ";
        string hard = " (H) HARD ";
        glRasterPos2i(225, 400);
        for (int i = 0; i < instructions.length(); i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, instructions[i]);
        }
        glRasterPos2i(300, 350);
        for (int i = 0; i < easy.length(); i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, easy[i]);
        }
        glRasterPos2i(300, 300);
        for (int i = 0; i < medium.length(); i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, medium[i]);
        }
        glRasterPos2i(300, 250);
        for (int i = 0; i < hard.length(); i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, hard[i]);
        }
    } else {
        // Draw scoreboard
        glColor3f(1.0f, 1.0f, 1.0f);
        stringstream score;
        score << "Player 1: " << scorePlayer1 << "  Player 2: " << scorePlayer2;
        glRasterPos2i(10, WINDOW_HEIGHT - 20);
        for (int i = 0; i < score.str().length(); i++) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, score.str()[i]);
        }

        // Draw upper and lower boundaries
        glColor3f(1.0f, 1.0f, 1.0f); // Set color to white
        glBegin(GL_LINES);
        glVertex2f(0.0f, 0.0f); // Bottom left
        glVertex2f(WINDOW_WIDTH, 0.0f); // Bottom right
        glVertex2f(0.0f, WINDOW_HEIGHT); // Top left
        glVertex2f(WINDOW_WIDTH, WINDOW_HEIGHT); // Top right
        glEnd();

        // Draw paddles
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_QUADS);
        glVertex2f(0.0f, paddle1Y);
        glVertex2f(PADDLE_WIDTH, paddle1Y);
        glVertex2f(PADDLE_WIDTH, paddle1Y + PADDLE_HEIGHT);
        glVertex2f(0.0f, paddle1Y + PADDLE_HEIGHT);

        glVertex2f(WINDOW_WIDTH - PADDLE_WIDTH, paddle2Y);
        glVertex2f(WINDOW_WIDTH, paddle2Y);
        glVertex2f(WINDOW_WIDTH, paddle2Y + PADDLE_HEIGHT);
        glVertex2f(WINDOW_WIDTH - PADDLE_WIDTH, paddle2Y + PADDLE_HEIGHT);
        glEnd();

        // Draw ball
        glColor3f(0.0f, 0.0f, 1.0f);
        glBegin(GL_QUADS);
        glVertex2f(ballX, ballY);
        glVertex2f(ballX + BALL_SIZE, ballY);
        glVertex2f(ballX + BALL_SIZE, ballY + BALL_SIZE);
        glVertex2f(ballX, ballY + BALL_SIZE);
        glEnd();

        // Draw the vertical thick dotted line
        glLineWidth(5.0f); // Set the line width to make it thick
        glEnable(GL_LINE_STIPPLE); // Enable line stipple to make the line dotted
        glLineStipple(2, 0xAAAA); // Set line stipple pattern for a dotted line
        glColor3f(1.0f, 1.0f, 1.0f); // Set color to white
        glBegin(GL_LINES);
        glVertex2f(WINDOW_WIDTH / 2, 0.0f); // Middle of the window, bottom
        glVertex2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT); // Middle of the window, top
        glEnd();
        glDisable(GL_LINE_STIPPLE); // Disable line stipple after drawing the line

        // Draw pause message if the game is paused
        if (gamePaused) {
            glColor3f(1.0f, 1.0f, 1.0f);
            string pauseMsg = "(P) Pause/Resume";
            string mainMenuMsg = "(ESC) Main Menu";
            string resetMsg = "(R) Reset Game";
            string quitMsg = "(Q) Quit Game";
            glRasterPos2i(WINDOW_WIDTH / 2 - 80, WINDOW_HEIGHT / 2);
            for (int i = 0; i < pauseMsg.length(); i++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, pauseMsg[i]);
            }
            glRasterPos2i(WINDOW_WIDTH / 2 - 80, WINDOW_HEIGHT / 2 + 20);
            for (int i = 0; i < pauseMsg.length(); i++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, mainMenuMsg[i]);
            }
            glRasterPos2i(WINDOW_WIDTH / 2 - 80, WINDOW_HEIGHT / 2 + 40);
            for (int i = 0; i < pauseMsg.length(); i++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, resetMsg[i]);
            }
            glRasterPos2i(WINDOW_WIDTH / 2 - 80, WINDOW_HEIGHT / 2 + 60);
            for (int i = 0; i < quitMsg.length(); i++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, quitMsg[i]);
            }

        }

         // Check if any player has reached the target score (10 points)
        if (scorePlayer1 >= 10 || scorePlayer2 >= 10) {
            // Fill the screen with a black rectangle
            glColor3f(0.0f, 0.0f, 0.0f);
            glBegin(GL_QUADS);
            glVertex2f(0.0f, 0.0f); // Bottom left corner
            glVertex2f(WINDOW_WIDTH, 0.0f); // Bottom right corner
            glVertex2f(WINDOW_WIDTH, WINDOW_HEIGHT); // Top right corner
            glVertex2f(0.0f, WINDOW_HEIGHT); // Top left corner
            glEnd();

            // Display winner message and options
            glColor3f(1.0f, 1.0f, 1.0f);
            string winnerMsg = scorePlayer1 >= 10 ? "Player 1 won!" : "Player 2 won!";
            string difficultyMsg = "Change difficulty (E, M, H)";
            string resetGameMsg = "Reset Game (R)";
            string mainMenuReturn = "Return to Main Menu (ESC)";
            string quitGame = "Quit Game (Q)";
            glRasterPos2i(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2);
            for (int i = 0; i < winnerMsg.length(); i++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, winnerMsg[i]);
            }
            glRasterPos2i(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 20);
            for (int i = 0; i < difficultyMsg.length(); i++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, difficultyMsg[i]);
            }
            glRasterPos2i(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 40);
            for (int i = 0; i < resetGameMsg.length(); i++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, resetGameMsg[i]);
            }
            glRasterPos2i(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 60);
            for (int i = 0; i < mainMenuReturn.length(); i++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, mainMenuReturn[i]);
            }
            glRasterPos2i(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 80);
            for (int i = 0; i < quitGame.length(); i++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, quitGame[i]);
            }
        }
    }
    glutSwapBuffers();
}

// Function to initialize OpenGL
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Project 3: Pong Game");
    glutDisplayFunc(render);
    glutKeyboardFunc(handleKeypress);
    glutSpecialFunc(handleSpecialKeypress); // Register special key input callback
    glutTimerFunc(16, update, 0);
    init();
    glutMainLoop();
    return 0;
}
