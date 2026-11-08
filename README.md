*This project has been created as part of the 42 curriculum by mahadout.*

# Get Next Line

## Description

**Get Next Line** is a 42 school project written in C. The goal is to create a function that reads and returns one line at a time from a file descriptor.

Unlike traditional file-reading approaches, `get_next_line()` does not read the entire file at once. Instead, it reads a limited number of bytes per operation, determined by `BUFFER_SIZE`, and preserves any remaining characters for subsequent calls.

The project introduces several important C programming concepts:

- File descriptors and the `read()` system call.
- Static variables and persistent storage.
- Dynamic memory allocation using `malloc()` and `free()`.
- String manipulation and memory management.
- Buffer handling and newline detection.
- Handling different file descriptors.

The function must return a line ending with `\n` when a newline is present. If the final line does not end with a newline, it must still return the remaining content. Once there is no more content to read, it returns `NULL`.

## Instructions

### Requirements

- A C compiler (`cc` or `gcc`).
- A Unix-like environment.
- The standard C library.
- A valid file descriptor to read from.

### Project files

**Mandatory part:**

- `get_next_line.c` — Main implementation of the function.
- `get_next_line_utils.c` — Helper functions used by the main implementation.
- `get_next_line.h` — Header file containing function prototypes, required headers, and the default `BUFFER_SIZE`.

**Bonus part:**

- `get_next_line_bonus.c` — Bonus implementation supporting multiple file descriptors.
- `get_next_line_utils_bonus.c` — Helper functions for the bonus implementation.
- `get_next_line_bonus.h` — Bonus header file.

### Compilation

Clone the repository:

```bash
git clone https://github.com/ahadout/42-get_next_line.git
cd get_next_line
```

Compile the mandatory part:

```bash
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c
```

Compile with a custom buffer size:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```

Compile the bonus part:

```bash
cc -Wall -Wextra -Werror get_next_line_bonus.c get_next_line_utils_bonus.c main.c
```

**Note:** `main.c` is a testing file and is not part of the final mandatory submission requirements. Use your own test file or test program when compiling.

### Execution

Run the compiled program:

```bash
./a.out
```

The function can read from:
- Regular files opened with `open()`.
- Standard input (`stdin`).
- Other valid file descriptors.

Example usage:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("test.txt", O_RDONLY);
    if (fd < 0)
        return (1);

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return (0);
}
```

### Buffer Size

`BUFFER_SIZE` determines the maximum number of bytes requested by each `read()` call.

For example:

```bash
-D BUFFER_SIZE=1
-D BUFFER_SIZE=42
-D BUFFER_SIZE=1000
```

The function must work with different buffer sizes without assuming that a complete line fits into a single buffer.

## Algorithm

The algorithm is based on reading data in chunks, accumulating the received characters, detecting newlines, and preserving unread content between function calls.

### 1. Persistent storage

A static variable is used to preserve unread characters between calls to `get_next_line()`.

This is necessary because local variables normally lose their values when a function returns. A static variable retains its value throughout the program's execution.

The storage contains characters that have already been read but have not yet been returned to the caller.

### 2. Reading data

The function allocates a temporary buffer based on `BUFFER_SIZE` and uses `read()` to retrieve data from the supplied file descriptor.

The return value of `read()` determines what happens next:

- A positive value indicates the number of bytes successfully read.
- `0` indicates the end of the file.
- `-1` indicates a reading error.

Only the bytes actually returned by `read()` are processed.

### 3. Accumulating the data

Every time new data is read, it is appended to the persistent storage.

Since the amount of data required for a complete line is not known in advance, dynamic memory allocation is used.

The process consists of:

1. Calculating the length of the existing stored data.
2. Calculating the number of newly received bytes.
3. Allocating enough memory for both parts and the null terminator.
4. Copying the existing data.
5. Appending the newly read data.
6. Freeing the previous allocation.

This allows the storage to grow when a line is longer than `BUFFER_SIZE`.

### 4. Newline detection

After accumulating new data, the function searches for the first `\n` character.

If no newline is found, additional data is read and appended.

If a newline is found, the function can extract the first complete line.

### 5. Extracting the line

Once a newline is detected, the function separates the accumulated string into two parts:

- **The returned line:** Contains all characters up to and including the first newline.
- **The remaining content:** Contains everything after that newline.

The returned line is allocated separately so that it can be safely returned to the caller.

### 6. Preserving the remaining content

The remaining characters are kept in persistent storage for the next call.

This prevents data loss when a single `read()` operation retrieves multiple lines.

For example, if the accumulated content is:

```text
Hello
World
42
```

The first call returns:

```text
Hello\n
```

The remaining storage becomes:

```text
World\n42
```

The next call can therefore return `World\n` without needing to read those characters again.

### 7. Handling EOF

When `read()` reaches the end of the file:

- If the storage contains remaining characters, they are returned as the final line, even if there is no trailing newline.
- If the storage is empty, the function returns `NULL`.

This ensures that the final line is not lost.

### Algorithm summary

```text
START
  |
  v
Read data into temporary buffer
  |
  v
Append received bytes to persistent storage
  |
  v
Is there a newline?
  |
  +---- YES ----> Extract the first line
  |                    |
  |                    v
  |              Preserve remaining data
  |                    |
  |                    v
  |              Return extracted line
  |
  +---- NO -----> Has EOF or an error occurred?
                       |
                       +---- NO ----> Read more data
                       |
                       +---- YES ---> Is storage empty?
                                           |
                                           +---- YES ---> Return NULL
                                           |
                                           +---- NO ----> Return remaining data
```

## Bonus Part

The bonus part extends the mandatory implementation to support multiple file descriptors.

Instead of maintaining one persistent storage area, the implementation maintains separate storage for each file descriptor.

This allows calls to `get_next_line()` using different file descriptors to be interleaved without mixing their unread content.

For example:

```c
get_next_line(fd1);
get_next_line(fd2);
get_next_line(fd1);
get_next_line(fd2);
```

Each file descriptor maintains its own reading progress and remaining data.

## Resources

The following resources were useful for understanding the concepts involved in this project:

- [Linux Manual — read(2)](https://man7.org/linux/man-pages/man2/read.2.html) — Documentation about the `read()` system call.
- [Linux Manual — malloc(3)](https://man7.org/linux/man-pages/man3/malloc.3.html) — Dynamic memory allocation.
- [Linux Manual — free(3)](https://man7.org/linux/man-pages/man3/free.3.html) — Releasing dynamically allocated memory.
- [GNU C Library Documentation](https://www.gnu.org/software/libc/manual/) — General C library documentation.

### AI Usage

AI tools, were used as learning and debugging assistance during this project.

They were used for:

- Understanding C concepts such as static variables, pointers, memory allocation, and the `read()` function.
- Understanding how to detect newlines and preserve unread characters.
- Discussing possible algorithm designs and edge cases.
- Understanding compiler errors and warnings encountered during development.
- Reviewing code behavior and explaining potential memory-management problems.

The AI was used as a learning and reference tool. The implementation, testing, and understanding of the project were developed as part of the learning process.

## Author

- **Author:** ahadout
- **Project:** get_next_line
- **School:** 1337 / 42 Network
