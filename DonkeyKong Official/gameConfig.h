#pragma once
#include <Windows.h>

constexpr int LOW_DIFFCULTY = 0, MEDIUM_DIFFCULTY = 1, HIGH_DIFFCULTY = 2;
constexpr int BOARD_WIDTH = 80;
constexpr int BOARD_HEIGHT = 25;
constexpr int firstFloorY = 23;
constexpr int BARRELS_NUM = 15;
constexpr int diffculty[3] = { 3, 5, 7 };
constexpr int BARREL_SPAWN_RATE = 20;
constexpr int GAME_SPEED = 65;
constexpr int FALL_TO_DEATH = 5;
struct Direction { int x, y; };

void playWinningSong();
void playFailSong();
void printWinningMessage(); // Print the winning message
void printFailMessage(); // Print the fail message
void printInstructions(); // Print the game instructions
void printMenu(); // Print the game menu
void printGoodbyeMessage(); // Print the goodbye message



                                                          
                                                          
                                                          
                                                          
                                                          
                                                          
                                                          
                                                          