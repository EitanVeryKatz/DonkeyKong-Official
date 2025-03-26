the following repository contains my mpeer's and mine final project for the c++ oop course in the degree.
I append the task specifications below.

Requirements and Guidelines

The exercises in the course would require you to implement a “donkey kong” game as a console application. You can watch the original “donkey kong” game in many videos on youtube, like for example this one.

You can read more on “donkey kong” in wikipedia, both in the English Wiki and in the Hebrew Wiki.

Environment and Submission Instructions:

The exercise should be implemented in Visual Studio 2022 or later, with standard C++ libraries and run on Windows with Console screen of standard size (80*25), using gotoxy for printing at a specific location on screen (X, Y), using _kbhit and _getch for getting input from the user without blocking, and Sleep for controlling the pace of the game.
(All the above would be explained to you during one of the next lab sessions).
Submission is in MAMA, as a single zip file containing only the code and the vcxproj and sln files + readme.txt with IDs -- but without the DEBUG folder and without any compiled artifact.

Note that you MUST provide a readme.txt file that would contain the IDs of the students submitting the exercise. Even if there is only a single submitter, you still need to put your ID in the readme.txt file. Your readme file will also list any additional bonus features you've implemented, if you'd like to request bonus points for them.

Important notes on GenAI and using external code snippets:

You may use ChatGPT or other GenAI tools, but remember that the responsibility for meeting the requirements and submitting working code is on you. Which means  that you have to carefully read and understand any piece of code that you integrate into your submission.
There are some existing C++ implementations for this project out there on the web, like for example: https://github.com/ianmurfinxyz/donkey_kong_arcade. Please note that any implementation that you find would probably not fit exactly the requirements of this exercise. Adapting existing code for the purpose of the exercise would probably be much more complicated than implementing your own code.
If you do choose to rely on an existing project that you found on the web, or from any other source, or if you rely heavily on AI generated code, you are required to add comments above any big portion of code that you didn’t write and are integrated into your project (for any snippet of 5 lines of code or more). The comment should point at the source of the code (link to the web, a brief summary of the prompt used with the AI tool to get this code, etc.). It would be emphasized again that: (a) it is valid to integrate code that you didn’t write! (b) you are still responsible for making sure the code works and fits its purpose. (c) you are required to have a clear comment indicating the origins of this code snippet. (d) slight adaptations to the code do not make it “yours”, so even if you rearrange it a bit, change variable names etc., but it is still an external code of 5 or more lines of code, you are required to add the origins comment as explained above.
The instructions above are relevant also for integrating pieces of code that you got from the lab exercise, etc. You should document that as well with a proper comment, indicating the origins of the code.


Exercise 1
In this exercise you will implement the basic “donkey kong” game for a human player.

You decide how to use the size of the screen for:
Presenting the board.
Presenting number of points, “remaining lives” information, etc.

Menu
The game shall have the following entry menu:
(1) Start a new game
(8) Present instructions and keys
(9) EXIT

When the game starts, Mario (the hero) is positioned at his start position (you should decide where it is) without any movement. Once the user selects move direction (using the keys, as listed below) Mario will continue to move in this direction even if the user doesn’t press any key, as long as game board boundaries are not reached and the “STAY” key isn’t pressed. 

Keys:

LEFT
a or A
RIGHT
d or D
UP / JUMP
w or W
Down
x or X
STAY
s or S


Game Elements and Flow
The gameboard is consisted of:
Donkey Kong, standing somewhere at the top of the gameboard (use & for that)
Barrels, thrown by “donkey kong” (use O, that is big ‘O’, for that)
Floor (the characters <, > or =, denoting floor and its direction) 
Ladder (use H)
Mario (use @)
Pauline (use $)

Donkey Kong (the &) throws barrels (the O). Barrels fall down at a certain pace (that you decide, try to make it reasonable), till they reach a floor. When a barrel reaches a floor it moves on this floor according to its direction: for < floor, it will move left, for > floor it will move right, and for = floor it will move according to its previous movement direction.

If a barrel hits Mario, the stage restarts (in exercise 1 there is only 1 stage), and Mario loses one of his three lives. If all three lives are lost, the game displays a proper message and returns to the main menu.

A ladder connects floors at different elevations. Barrels ignore ladders. Mario can climb ladders up and down (with the UP and Down keys) but can also pass a ladder without using it. To move between floor sections, the ladder should start one character above the lower floor and end one character below the upper floor. When using the UP key on a position where there isn’t a ladder, Mario would jump in the air 2 chars up, if he was in movement the jump will continue this movement, so he will land 2 chars away from the original jump position, either left or right. Mario should use ladders and jumps to avoid hitting barrels.

