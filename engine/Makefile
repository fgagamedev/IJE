NAME = ijengine
VERSION = 0.0.1

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
LIB_DIR = lib
TST_DIR = test

INSTALL_DIR = /usr/share/$(NAME)
PACKAGE = $(NAME)-$(VERSION).tar.gz

CC = g++
AR = ar

ARFLAGS = rcs
CFLAGS = -W -Wall -pedantic -std=c++11 -MMD -g3
INCLUDES = -Iinclude -Itest `sdl2-config --cflags`
LIBS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf

TARGET = $(LIB_DIR)/$(NAME).a

TEST = $(TST_DIR)/test
TST_SRC = ${wildcard $(TST_DIR)/*.cpp}
TST_OBJ = ${addprefix $(TST_DIR)/, ${notdir ${TST_SRC:.cpp=.o}}}

SRC = ${wildcard $(SRC_DIR)/*.cpp}
OBJ = ${addprefix $(OBJ_DIR)/, ${notdir ${SRC:.cpp=.o}}}

.PHONY: clean depend dist-clean dist install uninstall

all:
	@mkdir -p $(OBJ_DIR) $(LIB_DIR)
	$(MAKE) $(TARGET)
	$(MAKE) $(TEST)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo Building $@
	@$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

$(TST_DIR)/%.o: $(TST_DIR)/%.cpp
	@echo Building $@
	@$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

$(TARGET): $(OBJ)
	@echo Creating $@...
	@$(AR) $(ARFLAGS) $@ $(OBJ)

$(TEST): $(TST_OBJ) $(TARGET)
	@echo Building executable...
	@$(CC) $(CFLAGS) $(INCLUDES) $(TST_OBJ) $(TARGET) -o $@ $(LIBS)
	@echo Done!

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
	@rm test/test $(NAME).tar.gz

install: $(TARGET)
	@mkdir -p $(INSTALL_DIR)/lib $(INSTALL_DIR)/include
	@cp -rf include $(INSTALL_DIR)
	@cp -f $(TARGET) $(INSTALL_DIR)/lib/

uninstall:
	@rm -rf $(INSTALL_DIR)

-include $(OBJ:.o=.d)
