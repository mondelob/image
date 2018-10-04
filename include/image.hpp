/* image.hpp - functions to work with image files (header)
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

#include <fstream>
#include <string>

class image {
  private:
    std::fstream stream;
    /* Stream of the openned file */
    std::streampos soffset;
    /* Stream actual offset */
    bool openned;
    /* Flag to check if the image is open */
  public:
    image(void);
    /* Constructor */
    image(std::string fname);
    /* Constructor */
    ~image(void);
    /* Destructor */
    bool is_open(void);
    /* Returns the flag if it's the image openned */
    int open(std::string fname);
    /* Opens a file */
    int close(void);
    /* Closes the file */
    int read(char *c);
    /* Reads data from file */
    int read(char *buff, std::streamsize n);
    /* Reads data from file */
    int read(char *buff, std::streamsize n, std::streampos offset);
    /* Reads data from file */
    int write(const char *c);
    /* Writes data to file */
    int write(const char *buff, std::streamsize n);
    /* Writes data to file */
    int write(const char *buff, std::streamsize n, std::streampos offset);
    /* Writes data to file */
};
