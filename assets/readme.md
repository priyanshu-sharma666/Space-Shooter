# C++ Space Shooter Game

A modular, 2D top-down space arcade shooter built using C++ and the SFML (Simple and Fast Multimedia Library) graphics framework. 

Defend yourself against waves of randomly spawning enemies, track your high score, and manage your ship's shield/HP before it's Game Over!


## Project Structure & Assets
The repository contains both the modular C++ source code and the necessary visual/audio assets required to run the game:

### Source Code:
* `main.cpp` - Entry point that initializes and launches the core game runtime execution loop.
* `Game.h` / `Game.cpp` - Controls projectile updates, enemy spawning mechanics, collision checks, score calculations, and global asset management.
* `Player.h` / `Player.cpp` - Manages the player's 2D keyboard movement tracking, screen boundary lock limits, hitpoints, and flash damage states.

### Assets (Must be kept in the root directory next to your executable):
* `TTD Compadre-Regular.otf` - The custom font file used to render the live scoreboard and the Game Over screen text.
* `ship.png` - The player's spaceship texture asset.
* `enemy.png` - The enemy alien/spaceship sprite texture asset.


## Project Features
* **Modular Codebase:** Clean Object-Oriented design separating the main loop (`Game`) from the actor controls (`Player`).
* **Sprite Assets:** Custom textured rendering for the player ship and hostile targets.
* **Physics & Collisions:** Real-time boundary checking, automated projectile tracking, and precise bounding-box intersection handling.
* **Dynamic UI:** Real-time rendering of your current numeric Score, live HP readout, and a structural green health bar overlay.
* **Visual Polish:** Implements a timed dynamic red flash effect on the player's sprite whenever damage is taken.

## Project Structure
* `main.cpp` - Entry point that initializes and launches the core game runtime execution loop.
* `Game.h` / `Game.cpp` - Controls projectile updates, enemy spawning mechanics, collision checks, score calculations, and global asset management.
* `Player.h` / `Player.cpp` - Manages the player's 2D keyboard movement tracking, screen boundary lock limits, hitpoints, and flash damage states.

## Prerequisites
To compile or test this project locally, you need:
* A C++ compiler supporting **C++17** or higher.
* **SFML 2.6.2** installed and configured on your machine.
* Visual Studio Code with the C/C++ extension pack installed.

## Build and Run Configuration

This project is built using VS Code and GCC/MinGW. Follow these steps to compile and run the game on Windows.

### 1. Configure Compiler Paths
This workspace comes with a pre-configured `.vscode/tasks.json` template file. Open it and ensure that the paths for `-I` (Include directory) and `-L` (Lib directory) match where you have SFML installed on your local machine:
* `"C:/SFML-2.6.2/include"`   
* `"C:/SFML-2.6.2/lib"`
*(Note: These paths will vary depending on your personal installation directory).*

### 2. Building the Project
1. Open the project folder inside VS Code.
2. Press `Ctrl + Shift + B` to trigger the compilation task script.
3. This will compile all modular `.cpp` files together and generate a standalone `main.exe` executable inside your workspace.

### 3. Required DLL Files (CRITICAL)
Before launching `main.exe`, you **must copy the required SFML DLL files** into the exact same folder directory where your newly generated `main.exe` sits. If skipped, Windows will throw a missing `.dll` launch system error.

Go to your local installation directory (`SFML-2.6.2/bin/`) and copy these **3 DLL files** into your project directory:
* `sfml-graphics-2.dll`
* `sfml-window-2.dll`
* `sfml-system-2.dll`

### 4. Run the Game
Ensure your assets (`ship.png`, `enemy.png`, and `TTD Compadre-Regular.otf`) are in the root directory alongside your `main.exe`. Then simply double-click `main.exe` to play!
(download the font from any publically available website)

## Controls
* `W` / `A` / `S` / `D` - Move your Spaceship up, left, down, and right.
* `Left Mouse Click` - Fire laser projectiles.
* `R` - Restart the game once you encounter a Game Over screen.
