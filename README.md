# Clang_BSQMapResolver

This project is a exploration into the C language. It is based 
on the [BSQ assignment](https://github.com/Binary-Hackers/42_Subjects/blob/master/01_Piscines/C/EN/bsq.en.pdf) provided by the 42 network.

## Installation

The makefile provides some generic functionality. The following
make rules are available. Just running *make* will execute the *all* target.
```bash
make
make all
make bsq
make clean
make fclean
make re
```

## Usage

To generate a BSQ map, use the **map_generator.pl** script. This can be used 
in the following fashion:
```bash
perl map_generator.pl [HEIGHT] [WIDTH] [DENSITY] >> map.txt
```

The map can then be resolved by the program by providing either the filepath 
to a text file containing the map as an argument, or via stdin.

```bash
./bsq [PATH_TO_FILE, ...]
cat PATH_TO_FILE | ./bsq
perl map_generator.pl 10 10 5 | ./bsq
```

When providing file paths, 1 to N file path arguments can be passed to the program. Each found map will
be solved and displayed on stdout. When a map is found invalid, the text *map error* will be send to stdout.
When providing data via stdin, only one map can be passed.