# Pipex

#### ✅ [125/125]

`pipex` is a project that reimplements the behavior of shell pipe (`|`) functionality in C. It demonstrates low-level system programming concepts, process creation, file descriptor manipulation, and command execution in Unix-like systems.

## Table of Contents

- [Project Overview](#project-overview)
- [Compilation](#compilation)

## Project Overview

The goal of `pipex` is to simulate the following shell command:

### Mandatory:

```bash
< infile cmd1 | cmd2 > outfile
```

As a C program equivalent to:

```bash
./pipex infile cmd1 cmd2 outfile
```

### Bonus:

#### multiple commands:

```bash
< infile cmd1 | cmd2 | cmd3 | cmd4 > outfile
```

As a C program equivalent to:

```bash
./pipex infile cmd1 cmd2 cmd3 cmd4 outfile
```

#### here_doc:

```bash
<< LIM cmd1 | cmd2 >> outfile
```

As a C program equivalent to:

```bash
./pipex here_doc LIM cmd1 cmd2 outfile
```

## Compilation

To compile :

```sh
make
make all
make bonus
```

To clean object files:

```sh
make clean
```

To remove everything (including the binary `pipex`):

```sh
make fclean
```

To recompile:

```sh
make re
```

## License

This project is part of the 42 curriculum and follows its academic policies.
