# CEUL
An open-source, lightweight, fast and practical programming language designed for everyone, with a simple syntax and a lightweight standard library.
## What is "CEUL"?
CEUL stands for **Computationally Efficient Universal Language**, which is a C-like programming language written entirely in C designed to be fast, simple and lightweight programmers of all skill levels.
Currently, it's a concept for what CEUL should be, because the C interpreter is still a CLI like this:
```
CEUL
> write Hello, world!
Hello, world!
```
## Code examples
### "Hello, world!":
```
from std import Terminal;

@main
function main(int argc, char **argv): int
  Terminal.write("Hello, world!", Terminal.out);
  return 0;
;
```
