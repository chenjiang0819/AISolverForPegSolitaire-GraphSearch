# Peg Solitaire Graph Search Solver

A C console peg-solitaire game with a handwritten depth-first graph-search extension, rotational duplicate-state detection, bounded expansion, and solution-path reconstruction.

Chen Jiang’s University of Melbourne computing coursework.

University: University of Melbourne  

## Implementation

Explicit search nodes, stack-based expansion, parent-linked solution reconstruction, board-state duplicate detection across rotations, and bounded-search statistics.

## Technical approach

The original DFS frontier remains an explicit array stack, with per-slot ownership chains retaining popped nodes until search cleanup. The preserved transition functions are tested by replaying every recorded move against the preceding board.

The hash table remains the attributed implementation. Bounded expansion and best partial solutions are retained; the initial table is smaller and continues to grow through its existing mechanism.

## Run

Run `make`; use `./pegsol 0 AI 100` for bounded search or `./pegsol 0` for the original keyboard game. `play_solution` and legacy `play solution` are supported. Run `make test` and `make sanitize`.

## Checks and results

- Apple Clang 21: normal -O2 build and regression suite passed.
- AddressSanitizer + UndefinedBehaviorSanitizer regression suite passed on macOS.
- GCC 14.3 in a network-disabled Linux container: strict -Werror sanitizer checks passed, including LeakSanitizer defaults.
- make test: C core harness plus two CLI methods passed; all nine layouts tested with bounded budgets.
- Core checks cover terminal/impossible boards, rotation round trips, solution replay, repeat searches, full-stack cleanup, and hash growth.
- Strict Clang -O0 -Werror core build and checks passed.

## 2026 maintenance

- Validated layouts/budgets/options and handled noninteractive EOF safely.
- Defined all action return paths, guarded invalid coordinates/moves, and provided complete layout-string storage.
- Made global ownership explicit for portable linking; bounded and reset stack cleanup, including exhausted/repeated searches.
- Hardened hash allocation failure paths and added transition/replay/hash-growth/CLI regression coverage.
- Excluded the generated executable from tracking; its original version remains preserved.

These changes are 2026 AI-assisted maintenance of the original student implementation.

## Usage notes

- Search is exponential; a finite budget may return a best partial solution rather than a solved board.
- Interactive terminal key mapping and animation deserve manual checks on the intended terminal.
- Allocation-failure handling was reviewed but not exhaustively fault-injected.

## Original project notes

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
