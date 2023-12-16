# XO-game

Hombrew Tic-tac-toe for 3ds

## TO DO:
1. Change drawing to image
1. Sound effects
1. Save statistics
1. Multiplayer

## How to build:
1. Install devkitPro for 3ds
1. Install makerom
1. Clone this repo
1. Run `make && ./makerom -f cia -o XO-game.cia -rsf cia.rsf -target t -exefslogo -elf XO-game.elf -icon icon.smdh` in repo directory
1. Install cia file on your 3ds

## Known bugs:
1. No icon, banner and music in home menu
