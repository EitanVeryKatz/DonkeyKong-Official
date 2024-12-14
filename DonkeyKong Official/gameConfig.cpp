#include "gameConfig.h"
#include <iostream>

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


void playWeAreTheChampions() 
{
    // Frequencies (in Hz) for different notes
    const int G4 = 392;
    const int A4 = 440;
    const int B4 = 466;
    const int C5 = 523;
    const int D5 = 587;
    const int E5 = 659;
    const int F5 = 698;

    // Durations for each note (in milliseconds)
    const int quarterNote = 400;
    const int halfNote = 800;
    const int eighthNote = 200;
    const int dottedQuarterNote = 600;

    // Approximation of the "We Are the Champions" motif
    Beep(G4, halfNote);            // "We"
    Beep(A4, halfNote);            // "are"
    Beep(B4, halfNote);            // "the"
    Beep(G4, dottedQuarterNote);   // "Cham-"
    Beep(C5, eighthNote);          // "-pi-"
    Beep(B4, quarterNote);         // "-ons"

    // Add a dramatic pause
    Sleep(400);

    // Continuation with descending melody
    Beep(B4, quarterNote);         // "of"
    Beep(A4, quarterNote);         // "the"
    Beep(G4, halfNote);            // "world"
    Beep(G4, halfNote);            // Sustained "world" (repeat G4 for dramatic effect)

    // Ending flourish
    Beep(D5, quarterNote);
    Beep(C5, quarterNote);
    Beep(B4, halfNote);            // Final triumphant note
}


void printWinningMessage()
{
    const int consoleWidth = 80;
    const int artWidth = 75;
    const int consoleHeight = 25;
    const int artHeight = 7;

    int horizontalPadding = (consoleWidth - artWidth) / 2; // 2 spaces
    int verticalPadding = (consoleHeight - artHeight) / 2; // 9 blank lines

    // Print vertical padding (before the ASCII art)
    for (int i = 0; i < verticalPadding; ++i)
    {
        std::cout << std::endl;
    }

    // Print ASCII art with horizontal padding
    std::string padding(horizontalPadding, ' '); // Generate 2 spaces
    std::cout << padding << R"(
+---------------------------------------------------------------------------+
|____    ____  ______    __    __     ____    __    ____  ______   .__   __.|
|\   \  /   / /  __  \  |  |  |  |    \   \  /  \  /   / /  __  \  |  \ |  ||
| \   \/   / |  |  |  | |  |  |  |     \   \/    \/   / |  |  |  | |   \|  ||
|  \_    _/  |  |  |  | |  |  |  |      \            /  |  |  |  | |  . `  ||
|    |  |    |  `--'  | |  `--'  |       \    /\    /   |  `--'  | |  |\   ||
|    |__|     \______/   \______/         \__/  \__/     \______/  |__| \__||
+---------------------------------------------------------------------------+
)" << std::endl;

    // Print vertical padding (after the ASCII art)
    for (int i = 0; i < verticalPadding; ++i)
    {
        std::cout << std::endl;
    }
}

void printFailMessage()
{
    const int consoleWidth = 80;
    const int artWidth = 46;
    const int consoleHeight = 25;
    const int artHeight = 12;

    int horizontalPadding = (consoleWidth - artWidth) / 2; // 17 spaces
    int verticalPadding = (consoleHeight - artHeight) / 2; // 6 blank lines

    // Print vertical padding (before the ASCII art)
    for (int i = 0; i < verticalPadding; ++i)
    {
        std::cout << std::endl;
    }

    // Print ASCII art with horizontal padding
    std::string padding(horizontalPadding, ' '); // Generate 17 spaces
    std::cout << padding << "+----------------------------------------------+\n";
    std::cout << padding << "|  _______      ___      .___  ___.  _______   |\n";
    std::cout << padding << "| /  _____|    /   \\     |   \\/   | |   ____|  |\n";
    std::cout << padding << "||  |  __     /  ^  \\    |  \\  /  | |  |__     |\n";
    std::cout << padding << "||  | |_ |   /  /_\\  \\   |  |\\/|  | |   __|    |\n";
    std::cout << padding << "||  |__| |  /  _____  \\  |  |  |  | |  |____   |\n";
    std::cout << padding << "| \\______| /__/     \\__\\ |__|  |__| |_______|  |\n";
    std::cout << padding << "|                                              |\n";
    std::cout << padding << "|  ______   ____    ____  _______ .______      |\n";
    std::cout << padding << "| /  __  \\  \\   \\  /   / |   ____||   _  \\     |\n";
    std::cout << padding << "||  |  |  |  \\   \\/   /  |  |__   |  |_)  |    |\n";
    std::cout << padding << "||  |  |  |   \\      /   |   __|  |      /     |\n";
    std::cout << padding << "||  `--'  |    \\    /    |  |____ |  |\\  \\.    |  \n";
    std::cout << padding << "| \\______/      \\__/     |_______|| _| `._|    |  \n";
    std::cout << padding << "+----------------------------------------------+\n";

    // Print vertical padding (after the ASCII art)
    for (int i = 0; i < verticalPadding; ++i)
    {
        std::cout << std::endl;
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





