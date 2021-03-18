# Requirement
* Visual Studio 2019 (as of this writing)

# Script Information
* [glow-and-flashbang](glow-and-flashbang): Everyone glows through walls and player is unaffected by flashbang.
* [trigger-aim-me](trigger-aim-me): Aims at enemy heads and automatically shoots whenever the cursor scans an enemy.
* [hazedumper-master](hazedumper-master): Gets the latest offsets from every patch and updates of the game.

---
## How To Use
1. Create a new project in Visual Studio 2019 (as of this writing) and select *Empty Project*
2. Select either [glow-and-flashbang] or [trigger-aim-me] from this repo.
3. In the *Solution Explorer*, add those files by *right-clicking > Add > Add Existing Item*. Repeat untill all the files are added.
4. Select *Project > Properties*.
5. On the left pane, select *Configuration Properties > Advanced*, change *Character Set* from *Unicode* to *Multi-Byte*
6. Build the solution and then run "Local Windows Debugger"

## Hotkeys
### [glow-and-flashbang](glow-and-flashbang)
| Hotkey        | Description           |
| ------------- | --------------------- |
| 9             | Toggle glow           |
| 0             | Toggle anti-flashbang |

### [trigger-aim-me](trigger-aim-me)
| Hotkey        | Description                                 |
| ------------- | ------------------------------------------- |
| F2            | Toggle autoshoot when cursor scans an enemy |
| Left Alt      | Toggle triggerbot                           |

---
## Additional Notes
* CS:GO must be running before executing "Local Windows Debugger".
* For [trigger-aim-me](trigger-aim-me) to work properly, disable raw mouse input.
* [glow-and-flashbang](glow-and-flashbang) can run alongside [trigger-aim-me](trigger-aim-me) and vice versa. To do this, both VS Solutions must run independently while CS:GO is running.
* Run [hazedumper-master](hazedumper-master) for every CS:GO patches to pull new offsets, it will extract a new *csgo.hpp*. Paste this file inside the directories of the scripts to replace the outdated offsets.

---
# Author Notes - 19-March-2021
Scripts maintained only during leisure hours. I am not responsible if your Steam account gets reported and/or banned. Enjoy at your own risk.
