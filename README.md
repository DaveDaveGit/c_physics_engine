# c_physics_engine

A custom physics engine written in C/C++

## Requirements

- `cmake` for compiling
- `make` unless you want to type the shell-commands
- `gcc` / `clang` / possibly any other compiler
- `gdb` for debugging
- `clang-format` & `clang-tidy` to make the code look nice
- `doxygen` in case you want documentation

*tested only under windows with wsl, so no promises :)*

## Makefile

- `make clean`: delete files ignored by git
- `make fmt`: format all code
- `make test`: build and execute all unittests

- `make doc`: generate documantation
- `make build`: build the lib
- `make demo`: build and run the current demo
