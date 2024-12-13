#include "gameConfig.h"

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



