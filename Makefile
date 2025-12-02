# Advent of Code 2025 template Makefile

.PHONY: all help clean remove $(DAYS)

CXX      := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -pedantic -g

DAYS := 01 02 03 04 05 06 07 08 09 10 11 12

UTIL_SRC := utils.cpp
UTIL_HDR := utils.h

all: help

help:
	@echo "Usage:"
	@echo "  make dayNN       # build directly (e.g., make day01)"
	@echo "  make DAY=NN day  # optional shorthand (e.g., make DAY=03 day)"
	@echo "  make clean       # remove Windows build products"
	@echo "  make remove      # remove POSIX build products"

day%: day%.cpp $(UTIL_SRC) | $(UTIL_HDR)
	$(CXX) $(CXXFLAGS) $^ -o $@

day:
ifndef DAY
	$(error Provide the DAY variable, e.g., make DAY=05 day)
endif
ifeq ($(filter $(DAY),$(DAYS)),)
	$(error Unknown day '$(DAY)'; choose from $(DAYS))
endif
	$(MAKE) day$(DAY)

$(foreach D,$(DAYS),$(eval $(D): day$(D)))

clean:
	del /Q *.o 2>nul
	del /Q day??.exe 2>nul
	del /Q day?? 2>nul
	@echo clean done

remove:
	\rm -f *.o day?? day??.exe
	@echo remove done
