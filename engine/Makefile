NAME = ijengine.a

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
LIB_DIR = lib
TST_DIR = test

CC = g++
AR = ar

ARFLAGS = rcs
CFLAGS = -W -Wall -pedantic -ansi -std=c++11 -MMD
INCLUDES = -Iinclude -Itest `sdl2-config --cflags`
LIBS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf

TARGET = $(LIB_DIR)/$(NAME)

TEST = $(TST_DIR)/test
TST_SRC = ${wildcard $(TST_DIR)/*.cpp}
TST_OBJ = ${addprefix $(TST_DIR)/, ${notdir ${TST_SRC:.cpp=.o}}} 

SRC = ${wildcard $(SRC_DIR)/*.cpp}
OBJ = ${addprefix $(OBJ_DIR)/, ${notdir ${SRC:.cpp=.o}}} 

.PHONY: clean depend

all: 
	@mkdir -p $(OBJ_DIR) $(LIB_DIR)
	$(MAKE) $(TARGET)
	$(MAKE) $(TEST)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

$(TST_DIR)/%.o: $(TST_DIR)/%.cpp
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

$(TARGET): $(OBJ)
	$(AR) $(ARFLAGS) $@ $(OBJ)

$(TEST): $(TST_OBJ) $(TARGET)
	$(CC) $(CFLAGS) $(INCLUDES) $(TST_OBJ) $(TARGET) -o $@ $(LIBS)

clean:
	@find . -name *.o -exec rm {} \;
	@find . -name *.d -exec rm {} \;
	@rm -rf *~ *.o prog out.txt

dist-clean: clean
	@find . -name *.a -exec rm {} \;
	@rm test/test

-include $(OBJ:.o=.d)