Both Mario and the barrels can fall, if they move beyond the floor edges. Set a reasonable pace for the fall. When a barrel hits a floor after falling 8 or more lines, it will explode and disappear. If Mario is within 2 characters of the explosion in any direction (including diagonally), he loses a life and the stage restarts. If Mario falls and hits a floor 5 or more lines below, he will also lose a life and the stage will restart.

The boundaries of the game board stop the movement of both Mario and the barrels. You can decide whether you limit the game board boundaries or just use the screen edges as they are. In case you want to control the game board boundaries, use the character Q to mark the boundaries.

Mario wins this stage (the single stage in Exercise 1) when he rescues Pauline, by reaching to her, that is stepping to the exact location of Pauline. If this was the last stage (which is always the case in Exercise 1), a proper message should appear and the game should return to the main menu.

Pausing a game
Pressing the ESC key during a game pauses the game. It can be good to present a message on screen saying: “Game paused, press ESC again to continue”. But it is not mandatory to present such a message.
When the game is at pause state, pressing ESC again would continue the game, with all moving game objects (Mario, barrels, other moving game objects in next exercises) continuing their movement exactly as it was before pausing, as if the game hadn’t paused.

Notes to be aware of:
Do not use the command ‘exit’:
Using the command exit for finishing the program is not allowed. In general using ‘exit’ is a bad sign. You should finish the program by normally finishing main.
Make sure your program does not perform unnecessary bad recursive calls. For example, if your menu calls “game.run()” for starting a game, and then the game calls “menu.run()” for presenting the menu after the game ends, this sounds like a bad recursion that should be avoided.

Bonus Points:
You may be entitled for bonus points for additional features, such as adding colors or other nice features. Note: there will not be any bonus for music or any feature that requires additional binary files to be part of your submission! Adding large required binary files to your submissions may subtract points!

Important notes for getting bonus:

If you decided to add colors (as a bonus feature) please add an option in the menu to run your game with or without colors (the default can be to use colors, but the menu shall allow a switch between Colors / No Colors) - to allow proper check of your exercise in case your color selection would not be convenient for our eyes. The game MUST work properly in the No Colors selection.

Note: If you do want to support colors, use the following way for doing that:


#include <windows.h>
...
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
std::cout << "Hello" << std::endl;

For color constants list see: Console Screen Buffers - Windows Console
See also: Colorizing text in the console with C++ - Stack Overflow 

Please note that alternative methods of coloring text suggested on the web, such as using color codes with system commands, may not always work. It is advisable to avoid these methods and, instead, use the approach mentioned above if you intend to add colors.

To get bonus points, you must indicate inside your readme.txt file the bonus additions that you implemented.

Self Decisions:
Any decision that you have to make, which does not have any clear guidance in the requirements, you can take a reasonable decision as long as it doesn’t contradict any of the requirements or make the game naive or too restricted.

In case you have a question for which you don’t have an answer and you don’t want to make an assumption or you feel the assumption might be wrong or contradicts other requirements, please ask in the Exercise Forum in Mama.

Important – Important!!!
We will explain to you in one of the next lab sessions how to use gotoxy for printing at a specific location on screen (X, Y), _kbhit and _getch for getting input from the user without blocking, and Sleep for controlling the pace of the game.
BUT, you don’t have to wait for that, you can already watch now Keren Kalif explaining that in this great video tutorial: C++ תכנות מונחה עצמים | קרן כליף | משחק הנחשים 
The proper code would be published. 



Exercise 2
In this exercise you will implement the following additions to your game:

Ghosts
The game may have “ghosts”, marked with the letter x (small ‘x’). Ghosts must be located on a floor and they wander on the floor with probability 0.95 of continuing in the same direction as their previous step, and 0.05 for changing direction. Ghosts do not fall from floors, if a ghost reaches the end of the floor it will change its direction to prevent it from falling. There can be more than one ghost on a floor, if two ghosts meet each other, they will change their directions. If Mario meets a ghost it loses a life and the stage restarts. Ghosts cannot climb ladders. 

A hammer
A hammer can be present somewhere on screen, marked with the letter p (small ‘p’). If Mario collects the hammer, by getting to it, he can then use it to destroy barrels and kill ghosts. The hammer can be placed anywhere on screen, it doesn’t move and it cannot fall, it just stays where it was located unless it is collected. You can decide if a hammer appears again when a stage restarts, or not. There can be only one hammer on each screen. Operating the hammer by Mario is done with the key ‘p’ or ‘P’. To destroy a barrel or kill a ghost, press it just before Mario reaches their position. Pressing it after Mario overlaps them is too late. The hammer works in the direction Mario is moving to, but he can change his direction and use the hammer in the same step. If you press the key for changing direction before, the hammer will work in the new direction. When Mario owns a hammer you should indicate that either with a proper hint on Mario representation or with a hint in the legend, or both.

