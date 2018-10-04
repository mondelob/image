# image - library to work with image files
# Copyright (C) 2018  Bruno Mondelo

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

.PHONY: all clean dist check testdrivers

AUXFILES := Makefile README.md LICENSE

SRCFILES := $(shell find src -type f -name "*.cpp")
HDRFILES := $(shell find include -type f -name "*")
LIBFILES := libimage.a

OBJFILES := $(patsubst %.cpp,%.o,$(SRCFILES))
TSTFILES := $(patsubst %.cpp,%_t,$(SRCFILES))

DEPFILES := $(patsubst %.cpp,%.d,$(SRCFILES))
TSTDEPFILES := $(patsubst %,%.d,$(TSTFILES))

ALLFILES := $(AUXFILES) $(SRCFILES) $(HDRFILES)

WARNINGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
            -Wwrite-strings -Wmissing-declarations -Wredundant-decls \
            -Winline -Wno-long-long -Wconversion -Wcast-qual \
            -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 \
            -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept \
            -Wold-style-cast -Woverloaded-virtual -Wsign-conversion \
            -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 \
            -Wswitch-default -Wundef -Werror
CPPFLAGS := -std=c++17 $(WARNINGS)

all: $(LIBFILES)

clean:
	-@$(RM) $(wildcard $(OBJFILES) $(TSTFILES) $(LIBFILES) image.tar.gz)

dist:
	@tar czf image.tar.gz $(ALLFILES)

check: testdrivers
	-@rc=0; count=0; \
	for file in $(TSTFILES); do \
		./$$file; out=$$?; \
		echo " testing    $$file:	$$out"; \
		rc=`expr $$rc + $$out`; count=`expr $$count + 1`; \
	done; \
	echo; echo "tests: $$count  failed: $$rc"

testdrivers: $(TSTFILES)

-include $(DEPFILES) $(TSTDEPFILES)

%.o: %.cpp Makefile
	@$(CXX) $(CPPFLAGS) -Iinclude -MMD -MP -c $< -o $@

%_t: %.cpp
	@$(CXX) $(CPPFLAGS) -Iinclude -DTEST $< -o $@

libimage.a: $(OBJFILES)
	@ar csq $@ $?
