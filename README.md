_This project was created as part of the 42 curriculum by mjebali._

<h1 align="center">Get Next Line</h1>

# Description
get_next_line is a 42 curriculum project whose goal is to implement a function capable of reading a file line by line eturning one line per call, including the newline character \n when present. When the end of the file is reached, the function returns the last remaining line and subsequently returns NULL.

This project introduces fundamental concepts of systems programming in C:

* File descriptors (fd)
* System calls (read)
* Buffer management
* Static variables
* String manipulation
* Memory allocation and cleanup

The function prototype is :
``` c
char	*get_next_line(int fd);
```

## Workflow
The function uses a static stash to store leftover data between calls.
Each call performs three main steps:

#### **1. read_line**
Reads from the file descriptor into a buffer until:

     * A newline is found
     * EOF is reached

The read data is appended to the stash.

#### **2. extract_line**
Returns the next line from the stash:

     * Includes the newline \n if present
     * Allocates a new string for the line

#### **3. clean_stash**
Removes the returned line from the stash and keeps only the leftover.
If no leftover remains, stash becomes NULL.


## Project Structure
``` c
get_next_line/
│
├── get_next_line.c
├── get_next_line_utils.c
├── get_next_line.h
├── get_next_line_bonus.c
├── get_next_line_utils_bonus.c
├── get_next_line_bonus.h
└── README.md
```
### get_next_line.c
Contains:

* get_next_line
* read_line
* extract_line
* clean_stash

### get_next_line_utils.c
Contains helper functions:

* ft_strlen
* ft_strchr
* ft_strjoin
* ft_strdup
* ft_substr

### get_next_line.h
Contains:

* Required includes
* BUFFER_SIZE definition
* Function prototypes

# Instructions

## Compilation

Compile the source files:
```c
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c
```
Test Example
```c
cc -Wall -Wextra -Werror main.c get_next_line.c get_next_line_utils.c
```
Execution
```c
./a.out
```
Compilation with a Custom BUFFER_SIZE
```c
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
main.c get_next_line.c get_next_line_utils.c
```
## Usage Example
```c
int		fd;
char	*line;

fd = open("text.txt", O_RDONLY);

line = get_next_line(fd);
while (line)
{
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
}
close(fd);
```

## Validation
The project has been verified using:

#### Norminette
```c
norminette
```
#### Compilation
```c
cc -Wall -Wextra -Werror
```
#### Valgrind
```c
valgrind --leak-check=full ./a.out
```
Result:
```c
All heap blocks were freed -- no leaks are possible
ERROR SUMMARY: 0 errors
```

# Resources
## Official Documentation
* read(2) manual
* open(2) manual
* malloc(3) manual
* free(3) manual
* close(2) manual

## Use of Artificial Intelligence
During the development of this project, AI was used exclusively as an educational support tool for:

* Understanding how read() works.
* Understanding the purpose and behavior of BUFFER_SIZE.
* Assisting in the preparation of this README file.

## Key learning

* the need for the stash
* the use of a static variable
* incremental reading with read()
* precise extraction of lines
* cleaning the stash
* memory management without leaks

# Bonus Part
After completing the mandatory part, an additional version of the project was implemented to support multiple file descriptors simultaneously.

## Objective
The goal of the bonus part is to allow get_next_line() to maintain an independent reading state for each file descriptor.

This means that different files can be read alternately without losing track of the current position in any of them.

Example:

get_next_line(fd1);
get_next_line(fd2);
get_next_line(fd3);
get_next_line(fd1);
get_next_line(fd2);
get_next_line(fd3);

Each file descriptor continues reading from the exact position where it stopped during the previous call.

## Algorithm
The mandatory version uses a single static variable:
```c
static char *store;
```
The bonus version replaces it with an array of static pointers:
```c
static char *store[1024];
```
Each file descriptor has its own storage area:
```c
store[3]
store[4]
store[5]
...
```
This allows the function to preserve independent reading states for multiple files at the same time.

The helper functions remain unchanged, and only the management of the static storage is modified.

## Bonus Files
The bonus implementation is provided in the following files:
```c
get_next_line_bonus.c
get_next_line_bonus.h
get_next_line_utils_bonus.c
```
## Bonus Validation
The bonus implementation was tested using:

* Multiple file descriptors opened simultaneously.
* Different BUFFER_SIZE values.
* Valgrind memory analysis.
* Norminette verification.

