/* image.cpp - functions to work with image files
 * Copyright (C) 2018  Bruno Mondelo

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <ios>
#include <image>

image::image(void) {
  this->openned = false;
}
/* Constructor */

image::image(std::string fname) {
  this->openned = false;
  this->open(fname);
}
/* Constructor */

image::~image(void) {
  if (this->openned)
    this->close();
}
/* Destructor */

bool
image::is_open(void) {
  return this->openned;
}

int
image::open(std::string fname) {
  if (this->openned)
    return -1;

  this->stream.open(fname, std::ios::in | std::ios::out | std::ios::binary);
  if (!this->stream.is_open())
    return -2;

  this->soffset = 0;
  this->openned = true;

  return 0;
}
/* Opens a file */

int
image::close(void) {
  if (!this->openned)
    return -1;

  this->stream.close();

  this->openned = false;

  return 0;
}
/* Closes the file */

int
image::read(char *c) {
  return this->read(c, 1, this->soffset);
}
/* Reads data from file */

int
image::read(char *buff, std::streamsize n) {
  return this->read(buff, n, this->soffset);
}
/* Reads data from file */

int 
image::read(char *buff, std::streamsize n, std::streampos offset) {
  if (!this->openned)
    return -1;

  if (offset != this->soffset) {
    this->stream.seekg(offset);
    this->soffset = offset;
  }

  this->stream.read(buff, n);

  if (this->stream.eof())
    return -2;
  else if (this->stream.fail())
    return -3;
  else if (this->stream.bad())
    return -4;

  this->soffset += n;

  return 0;
}
/* Reads data from file */

int
image::write(const char *c) {
  return this->write(c, 1, this->soffset);
}
/* Writes data to file */

int
image::write(const char *buff, std::streamsize n) {
  return this->write(buff, n, this->soffset);
}
/* Writes data to file */

int
image::write(const char *buff, std::streamsize n, std::streampos offset) {
  if (!this->openned)
    return -1;

  if (offset != this->soffset) {
    this->stream.seekp(offset);
    this->soffset = offset;
  }

  this->stream.write(buff, n);

  if (this->stream.fail())
    return -2;
  else if (this->stream.bad())
    return -3;

  this->soffset += n;

  return 0;
}
/* Writes data to file */

#ifdef TEST

int
main(void) {
  int nerr;
  image img;
  /* Variables to test the read and the writing */
  /* char elf[4];
  char alf[4]; */

  nerr = 0;

  if (img.is_open())
    nerr++;

  if (img.open("LICENSE") != 0)
    nerr++;

  if (!img.is_open())
    nerr++;

  /* This is the test to check the read and the writing to run this tests you
  should first run a make all */
  /* if (img.close() != 0)
    nerr++;

  if (img.open("src/image.o") != 0)
    nerr++;

  if (img.read(elf, 4, 0) != 0 )
    nerr++;

  if (elf[0] != 0x7f || elf[1] != 0x45 || elf[2] != 0x4c || elf[3] != 0x46)
    nerr++;

  elf[0] = 0x12;
  elf[1] = 0x34;
  elf[2] = 0x56;
  elf[3] = 0x78;

  if (img.write(elf, 4, 0) != 0)
    nerr++;

  if (img.close() != 0)
    nerr++;

  if (img.open("src/image.o") != 0)
    nerr++;

  if (img.read(alf, 4, 0) != 0 )
    nerr++;

  if (alf[0] != 0x12 || alf[1] != 0x34 || alf[2] != 0x56 || alf[3] != 0x78)
    nerr++; */

  if (img.close() != 0)
    nerr++;

  if (img.is_open())
    nerr++;

  return nerr;
}

#endif
/* Tests */
