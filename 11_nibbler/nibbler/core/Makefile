
#         Art by Blazej Kozlowski
#
#                    __.
#                 .-".'                      .--.            _..._
#               .' .'                     .'    \       .-""  __ ""-.
#              /  /                     .'       : --..:__.-""  ""-. \
#             :  :                     /         ;.d$$    sbp_.-""-:_:
#             ;  :                    : ._       :P .-.   ,"TP
#             :   \                    \  T--...-; : d$b  :d$b
#              \   `.                   \  `..'    ; $ $  ;$ $
#               `.   "-.                 ).        : T$P  :T$P
#                 \..---^..             /           `-'    `._`._
#                .'        "-.       .-"                     T$$$b
#               /             "-._.-"               ._        '^' ;
#              :                                    \.`.         /
#              ;                                -.   \`."-._.-'-'
#             :                                 .'\   \ \ \ \
#             ;  ;                             /:  \   \ \ . ;
#            :   :                            ,  ;  `.  `.;  :
#            ;    \        ;                     ;    "-._:  ;
#           :      `.      :                     :         \/
#           ;       /"-.    ;                    :
#          :       /    "-. :                  : ;
#          :     .'        T-;                 ; ;
#          ;    :          ; ;                /  :
#          ;    ;          : :              .'    ;
#         :    :            ;:         _..-"\     :
#         :     \           : ;       /      \     ;
#         ;    . '.         '-;      /        ;    :
#         ;  \  ; :           :     :         :    '-.
#         '.._L.:-'           :     ;    bug   ;    . `.
#                              ;    :          :  \  ; :
#                              :    '-..       '.._L.:-'
#                               ;     , `.
#                               :   \  ; :
#                               '..__L.:-'
#

NAME = bombler

_RED=$(shell tput setaf 1 2> /dev/null || echo "")
_GREEN=$(shell tput setaf 2 2> /dev/null || echo "")
_YELLOW=$(shell tput setaf 3 2> /dev/null || echo "")
_BLUE=$(shell tput setaf 4 2> /dev/null || echo "")
_PURPLE=$(shell tput setaf 5 2> /dev/null || echo "")
_CYAN=$(shell tput setaf 6 2> /dev/null || echo "")
_WHITE=$(shell tput setaf 7 2> /dev/null || echo "")
_END=$(shell tput sgr0 2> /dev/null || echo "")

MAKEFLAGS += --no-print-directory

SRC_FOLDER = src/

include files.mk

CXX = clang++
CXX_FLAGS = -g -O2 -Wall -Wextra -Werror -Weverything -Wno-c++98-compat -Wno-padded -Wno-c++98-compat-pedantic -D BASEPATH=\"$(BASEPATH)\"
CXX_FLAGS_DEPS = -MT $@ -MD -MP -MF $(@:.o=.d)
CXX_STD = -std=c++11
INC_FLAGS = -I ../common -I src
LFLAGS = -ldl -lpthread
FLAGS = $(CXX_FLAGS) $(CXX_FLAGS_DEPS) $(CXX_STD) $(INC_FLAGS)

OBJ = \
		$(SRC_FILES:%.cpp=%.o) \

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ)
	@ printf "\\t%sLD%s\\t%s\\n" "$(_PURPLE)" "$(_END)" "$@"
	@ $(CXX) $(FLAGS) $(OBJ) -o $(NAME) $(LFLAGS)

%.o: %.cpp
	@ printf "\\t%sCC%s\\t%s\\n" "$(_GREEN)" "$(_END)" "$<"
	@ $(CXX) $(FLAGS) -c $< -o $@

#add dependencies files (*.d)
DEP_FILES = $(SRC_FILES:%.cpp=%.d)
-include $(DEP_FILES)

.PHONY: clean
clean:
	@ echo "Objects removed"
	@ rm -rf $(OBJ)
	@ rm -rf $(DEP_FILES)

.PHONY: fclean
fclean: clean
	@ echo "Program $(NAME) removed"
	@ rm -rf $(NAME)

.PHONY: re
re:
	@ make fclean
	@ make all
