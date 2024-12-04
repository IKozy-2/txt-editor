# kri
<!--[![C/C++ CI](https://github.com/ikozyris/kri/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/ikozyris/kri/actions/workflows/c-cpp.yml)-->
A simple, compact and *fast* text editor using ncurses and a gap buffer, written in C++, in ~1.3k lines of code.
More information is available on the [wiki](https://github.com/ikozyris/kri/wiki).

![A C++ file in kri](https://github.com/ikozyris/kri/assets/80053394/8fa12952-272f-41e0-9535-0a77f3652286)

## Build
```sh
make build
sudo make install
```

Or use the user-friendly dialog utility `wizard.sh`
which also supports configuring kri

## Usage
```sh
kri text.txt # open existing file or create if it doesn't exist
kri --help # show help page
kri # ask for filename on save file operation
```

### Keybindings
* Save: Ctrl-S
* Exit: Ctrl-X
* Go to start of line: Ctrl-A
* Go to end of line: Ctrl-E
* Open other file Alt-R
* Go to previous/next word: Shift + Left/Right arrow
* Enter built-in terminal: Alt-C
* Show info: Alt-I (also command _stats_ in built-in terminal)

### How fast is it?
kri is several times faster than any other text editor at reading files and other operations.
See the [benchmarks](https://github.com/ikozyris/kri/wiki/Performance-&-Benchmarks) for more.

### License

Copyright (C) 2022-2024  ikozyris

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

