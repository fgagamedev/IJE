NAME = ijengine
VERSION = 0.0.3

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
LIB_DIR = lib
TST_DIR = test

INSTALL_DIR = /usr/local
INCLUDES_INSTALL_DIR = $(INSTALL_DIR)/include/$(NAME)
LIB_INSTALL_DIR = $(INSTALL_DIR)/lib

PACKAGE = $(NAME)-$(VERSION).tar.gz

CC = g++
AR = ar

ARFLAGS = rcs
CFLAGS = -W -Wall -pedantic -std=c++11 -MMD -g3 -g
INCLUDES = -Iinclude -Itest `sdl2-config --cflags`
LIBS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lSDL2_mixer

TARGET = $(LIB_DIR)/lib$(NAME).a

TEST = $(TST_DIR)/test
TST_SRC = ${wildcard $(TST_DIR)/*.cpp}
TST_OBJ = ${addprefix $(TST_DIR)/, ${notdir ${TST_SRC:.cpp=.o}}}

SRC = ${wildcard $(SRC_DIR)/*.cpp}
OBJ = ${addprefix $(OBJ_DIR)/, ${notdir ${SRC:.cpp=.o}}}

.PHONY: clean depend dist-clean dist install uninstall

all:
	@mkdir -p $(OBJ_DIR) $(LIB_DIR)
	$(MAKE) $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo Building $@
	@$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

$(TST_DIR)/%.o: $(TST_DIR)/%.cpp
	@echo Building $@
	@$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

$(TARGET): $(OBJ)
	@$(AR) $(ARFLAGS) $@ $(OBJ)

$(TEST): $(TST_OBJ) $(TARGET)
	@echo Building executable...
	@$(CC) $(CFLAGS) $(INCLUDES) $(TST_OBJ) $(TARGET) -o $@ $(LIBS)

clean:
	@echo Cleaning...
	@find . -name *.o -exec rm {} \;
	@find . -name *.d -exec rm {} \;
	@rm -rf *~ *.o prog out.txt

dist:
	@rm -rf *~
	@tar czf $(PACKAGE) include src Makefile

dist-clean: clean
	@find . -name *.a -exec rm {} \;
	@rm -f test/test $(TARGET)
	@rm -rf *.tar.gz

install: $(TARGET)
	@mkdir -p $(INCLUDES_INSTALL_DIR) $(LIB_INSTALL_DIR)
	@cp -rf include/* $(INCLUDES_INSTALL_DIR)
	@cp -f $(TARGET) $(LIB_INSTALL_DIR)

uninstall:
	@rm -rf $(INCLUDES_INSTALL_DIR) $(INSTALL_DIR)/$(TARGET)

-include $(OBJ:.o=.d)
