NAME = libmedia_ncurses.so

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
CXX_FLAGS = -g -O2 -Wall -Wextra -Werror -Weverything -Wno-c++98-compat -Wno-padded
CXX_FLAGS_DEPS = -MT $@ -MD -MP -MF $(@:.o=.d)
SRC_CXXFLAGS = -fPIC
BIN_CFLAGS = -shared
CXX_STD = -std=c++11
INC_FLAGS = -I . -I ../common
LFLAGS = -lncurses
SRC_FLAGS = $(SRC_CXXFLAGS) $(CXX_FLAGS_DEPS) $(CXX_FLAGS) $(CXX_STD) $(INC_FLAGS)
BIN_FLAGS = $(BIN_CFLAGS) $(CXX_FLAGS_DEPS) $(CXX_FLAGS) $(INC_FLAGS)


SRC_FOLDER = src/

SRC_FILES =	WrapperNcurses.class.cpp \
			Renderer.class.cpp

SRC = $(addprefix $(SRC_FOLDER), $(SRC_FILES))

### add cpp files from common dir
SRC += ../common/ILibMedia.class.cpp

OBJ = $(SRC:%.cpp=%.o)

#################################### COMPILATION ###############################

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ)
	@printf "\\t%sLD%s\\t" "$(_CYAN)" "$(_END)"
	@$(CXX) $(BIN_FLAGS) $(OBJ) -o $(NAME) $(LFLAGS)
	@printf "%s\\n" "$@"

%.o: %.cpp
	@printf "\\t%sCC%s\\t" "$(_GREEN)" "$(_END)"
	@$(CXX) $(SRC_FLAGS) -c $< -o $@
	@printf "%s\\n" "$<"

#add dependencies files (*.d)
DEP_FILES = $(SRC:%.cpp=%.d)
-include $(DEP_FILES)

.PHONY: clean
clean:
	@rm -rf $(OBJ)
	@rm -rf $(DEP_FILES)
	@echo "Objects removed"

.PHONY: fclean
fclean: clean
	@rm -rf $(NAME)
	@echo "Library $(NAME) removed"

.PHONY: re
re:
	@make fclean
	@make all
