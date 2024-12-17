#include "gameConfig.h"
#include <iostream>
#include "utils.h"

// Function to play the winning song
void playWinningSong() {
    // Frequencies (in Hz) for different notes
    const int C4 = 261;
    const int D4 = 294;
    const int E4 = 329;
    const int F4 = 349;
    const int G4 = 392;
    const int A4 = 440;
    const int B4 = 466;
    const int C5 = 523;

    // Durations for each note (in milliseconds)
    const int quarterNote = 400;
    const int halfNote = 800;
    const int eighthNote = 200;
    const int dottedQuarterNote = 600;

    // Start with an ascending melody
    Beep(C4, quarterNote);
    Beep(D4, quarterNote);
    Beep(E4, quarterNote);
    Beep(F4, quarterNote);

    // Play a quick higher melody
    Beep(G4, eighthNote);
    Beep(A4, eighthNote);
    Beep(G4, quarterNote);
    Beep(F4, quarterNote);

    // Add some more variation with jumps
    Beep(C5, quarterNote);   // Big jump to C5 for excitement
    Beep(B4, quarterNote);
    Beep(A4, quarterNote);

    // End with a happy conclusion
    Beep(C5, halfNote);  // Bright, final note to signal the win
}

void playFailSong()
{
    Beep(523, 300); // C5, 500 ms
    Beep(587, 300); // D5, 500 ms
    Beep(659, 300); // E5, 500 ms
    Beep(698, 300); // F5, 500 ms
    Beep(784, 500); // G5, 500 ms
}

void printWinningMessage()
{
    const int consoleWidth = 80;
    const int artWidth = 75;
    const int consoleHeight = 25;

    const char* art[] = {
        "+---------------------------------------------------------------------------+",
        "|____    ____  ______    __    __     ____    __    ____  ______   .__   __.|",
        "|\\   \\  /   / /  __  \\  |  |  |  |    \\   \\  /  \\  /   / /  __  \\  |  \\ |  ||",
        "| \\   \\/   / |  |  |  | |  |  |  |     \\   \\/    \\/   / |  |  |  | |   \\|  ||",
        "|  \\_    _/  |  |  |  | |  |  |  |      \\            /  |  |  |  | |  . `  ||",
        "|    |  |    |  `--'  | |  `--'  |       \\    /\\    /   |  `--'  | |  |\\   ||",
        "|    |__|     \\______/   \\______/         \\__/  \\__/     \\______/  |__| \\__||",
        "+---------------------------------------------------------------------------+"
    };

    // Dynamically calculate art height based on array size
    const int artHeight = sizeof(art) / sizeof(art[0]);

    int horizontalPadding = (consoleWidth - artWidth) / 2; // Horizontal centering
    int verticalPadding = (consoleHeight - artHeight) / 2; // Vertical centering

    // Print each line of the ASCII art
    for (int i = 0; i < artHeight; ++i)
    {
        gotoxy(horizontalPadding, verticalPadding + i); // Position each line
        std::cout << art[i];
    }
}



void printFailMessage()
{
    const int consoleWidth = 80;
    const int artWidth = 46;
    const int consoleHeight = 25;

    const char* art[] = {
        "+----------------------------------------------+",
        "|  _______      ___      .___  ___.  _______   |",
        "| /  _____|    /   \\     |   \\/   | |   ____|  |",
        "||  |  __     /  ^  \\    |  \\  /  | |  |__     |",
        "||  | |_ |   /  /_\\  \\   |  |\\/|  | |   __|    |",
        "||  |__| |  /  _____  \\  |  |  |  | |  |____   |",
        "| \\______| /__/     \\__\\ |__|  |__| |_______|  |",
        "|                                              |",
        "|  ______   ____    ____  _______ .______      |",
        "| /  __  \\  \\   \\  /   / |   ____||   _  \\     |",
        "||  |  |  |  \\   \\/   /  |  |__   |  |_)  |    |",
        "||  |  |  |   \\      /   |   __|  |      /     |",
        "||  `--'  |    \\    /    |  |____ |  |\\  \\-.   |",
        "| \\______/      \\__/     |_______|| _| `.__|   |",
        "+----------------------------------------------+"
    };

    // Dynamically calculate art height based on array size
    const int artHeight = sizeof(art) / sizeof(art[0]);

    int horizontalPadding = (consoleWidth - artWidth) / 2; // Horizontal centering
    int verticalPadding = (consoleHeight - artHeight) / 2; // Vertical centering

    // Print each line of the ASCII art
    for (int i = 0; i < artHeight; ++i)
    {
        gotoxy(horizontalPadding, verticalPadding + i); // Position each line
        std::cout << art[i];
    }
}




