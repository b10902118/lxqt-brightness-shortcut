# lxqt-brightness-shortcut
lxqt backlight adjustment program with popup indicator \
## Dependency: 
xbacklight, dbus-python (Python), libnotify (C)

## Demo

![](https://github.com/b10902118/lxqt-brightness-shortcut/blob/main/demo.gif)

## Installation
### Python3 version (recommended)
Run ```install.sh``` and follow the instruction

### C version
1. Open brightness.c and check whether the paths in the macros points to a file. If not, find your backlight files (probably under /sys/class/backlight/) and change the macros to their path.
2. ```make``` will create a executable called ```release``` 
3. Add shortcuts with command \
```path/to/executable dec``` for decrement \
```path/to/executable inc``` for increment \
in Preferences->LXQt Settings->Shortcut Keys

In my case:
![](https://i.imgur.com/F1fgYO6.png)

