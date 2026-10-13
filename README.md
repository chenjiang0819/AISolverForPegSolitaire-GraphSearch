# Peg Solitaire Graph Search Solver

## Overview

A C console peg-solitaire game with a handwritten depth-first graph-search extension, rotational duplicate-state detection, bounded expansion, and solution-path reconstruction.

## Original Context

Chen Jiang’s search extension builds on the attributed game by Maurits van der Schee and the attributed goldsborough hash-table implementation; those credits are retained. The preserved pre-maintenance snapshot is `070d9f647b55cb7e2ac1cd861c059712313319e9`;
its most recent original commit is dated 2024-05-27. This date describes Git evidence,
not necessarily the complete implementation period.

## What I Implemented

Explicit search nodes, stack-based expansion, parent-linked solution reconstruction, board-state duplicate detection across rotations, and bounded-search statistics.

## Technical Approach

The original DFS frontier remains an explicit array stack, with per-slot ownership chains retaining popped nodes until search cleanup. The preserved transition functions are tested by replaying every recorded move against the preceding board.

The hash table remains the attributed implementation. Bounded expansion and best partial solutions are retained; the initial table is smaller and continues to grow through its existing mechanism.

## Build / Run

Run `make`; use `./pegsol 0 AI 100` for bounded search or `./pegsol 0` for the original keyboard game. `play_solution` and legacy `play solution` are supported. Run `make test` and `make sanitize`.

## Testing

- Apple Clang 21: normal -O2 build and regression suite passed.
- AddressSanitizer + UndefinedBehaviorSanitizer regression suite passed on macOS.
- GCC 14.3 in a network-disabled Linux container: strict -Werror sanitizer checks passed, including LeakSanitizer defaults.
- Critical make test checks are rerun on the merged default branch before pushing it.
- make test: C core harness plus two CLI methods passed; all nine layouts tested with bounded budgets.
- Core checks cover terminal/impossible boards, rotation round trips, solution replay, repeat searches, full-stack cleanup, and hash growth.
- Strict Clang -O0 -Werror core build and checks passed.
- Evidence: peg_core_before.log, peg_after_tests.log, peg_O0_tests.log, peg_linux_tests.log.

## 2026 Maintenance

- Validated layouts/budgets/options and handled noninteractive EOF safely.
- Defined all action return paths, guarded invalid coordinates/moves, and provided complete layout-string storage.
- Made global ownership explicit for portable linking; bounded and reset stack cleanup, including exhausted/repeated searches.
- Hardened hash allocation failure paths and added transition/replay/hash-growth/CLI regression coverage.
- Excluded the generated executable from tracking; its original version remains preserved.

The later work is AI-assisted maintenance, separate from the original implementation.
The exact original snapshot remains on `archive/handwritten-original`.
See [AI_PROJECT_REVIEW.md](AI_PROJECT_REVIEW.md) for a technical review.

## Known Limitations

- Search is exponential; a finite budget may return a best partial solution rather than a solved board.
- Interactive terminal key mapping and animation deserve manual checks on the intended terminal.
- Allocation-failure handling was reviewed but not exhaustively fault-injected.

## Original Assignment Notes

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
