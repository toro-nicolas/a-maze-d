# 🧭 A-maze-D 🚸

![A-maze-D](https://toro-nicolas.github.io/a-maze-d/preview.png)

## Table of contents 📑
- [Description](https://github.com/toro-nicolas/a-maze-d/blob/main/README.md#description-)
- [Usage](https://github.com/toro-nicolas/a-maze-d/blob/main/README.md#usage-%EF%B8%8F)
- [Result](https://github.com/toro-nicolas/a-maze-d/blob/main/README.md#result-)
- [Compilation](https://github.com/toro-nicolas/a-maze-d/blob/main/README.md#compilation-%EF%B8%8F)
- [Documentation](https://github.com/toro-nicolas/a-maze-d/blob/main/README.md#documentation-)
- [Code mandatory](https://github.com/toro-nicolas/a-maze-d/blob/main/README.md#code-mandatory-)
- [What's next ?](https://github.com/toro-nicolas/a-maze-d/blob/main/README.md#whats-next--)
- [Contributors](https://github.com/toro-nicolas/a-maze-d/blob/main/README.md#contributors-)


## Description 📝
The **A-maze-D** is a project carried out by **groups of 3** (see [Contributors](https://github.com/toro-nicolas/a-maze-d/blob/main/README.md#contributors-), during our **1st year** in [**EPITECH**](https://www.epitech.eu/) Grand Ecole program.  
Its purpose is to create in [**C**](https://en.wikipedia.org/wiki/C_(programming_language)) a [**maze solver**](https://en.wikipedia.org/wiki/Maze-solving_algorithm).  
The aim of the **A-maze-D** is to **solve a maze** as **efficiently** and **quickly** as possible, using [**path-finding algorithms**](https://en.wikipedia.org/wiki/Pathfinding).  


## Usage ⚔️
You can run a-maze-d like this :
```sh
./amazed < maps/labyrinth1
```

For more information, please see the help section or the PDF :
```sh
> ./amazed --help
Usage: ./amazed < [map]
```


## Result 🚩
The result of this project is an **perfect A-maze-D**.  
If you discover a **problem** or an **error**, don't hesitate to **create an issue** and **report it** to us as soon as possible.


### my.epitech.eu result

| Category       | Percentage | Numbers of tests |  Crash   |
|----------------|:----------:|:----------------:|:--------:|
| Algorithm app  |    100%    |       3/3        |    No    |
| Basics         |    100%    |       3/3        |    No    |
| Data Structure |    100%    |       3/3        |    No    |
| Optimization   |    100%    |       2/2        |    No    |
| Parsing        |    100%    |       9/9        |    No    |
| Robustness     |    100%    |      13/13       |    No    |
| **Results**    |  **100%**  |    **33/33**     |  **No**  |


### Tests and code coverage
**Unit tests** were performed using [criterion](https://criterion.readthedocs.io/en/master/intro.html).  
In this project, **only** the **library code is covered**.
Unit tests are still to be performed, but a large part of the code is already covered:
- Lines: 94.8%
- Functions: 97.6%
- Branches:	43.7%

You can compile the project and run the unit tests with this command :
```sh
make tests_run
```

For more details, please click [here](https://toro-nicolas.github.io/a-maze-d/tests/test.html).


## Compilation 🛠️
You can compile the project with this command :
```sh
make
```

If you want to debug the program, you can compile the project with this :
```sh
make debug 
```

If you want clean the project, you can run this command :
```sh
make fclean
```

You can clean and compile the project with ```make re``` and for debugging ```make re_debug```

You can compile the unit tests with this command :
```sh
make unit_tests
```


## Documentation 📚
The documentation is accessible [here](https://toro-nicolas.github.io/a-maze-d/html/).

You can generate the documentation with this command :
```sh
make doc
```
You need multiple package for generate them :
- doxygen
- doxygen-latex
- doxygen-doxywizard
- graphviz


## Code mandatory 📦
- You'll need to create a branch where you'll push your code. Once you've completed your tasks on this branch, we'll work together to merge it and check that everything works.
- Every function you add must be code-style and documented.
- Before merging, you'll need to check that all unit tests pass by running ```make tests_run```.
- If the github actions don't succeed, then ask yourself some questions
- Each commit will contain ```[+]``` or ```[-]``` or ```[~]``` followed by a message
    - ```[+]``` : Add feature
    - ```[-]``` : Delete feature
    - ```[~]``` : Edit feature

**Of course, in exceptional cases, we may depart from these rules.**


## What's next ? 🚀
- Add documentation on forgotten functions
- Make a graphical viewer
- Add unit tests on each piece of code


## Contributors 👥
For this project, we were a group of **3 people**. Here are the people in the group:
- [Christophe VANDEVOIR](https://github.com/ItsKarmaOff)
- [Guillaume LECOCQ](https://github.com/guilec06)
- [Nicolas TORO](https://github.com/toro-nicolas)
