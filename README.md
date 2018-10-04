# image
> Library to work with image files

**image** is a library (or small set of functions) to work with image files.
Mostly it can read and write binary data into a file.

## Constructors

The library admits two types of constructors:

```c++
image(void);

image(std::string fname);
```

The first one only creates the file. The second, also opens the file. You can
check if an image is open with the method:

```c++
bool is_open(void);
```

To open and close a file you must use the following methods:

```c++
int open(std::string fname);

int close(void);
```

Both functions return zero on correct ending and a non-zero value on error. To
perform the write or read of a file, you can use one of the following methods:

```c++
int read(char *c);
int read(char *buff, std::streamsize n);
int read(char *buff, std::streamsize n, std::streampos offset);

int write(const char *c);
int write(const char *buff, std::streamsize n);
int write(const char *buff, std::streamsize n, std::streampos offset);
```

The first one reads/writes one character at the actual position, the second
reads/writes n bytes at the actual position, and the last one, reads/writes n
bytes at the offset position.

## Example

```c++
/* test-image.cpp - tests the image library
 * g++ -o test-image -Iinclude -L. test-image.cpp -limage
 */

#include <iostream>
#include <cstring>
#include <image>

int
main(void) {
  image img;
  char dot, elf[3];

  if (img.open("file.elf") != 0) {
    std::cerr << "error openning file 'file.elf'" << std::endl;
    return 1;
  }
  /* Open an ELF file */

  if (img.is_open()) {
    if (img.read(&dot) != 0 || dot != 0x7f) {
      std::cerr << "error reading file" << std::endl;
      return 2;
    }
    if (img.read(elf, 3, 1) != 0 || elf[0] != 0x45 || elf[1] != 0x4c ||
      elf[2] != 0x46) {
      std::cerr << "error reading file" << std::endl;
      return 3;
    }
  }
  /* Read ELF header */

  /* img.close();
  Closing the file isn't necessary, the destructor will do it for us */

  return 0;
}
```
