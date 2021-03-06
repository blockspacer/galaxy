# galaxy
[![Build Status](https://ci.appveyor.com/api/projects/status/ac0ec6gtxl7776y5?svg=true)](https://ci.appveyor.com/project/reworks/galaxy)
[![Documentation Status](https://travis-ci.org/DomRe/galaxy.svg?branch=master)](https://domre.github.io/galaxy/)
[![Apache 2.0 Licensed](https://img.shields.io/badge/license-apache-blue.svg)](./LICENSE.txt)

Game programming framework built on C++17 using SFML, Lua and JSON. This was built as a hobby for hobby projects.

## Building
### Windows:
```
git clone --recursive https://github.com/DomRe/galaxy.git
type PATCH.txt >> modules/imgui/imconfig.h
msbuild galaxy.sln
```

### Unix:
```
// todo
```

If your submodules did not clone properly run:
```
git submodule update --init --recursive
```

## Documentation
See [documentation](https://domre.github.io/galaxy/).  

## Features
- Uses Modern C++, including C++17 features.
- [ImGui](https://github.com/ocornut/imgui) for making and using debugging and utility UI.
- [sol3](https://github.com/ThePhD/sol2) for [Lua](https://www.lua.org/) integration.
- Built on top of --

### Credits
* [doxygen-dark-theme](https://github.com/MaJerle/doxygen-dark-theme).
* [sercode.ttf](http://www.dafont.com/secret-code.font).

Any included libraries should have a LICENSE file associated.

Resources used in sandbox demo:
Various from opengameart.org. No copyright infringement intended.