Loading Screens from files
The game would look for files in the working directory, with the names dkong_*.screen these files would be loaded in lexicographical order (i.e. dkong_a.screen before dkong_b.screen or dkong_01.screen before dkong_02.screen etc.). The files are text files (NOT binary files).

You MUST submit 3 screens with your exercise!

If there are no files, a proper message would be presented when trying to start a new game.
The menu should have a new option to allow running a specific screen, by name.
The screen file should be a text file representing the screen, with the characters:


Q
A “wall”, indicating the boundaries of the game. It is not mandatory that the file will have any Q, in which case the board boundaries are equal to the screen boundaries. But you must support getting Q.
&
Donkey Kong
@
Mario
$
Pauline
=, <, >
floors, indicating the movement directions for barrels
H
Ladder
x
Ghost
p
Hammer
L
Indicating the legend top-left position, where Score and Remaining Live information shall be presented. It is the responsibility of the screen designer (not of your program) to make sure that the L is placed in a position not accessible by the game creatures. You may assume that the screen designer follows this instruction. The size of the actual printed legend shall be not more than 3 lines height * 20 characters.

Note that the above chars are mandatory, even if you use other chars for drawing the board on screen (which is valid).

Moving to the next stage (next screen) doesn’t gain lives, Mario continues with the remaining lives that he had.

Score
Add score to your game. You should decide about the score formula, you can decide that destroying ghosts and killing ghosts gains score, you can also decide that the score relates to the time it took Mario to rescue Pauline in each stage.

Note
You should change your original code, to use new materials that we learned - where appropriate.





Exercise 3
In this exercise you will implement an option to run a game from files and to record a game into files, mainly for testing. This would work as following:
There would be a text file with a list of steps for all game objects, per screen in a structure of your choice. The structure shall be concise, i.e. shall include only information that cannot be deduced from previous file info and the game rules. Do not add to the file information that can be deduced from previous data in file, for example there isn’t a need to save into the file all Mario’s positions, only the change of directions and other steps that cannot be deduced. It is important to save each “step” with a “time” so it can be reproduced exactly as it happened. If the barrels appear in a deterministic pace there is no need to save this to file, however if they appear in a random pace, then you should save their appearance.
Name of file shall be in the format corresponding the screen name: dkong_*.steps (e.g. dkong_01.steps for dkong_01.screen)
There would be a file with the expected result for the screens, in the format corresponding to the screen name: dkong_*.result (e.g. dkong_01.result), the file shall include the following information:
points of time* for this screen where Mario lost a live (if any)
point of time* for this screen where Mario finished the screen (if finished)
score gained for this screen

* point of time = game’s time counter, not actual time, each iteration can be counted as “1 time point”

You have the freedom to decide on the exact format of the files but without changing the above info or adding unnecessary additional info.

You should provide at least 3 examples, with the steps and results files (thus 9 files overall: screen, steps, results * 3 screens).
Keep Mario alive till the 3rd screen, you can decide whether he finishes the 3rd screen successfully or not. You should also add a dedicated readme file called file_format.txt explaining your file formats, to allow creation of new files or update of existing files.

The game shall be able to load and save your files!
All files shall be retrieved / saved from /to the current working directory.

Running the option for loading or saving game files would be done from the command line with the following parameters:

dkong.exe -load|-save [-silent]


The -load/-save option is for deciding whether the run is for saving files while playing (based on user input) or for loading files and playing the game from the files (ignoring any user input).
In the -load mode there is NO menu, just run the loaded game as is, and finish! Also you should ignore any user input, including ESC - there is no support for ESC in load mode!
In the -save mode there is a menu and the game is the same as in Ex2, except that files are saved. Note that each new game overrides the files of the previous game, i.e. we always keep the last game saved (you can always take the files and copy them to another folder manually if you wish).

The -silent option is relevant only for load, if it is provided in save mode you should ignore it, if it is provided in load mode, then the game shall run without printing to screen and just testing that the actual result corresponds to the expected result, with a proper output to screen (test passed or failed, and if failed - what failed). In silent mode you should avoid any unnecessary sleep, the game should run as fast as possible. Without -silent, the loaded game would be presented to screen, with some smaller sleep values than in a regular game.

Note: you should still support running your game in “simple” mode, without any command line parameters, as in Ex2:  dkong.exe 
In which case it will not save or load files and would behave as in Ex2 (except for the other addition of Ex3 below).

Ghosts that can climb ladders
In this exercise you should also add ghosts that can climb ladders. Those would be denoted in the file with X (and can be presented on screen in any way that you wish, as long as they are distinguished from the regular, non-climbing ghosts). You can decide what would be the behavior of the climbing ghosts. You can request a bonus for sophisticated behaviors like using an algorithm that tries to hunt Mario.
