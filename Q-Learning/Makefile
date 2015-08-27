# Makefile for Car Tracking

CXX = g++
CFLAGS = -O2 -Wall -g -pipe -I.
LIBS = -lSDL -lSDL_gfx

OBJ_DIR = ./.obj

HDRS = $(wildcard *.hpp)
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRCS))

TARGET = ./ipq

LOG_FILES = 
OTHER_FILES = 

TOUCH = touch
RM = rm -f

.PHONY: all run clean touch

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CFLAGS) $(OBJS) $(LIBS) -o $(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

run:
	$(TARGET)

clean:
	$(RM) $(OBJS)
	$(RM) $(TARGET)
	$(RM) $(LOG_FILES)
#	$(RM) $(OTHER_FILES)

touch:
	$(TOUCH) $(wildcard *)

