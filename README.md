# SassySpecter: AI Bot for StarCraft: Brood War and StarCraft II

[![License: GNU GPL v3](https://img.shields.io/badge/License-GNU_GPL_v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0.en.html)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

SassySpecter is a fork of [CommandCenter](https://github.com/davechurchill/commandcenter).
The  goal is  to have  a  bot able  to play  the  3 races  from the  2
StarCraft games,  with the same  code (modulo API-specific  parts), by
using   massively   the    Constraint   Programmaing   toolkit   [GHOST](https://github.com/richoux/GHOST) for decision-making. 

## Kickstarter: where to get SC1&2 and their APIs?

### Games
<!-- * You need StarCraft : Brood War version 1.16.1. You won't be able to have it through Battle.net now. You can download the [right version provided by ICCup](http://files.theabyss.ru/sc/starcraft.zip) (chill out, everything is legal here). -->
* You need StarCraft : Brood War version 1.16.1. You won't be able to have it through Battle.net now. You can download the [right version provided by ICCup](https://www.richoux.fr/files/starcraft.zip) (chill out, everything is legal here).
* You can download [StarCraft II](https://www.blizzard.com/en-us/download/confirmation?platform=windows&locale=en_US&version=LIVE&id=sc2) for free.
  
### APIs
* SassySpecter uses [BWAPI v4.4.0](https://github.com/bwapi/bwapi/releases/tag/v4.4.0).
* [Precompiled libs](http://blzdistsc2-a.akamaihd.net/SC2API_Binary_vs2017.zip) for
  SC2 API is a nice option.

## Developer Install / Compile Instructions (Windows)
* Download and install [Visual Studio](https://www.visualstudio.com/downloads/). Make sure to
  select  the  **Visual  Studio  2017 compiler  (MSVC  v141)**  during
  installation. If you missed it, you can always install it afterwise
  by launching again the vs_community.exe file.
* Clone this git repository to a folder on your PC
* Open "SassySpecter/vs/SassySpecter.sln" in VS
* If you compile the SassySpecter project with the x64 Platform, it will compile the SC2 bot
* If you compile the SassySpecter project with the x86 or Win32 Platform, it will compile the BW bot
* Set the VS Project include and lib folders to point to the directories
  * Right click the SassySpecter project in VS
  * Select "Properties"
  * Select the correct configuration that you want to build in the top left ("Release" or "Debug")
  * Select the target platform you want to build (x64 = SC2, Win32 = BW)
  * Select "VC++ Directories" on the left
  * Select the "Include Directories" option in the table on the right
  * Click the dropdown arrow on the right and click Edit...
  * Modify the existing directory entry to point to your (SC2API|BWAPI)/include directory
  * Select the "Library Directories" option in the table on the right
  * Click the dropdown arrow on the right and click Edit...
  * Modify the existing directory entry to point to your (SC2API|BWAPI)/lib directory
* From the "Build" menu, click "Build Solution"
* The binary "SassySpecter_{SC1/SC2}.exe" should appear in the SassySpecter/bin/ directory
* Run the SassySpecter bot by either:
  * Double clicking the executable in the SassySpecter/bin/ directory
  * Running the program from the console
  * Click "Local Windows Debugger" in VS to launch the program from within VS. To do this, you need to set the "Working Directory" option under "Debugging" to "$(ProjectDir)/../bin/" (I don't know why this option won't save)
* If you are running the BW version of the bot, you must then start BW via Chaoslauncher with BWAPI injected
* The SassySpecter/bin/BotConfig.txt file must be in the same directory as the .exe to run properly

## CommandCenter

CommandCenter  is a  StarCraft AI  bot that  can play  both StarCraft:
Broodwar and StarCraft 2 written by David Churchill (https://github.com/davechurchill/commandcenter).

![CommandCenter Screenshot](https://i.imgur.com/SbTymsO.jpg)

CommandCenter is written in C++ using [BWAPI](https://github.com/bwapi/bwapi) and Blizzard's [StarCraft II AI API](https://github.com/Blizzard/s2client-api). It provides many wrapper functions around both APIs that allow it to perform the same functionality in both games via the same source code. It is written by [David Churchill](http://www.cs.mun.ca/~dchurchill/), Assistant Professor of [Computer Science](https://www.cs.mun.ca/) at Memorial University, and organizer of the [AIIDE StarCraft AI Competition](http://www.cs.mun.ca/~dchurchill/starcraftaicomp/).

CommandCenter is based on the architecture of [UAlbertaBot](https://github.com/davechurchill/ualbertabot/wiki), and is intended to be an easy to use architecture for you to quickly modify, play with, and build your own bot. The bot itself does not contain much in the way of hard-coded strategy or tactics, however it provides a good starting point for you to implement your own strategies for any race. 

CommandCenter currently provides the following features:
* Plays both Starcraft games with the same source code
* Plays all 3 races with generalized micro controllers for combat units
* Performs online map analysis, extracting information such as base locations and expansions
* Keeps track of all previously seen enemy units and their last known locations on the map
* Has a WorkerManager which manages resource gathering and worker allocation / buiding
* Is able to carry out predefined build-orders written in a configuration file
* Allows you to easily create your own build-orders and modify them on the fly in-game
* Contains a building placement algorithm, finding the closest buildable location to a given position for a given building 
* Scouts the map with a worker unit, discovering where the enemy base is located
* Once a specific condition has been reached (having 12 combat units, by default), it will commence an attack, sending waves of units at the enemy base
* Squads can be formed, consisting of multiple units following a specific order such as attack or defend a given location

The bot only plays 1v1, and will have undefined behavior / crash if played against multiple enemies or on teams
