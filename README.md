# CEUL
An open-source, lightweight, fast and practical C-like programming language, with a simple syntax and a lightweight standard library.
## What is "CEUL"?
CEUL stands for **Computationally Efficient Universal Language**, which is a programming language written entirely in C designed to be fast, simple and lightweight for programmers of all skill levels.
> Currently, CEUL is still in early development, so most of its features, like the syntax, are subject to change:
```
CEUL v0.0.2
> write "Hello, world!"
Hello, world!
```
## Installation
### Windows
Download the official `.exe` file from the [Official Releases Page](https://github.com/DaviAlmada-MensaBrasilJB/ceul/releases)
### Linux / WSL2
Download the official Linux release from the [Official Releases Page](https://github.com/DaviAlmada-MensaBrasilJB/ceul/releases)
### macOS and Unix-based systems
In order to install and use the CLI follow these steps:
1. Make sure you have the GCC compiler installed on your machine.
2. Download the [source code](https://github.com/DaviAlmada-MensaBrasilJB/ceul/archive/refs/tags/Windows.zip).
3. Run these commands in order to:  
#### Compile:
```
gcc src/main.c -o build/main
```
#### Execute:
```
./build/main
```
## Available commands
### Write
Works like `print()`. Outputs a string of text.
#### Args:
```
> write <string of text(surrounded by quotes)>
```
#### Example:
```
> write "Hello"
Hello
```
### Clear
Clears the terminal.
#### Use:
```
> clear
```
### Exit
Terminates the CEUL interpreter without closing the terminal.
#### Use:
```
> exit
```
### Loop
Executes a command multiple times with a `for` loop.
#### Args:
```
> loop <start INT> <end INT> <step INT> <command>
```
#### Example:
```
> loop 0 10 1 write "Hello"
Hello
Hello
...
```
## Implemented
- [x] Strings
- [x] CLI
- [x] `write`
- [x] `exit`
- [x] `clear`
- [x] `loop`
- [ ] While and Do While loops
- [ ] Variables
- [ ] Arithmetic operations
- [ ] Conditions
- [ ] Functions
- [ ] Libraries
## Code examples (Goal)
### Hello, world!
```
from std import Terminal;

@main
function main(int argc, char **argv): int
  Terminal.write("Hello, world!", Terminal.out);
  return 0;
;
```
