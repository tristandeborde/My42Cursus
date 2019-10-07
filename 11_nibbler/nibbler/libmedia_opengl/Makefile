NAME = libmedia_opengl.so

_RED=$(shell tput setaf 1 2> /dev/null || echo "")
_GREEN=$(shell tput setaf 2 2> /dev/null || echo "")
_YELLOW=$(shell tput setaf 3 2> /dev/null || echo "")

_BLUE=$(shell tput setaf 4 2> /dev/null || echo "")
_PURPLE=$(shell tput setaf 5 2> /dev/null || echo "")
_CYAN=$(shell tput setaf 6 2> /dev/null || echo "")
_WHITE=$(shell tput setaf 7 2> /dev/null || echo "")
_END=$(shell tput sgr0 2> /dev/null || echo "")

MAKEFLAGS += --no-print-directory

CXX = clang++

SRC_FOLDER = src/

CFLAGS = -Wall -Wextra -Werror -Weverything -pedantic -Wno-c++98-compat -Wno-padded -MD -g -O2 -D BASEPATH=\"$(BASEPATH)\"
SRC_CFLAGS = -fPIC
BIN_CFLAGS = -shared
CXX_STD = -std=c++11
IFLAGS = -I . -I src -I ../common
LFLAGS = $(shell sdl2-config --libs) -lGLEW -lglfw -lassimp -lSDL2 -lSDL2_image -lSDL2_ttf

ifeq ($(shell uname -s), Linux)
    LFLAGS += -LGL
endif
ifeq ($(shell uname -s), Darwin)
    LFLAGS += -framework OpenGl -framework AppKit
endif

BREW_PATH = ~/.brew
ifeq ($(shell [ -d $(BREW_PATH) ]; echo $$?), 0)
    IFLAGS += -isystem $(BREW_PATH)/include
endif

SRC_FLAGS = $(SRC_CFLAGS) $(CFLAGS) $(IFLAGS)
BIN_FLAGS = $(BIN_CFLAGS) $(CFLAGS) $(IFLAGS)

SRC_FILES = \
	Renderer.class.cpp \
	Exception.class.cpp \
	Opengl.class.cpp \
	Shader.class.cpp \
	Mesh.class.cpp \
	Model.class.cpp \
	ModelConfig.class.cpp \
	Camera.class.cpp \
	Entity3d.class.cpp \
	WrapperOpenGL.class.cpp \
	Config.cpp

SRC = $(addprefix $(SRC_FOLDER), $(SRC_FILES))

### add cpp files from common dir
SRC += ../common/ILibMedia.class.cpp

OBJ = $(SRC:%.cpp=%.o)

#################################### COMPILATION ###############################

.PHONY: all
all:  $(NAME)

$(NAME): $(OBJ)
	@printf "\\t%sLD%s\\t" "$(_CYAN)" "$(_END)"
	@$(CXX) $(BIN_FLAGS) $(OBJ) -o $(NAME) $(LFLAGS)
	@printf "%s\\n" "$@"

%.o: %.cpp Makefile
	@printf "\\t%sCC%s\\t" "$(_GREEN)" "$(_END)"
	@$(CXX) $(CXX_STD) $(SRC_FLAGS) -c $< -o $@
	@printf "%s\\n" "$<"

#add dependencies files (*.d)
DEP_FILES = $(SRC:%.cpp=%.d)
-include $(DEP_FILES)

.PHONY: clean
clean:
	@rm -rf $(OBJ)
	@echo "Objects removed"

.PHONY: fclean
fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(DEP_FILES)
	@echo "Library $(NAME) removed"

.PHONY: re
re:
	@make fclean
	@make all
