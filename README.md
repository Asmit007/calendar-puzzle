# Daily Calendar Puzzle
Daily Calendar Puzzle combines the challenge of fitting pieces into a frame with the functionality of a calendar. 


#### Components:  
The puzzle includes a wooden frame with various colored, Tetris-like pieces and two slots that reveal the month and the day.

#### Objective: 
Each day, you change the pieces around so that the slots display the current month and date.

#### Challenge:  
The pieces need to be arranged in such a way that they fit perfectly into the frame while also revealing the correct date.

<img width="300" alt="Screenshot 2024-07-01 at 10 52 22 PM" src="https://github.com/Asmit007/calendar-puzzle/assets/42831147/560af490-d1cd-4338-9cd8-f5fdf5cba984" style="border: 2px solid black;">
<img width="300" alt="Screenshot 2024-07-01 at 10 50 48 PM" src="https://github.com/Asmit007/calendar-puzzle/assets/42831147/7cc1a4f8-f5a8-4ba7-a6e5-5690f66848b9">
<img width="300" alt="Screenshot 2024-07-01 at 10 51 50 PM" src="https://github.com/Asmit007/calendar-puzzle/assets/42831147/c328bd59-d999-4dd5-9c06-24e4fd19e86f">


# How it works:

This C++ program solves the puzzle using backtracking and bitmasking. The puzzle consists of 8 pieces, each with multiple variations achieved through rotation and inversion. Here’s a breakdown of the key components:

#### Piece Class:
Each piece can be rotated clockwise up to 4 times and inverted, resulting in a total of 8 possible orientations per piece.

#### Board Class: 
Manages a 10x10 board where pieces need to be placed. It uses a bitmask to track which pieces have been placed, ensuring each piece is used exactly once.

#### Backtracking Approach:
The Solve function recursively attempts to place pieces on the board. It checks all possible orientations of each piece at each position, backtracking when a solution is not feasible.

#### Bitmasking:
Utilized to keep track of which pieces have been placed on the board efficiently. Each bit in the bitmask represents whether a corresponding piece has been used.

#### Optimization:
Before moving to the next row, the program checks if the current row is fully filled. If so, it advances to the next row, reducing unnecessary computations and improving efficiency.

#### Terminal Coloring:
Provides visual feedback in the terminal using ANSI escape codes to differentiate between pieces and important board elements.


# How to run:
1. Go into the same directory in which the calendar_puzzle.cpp file is present
2. Run `g++ -std=c++17 -o output calendar_puzzle.cpp && ./output`
3. Output examples:
   
#### 29th Oct:
<img width="688" alt="Screenshot 2024-07-01 at 11 42 35 PM" src="https://github.com/Asmit007/calendar-puzzle/assets/42831147/feaf0e5f-0510-47ca-8add-a4d2e28855c7">


#### 19th Aug:
<img width="688" alt="Screenshot 2024-07-01 at 11 41 38 PM" src="https://github.com/Asmit007/calendar-puzzle/assets/42831147/5ecf665b-6638-4cdf-994b-3250e5c832cf">


#### 1st Nov:
<img width="688" alt="Screenshot 2024-07-01 at 11 40 36 PM" src="https://github.com/Asmit007/calendar-puzzle/assets/42831147/6a1c7fbe-606a-4036-96d6-76d434b54280">



