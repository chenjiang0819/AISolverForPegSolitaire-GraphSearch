# AISolverForPegSolitaire-GraphSearch

You can play the game with the keyboard by executing:  
./pegsol (level)  
where *level* ∈ {0, . . . , 8} for standard levels.  
  
In order to execute the AI solver use the following command:  
./pegsol (level) AI (budget) play solution  
Where *AI* calls the algorithm; *play solution* is optional, if typed in as an argument, the program will play the solution found by the algorithm once it finishes; *(budget)* is an integer number indicating the budget of the search.  
For example:  
./pegsol 5 AI 1200000 play solution  
Will run the 6th layout expanding maximum 1.2M nodes and will play the soltution found.  
