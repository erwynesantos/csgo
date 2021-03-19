# <div align="center"> Counter-Strike: Global Offensive </div>
<p align="center"> <img src="https://i.ibb.co/TLB5Hk4/4ce9e1f2403bc1a13118ab2e2dda6d47-1-1-30.jpg"> </p>

## Requirement
* Visual Studio 2019 (as of this writing)

## Script Information
* [glow-and-flashbang](glow-and-flashbang): Everyone glows through walls and player is unaffected by flashbang.
* [trigger-aim-me](trigger-aim-me): Aims at enemy heads and automatically shoots whenever the cursor scans an enemy.
* [hazedumper-master](hazedumper-master): Gets the latest offsets from every patch and updates of the game.

---
## Building the Script
1. Create a new project in Visual Studio 2019 (as of this writing) and select `Empty Project`
2. Select either [glow-and-flashbang](glow-and-flashbang) or [trigger-aim-me](trigger-aim-me) from this repo.
3. In the `Solution Explorer`, add those files by `right-clicking` > `Add` > `Add Existing Item`. Repeat untill all the files are added.
4. Select `Project > Properties`.
5. On the left pane, select `Configuration Properties` > `Advanced` > change `Character Set` from `Unicode` to `Multi-Byte`.

## Usage
1. Run CS:GO
2. In the previously built solution, run it by hitting ![image](https://i.ibb.co/8cv7L6h/Capture.png "Local Windows Debugger")

## Hotkeys
### [glow-and-flashbang](glow-and-flashbang)
| Hotkey        | Description           |
| ------------- | --------------------- |
| <kbd>0</kbd>  | Toggle glow           |
| <kbd>9</kbd>  | Toggle anti-flashbang |

### [trigger-aim-me](trigger-aim-me)
| Hotkey                | Description                                 |
| -------------         | ------------------------------------------- |
| <kbd>F2</kbd>         | Toggle autoshoot when cursor scans an enemy |
| Left <kbd>Alt</kbd>   | Toggle triggerbot                           |

---
## Additional Notes
* CS:GO must be running before executing "Local Windows Debugger".
* For [trigger-aim-me](trigger-aim-me) to work properly, disable raw mouse input.
* [glow-and-flashbang](glow-and-flashbang) can run alongside [trigger-aim-me](trigger-aim-me) and vice versa. To do this, both VS Solutions must run independently while CS:GO is running.
* Run [hazedumper-master](hazedumper-master) for every CS:GO patches to pull new offsets, it will extract a new *csgo.hpp*. Paste this file inside the directories of the scripts to replace the outdated offsets.

---
# Author Notes ![[date](https://img.shields.io/badge/Date-19%20Mar%202021-orange)](https://github.com/erwynesantos/csgo)
Scripts maintained only during leisure hours. I am not responsible if your Steam account gets reported and/or banned. Enjoy at your own risk.
