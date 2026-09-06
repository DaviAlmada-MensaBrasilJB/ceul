# CEUL
A lightweight and fast interpreted programming language.

## What is "CEUL"?
CEUL stands for **Computationally Efficient Universal Language**, which is a programming language implemented entirely in C designed to be fast and simple for programmers of all skill levels.

## Latest Version
```
v0.0.3-beta.2
```
### Latest Stable Version
```
v0.0.2
```
### Stability Note
> CEUL is still in early development, which makes most of its features subject to change.
## Installation
### Windows
Download the official `.exe` file from the [Official Releases Page](https://github.com/DaviAlmada-MensaBrasilJB/ceul/releases)
### Linux / WSL2
Download the official Linux release from the [Official Releases Page](https://github.com/DaviAlmada-MensaBrasilJB/ceul/releases)
### Other Systems
In order to install and use the CLI follow these steps:
1. Make sure you have the GCC compiler installed on your machine.
2. Download the [source code](https://github.com/DaviAlmada-MensaBrasilJB/ceul/archive/refs/tags/v0.0.3-beta.zip).
3. Run the following commands:  
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
Outputs a string of text to stdout (Standard Output).
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
Terminates the CEUL REPL interpreter without closing the terminal.
#### Use:
```
> exit
```
### Sleep
Waits a specified amount of time before continuing.
#### Use:
```
> sleep <wait time(in milliseconds)>
```
### Loop
Executes a command a set amount of times.

#### Args:
```
> loop <start INT> <end INT> <step INT> <command>
```
start = Starting value\
end = End limit\
step = Increment/decrement\
command = The command which should be executed\
\
INT = Integer
#### Example:
```
> loop 0 10 1 write "Hello"
HelloHelloHelloHelloHelloHelloHelloHelloHelloHello
```
### File
Runs a file as code.\
\
Requires the `n` prefix before the filepath which tells CEUL not to treat backslashes as escape sequences.\
The prefix is also removed from the string after processing.
#### Args:
```
> file n"<filepath>"(Surrounded by quotes, as shown)
```
#### Example:
C:\Users\Generic User\Documents\main.txt:
```
write "\"Hello\" 100 times!"
loop 0 100 1 write "Hello! " sleep 500
```
REPL:
```
> file n"C:/Users/Generic User/Documents/main.txt"
Hello! Hello! Hello! Hello! Hello! Hello! Hello!...
```
## Roadmap Checklist
- [x] Strings
- [x] REPL CLI
- [x] `write`
- [x] `exit`
- [x] `clear`
- [x] `loop`
- [x] `sleep`
- [x] File reading with `file`
- [ ] `()` for arguments
- [ ] Code block closing with `end`
- [ ] Variables
- [ ] While and Do While loops
- [ ] Arithmetic operations
- [ ] Conditions
- [ ] Functions
- [ ] Libraries
- [ ] Modules
- [ ] Objects and classes (OOP)
## Proposed Syntax (Not implemented)
### Hello, world!
```
from std import Terminal;

@main
function main(int argc, char **argv): int
    Terminal.write("Hello, world!", Terminal.out);
    return 0;
end
```
