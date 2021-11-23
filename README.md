<p align="center"><img alt="logo" src="https://github.com/williamniemiec/PokeMaze/blob/master/docs/img/logo/logo.png?raw=true" /></p>

<h1 align='center'>PokeMaze</h1>
<p align='center'>Maze game with Pokémon theme.</p>
<p align="center">
	<a href="https://github.com/williamniemiec/PokeMaze/actions/workflows/windows.yml"><img src="https://github.com/williamniemiec/PokeMaze/actions/workflows/windows.yml/badge.svg" alt="Windows build"></a>
	<a href="https://docs.microsoft.com/en-us/cpp/"><img src="https://img.shields.io/badge/C++-17+-D0008F.svg" alt="Cpp compatibility"></a>
	<a href="https://github.com/williamniemiec/PokeMaze/blob/master/LICENSE"><img src="https://img.shields.io/badge/License-BSD0-919191.svg" alt="License"></a>
	<a href="https://github.com/williamniemiec/PokeMaze/releases"><img src="https://img.shields.io/github/v/release/williamniemiec/PokeMaze" alt="Release"></a>
</p>
<hr />

## ❇ Introduction
Simple Pokémon themed maze game. The goal is to get the Pokéball. To do this, the player must first find the pikachu to clear the way to the Pokéball. Charizard (dragon) indicates where the Pokéball is.

## ✔ Requirements
- Operating system: Ubuntu
- GLFW
- libpng
- SDL
- [SFML library](https://www.sfml-dev.org/download.php)
- [CMake](https://cmake.org/)

## Environment

#### Ubuntu
> sudo apt-get install libsfml-dev

> sudo apt-get install libsdl-image1.2-dev

> sudo apt-get install libsdl-dev

> sudo apt-get install libpng-dev

#### Run

1. `cmake -G "Unix Makefiles"`
2. `make`
3. `./bin/pokemaze`

## 🎮 Controls
|        Command        |Description|
|----------------|-------------------------------|
| `w` | Move up |
| `a` | Move left |
| `s` | Move down |
| `d` | Move right |
| `p`| Perspective projection |
| `o`| Parallel projection |
| `c` | Free camera mode |
| `ESC` | Pause / Continue game |
| `Left mouse button` pressed + `direction`  | Moves player camera to `direction` |

## 🖼 Gallery

![gif1](https://github.com/williamniemiec/PokeMaze/blob/master/docs/gif/gif1.gif?raw=true)

![gif2](https://github.com/williamniemiec/PokeMaze/blob/master/docs/gif/gif2.gif?raw=true)

![gif3](https://github.com/williamniemiec/PokeMaze/blob/master/docs/gif/gif3.gif?raw=true)

![gif4](https://github.com/williamniemiec/PokeMaze/blob/master/docs/gif/gif4.gif?raw=true)

## 🚩 Changelog
Details about each version are documented in the [releases section](https://github.com/williamniemiec/PokeMaze/releases).

## 🤝 Contribute!
See the documentation on how you can contribute to the project [here](https://github.com/williamniemiec/PokeMaze/blob/master/CONTRIBUTING.md).

## 📁 Files

### /
|        Name        |Type|Description|
|----------------|-------------------------------|-----------------------------|
|data |`Directory`|Application resources (objects, textures...)|
|dist |`Directory`|Released versions|
|docs |`Directory`|Documentation files|
|include   |`Directory`| Class definitions  |
|lib   |`Directory`|Libraries the project uses   |
|media   |`Directory`|Application multimedia   |
|src     |`Directory`| Application source files|
|test|`Directory`|Application test files  |