void printInstructions()
{
    std::cout << "\n+----------------------------------------------+\n";
    std::cout << "|                 INSTRUCTIONS                 |\n";
    std::cout << "+----------------------------------------------+\n";
    std::cout << "\nWelcome to the game! Your goal is to reach the\n"
        "top of the board and save the princess ($)\n"
        "from Donkey Kong (&)!\n\n";

    std::cout << "Game Objective:\n";
    std::cout << "- Navigate the board as Mario (@).\n";
    std::cout << "- Avoid the barrels thrown by Donkey Kong (&).\n";
    std::cout << "- Barrels can explode after falling a few floors, so\n"
        "  be careful as they may change the course of your journey!\n";
    std::cout << "- Use ladders to climb up and save the princess ($) at the top.\n\n";

    std::cout << "You have 3 lives. Use them wisely. Good luck!\n\n";

    std::cout << "Controls:\n";
    std::cout << "  'a' - Move left\n";
    std::cout << "  'd' - Move right\n";
    std::cout << "  'w' - Jump or climb up a ladder\n";
    std::cout << "  's' - Stop\n";
    std::cout << "  'x' - Climb down a ladder\n";
    std::cout << "  'esc' - Pause the game\n\n";

    std::cout << "Press any key to return to the menu...\n";
    std::cout << "+----------------------------------------------+\n";
}



void printMenu()
{
    system("cls");
    std::cout << R"( 
		         ____   ___  _   _ _  _________   __
			|  _ \ / _ \| \ | | |/ / ____\ \ / /
			| | | | | | |  \| | ' /|  _|  \ V / 
			| |_| | |_| | |\  | . \| |___  | |  
			|____/_\___/|_|_\_|_|\_\_____| |_|  
			| |/ / _ \| \ | |/ ___|             
			| ' / | | |  \| | |  _              
			| . \ |_| | |\  | |_| |             
			|_|\_\___/|_| \_|\____|             )" << std::endl;

    std::cout << "******************************************************************************" << std::endl;
    std::cout << "Chose from the options below by using the keyboard:" << std::endl;
    std::cout << "\n";
    std::cout << "1. Start Game" << std::endl;
    std::cout << "\n";
    std::cout << "8. Present instructions and keys" << std::endl;
    std::cout << "\n";
    std::cout << "9. Exit" << std::endl;
    std::cout << "\n";
}


void printGoodbyeMessage()
{
    const int consoleWidth = 80;
    const int consoleHeight = 25;
    const int artWidth = 69;
    const int artHeight = 7;

    int startX = (consoleWidth - artWidth) / 2;
    int startY = (consoleHeight - artHeight) / 2;

    gotoxy(startX, startY++); std::cout << "+---------------------------------------------------------------------+";
    gotoxy(startX, startY++); std::cout << "|     _______. _______  _______            ____    ____  ___       __ |";
    gotoxy(startX, startY++); std::cout << "|    /       ||   ____||   ____|           \\   \\  /   / /   \\     |  ||";
    gotoxy(startX, startY++); std::cout << "|   |   (----`|  |__   |  |__    ______     \\   \\/   / /  ^  \\    |  ||";
    gotoxy(startX, startY++); std::cout << "|    \\   \\    |   __|  |   __|  |______|     \\_    _/ /  /_\\  \\   |  ||";
    gotoxy(startX, startY++); std::cout << "|.----)   |   |  |____ |  |____                |  |  /  _____  \\  |__||";
    gotoxy(startX, startY++); std::cout << "||_______/    |_______||_______|               |__| /__/     \\__\\ (__)|";
    gotoxy(startX, startY++); std::cout << "+---------------------------------------------------------------------+";
}







