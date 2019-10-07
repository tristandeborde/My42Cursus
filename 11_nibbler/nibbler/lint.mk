#                            _                 __
#                    __.--**"""**--...__..--**""""*-.
#                  .'                                `-.
#                .'                         _           \
#               /                         .'        .    \   _._
#              :                         :          :`*.  :-'.' ;
#              ;    `                    ;          `.) \   /.-'
#              :     `                             ; ' -*   ;
#                     :.    \           :       :  :        :
#               ;     ; `.   `.         ;     ` |  '
#               |         `.            `. -*"*\; /        :
#               |    :     /`-.           `.    \/`.'  _    `.
#               :    ;    :    `*-.__.-*""":`.   \ ;  'o` `. /
#                     ;   ;                ;  \   ;:       ;:   ,/
#                |  | |            [bug]      /`  | ,      `*-*'/
#                `  : :  :                /  /    | : .    ._.-'
#                 \  \ ,  \              :   `.   :  \ \   .'
#                  :  *:   ;             :    |`*-'   `*+-*
#                   `**-*`""               *---*

###############################################################################
###################                 LINTING                 ###################
###############################################################################

_EXCEPT_DIRS = \
			./uncrustify \
			./venv \
			./.git \
			./.vscode \

EXCEPT_DIRS = \
			$(foreach dir, $(_EXCEPT_DIRS), -not -path "$(dir)*") \
			-not -path "." \

ALL_DIRS = $(shell find . -type d $(EXCEPT_DIRS))

ALL_FILES = $(shell find . -name "*.[cht]pp" $(EXCEPT_DIRS) -o -name "*.[ch]" $(EXCEPT_DIRS))
SRC_FILES = $(shell find . -name "*.[ct]pp" $(EXCEPT_DIRS))
IFLAGS = $(foreach dir, $(ALL_DIRS), -I $(dir))

BREW_PATH = ~/.brew
# lib SDL2 on macs with brew
ifeq ($(shell [ -d $(BREW_PATH) ]; echo $$?), 0) 
    IFLAGS += -isystem $(BREW_PATH)/include
endif

MAKE = make -f lint.mk

# Checks with all tools
.PHONY: all
all: check

.PHONY: check
check:
	$(MAKE) uncrustify_check
	$(MAKE) cpplint
	$(MAKE) cppcheck
	$(MAKE) clang_tidy

# Auto fix when it is possible
.PHONY: apply
apply:
	$(MAKE) uncrustify_apply

# handling submdules
.PHONY: submodule
submodule:
	git submodule init
	git submodule update

# handling venv
venv:
	python3 -m venv venv
	venv/bin/pip3 install pip --upgrade
	venv/bin/pip3 install cpplint
	venv/bin/pip3 install progressbar

################################ UNCRUSTIFY ###################################

UNCRUSTIFY = uncrustify/build/uncrustify
CONFIG_UNCRUSTIFY = .lint_uncrustify.cfg

$(UNCRUSTIFY): submodule
	mkdir -p uncrustify/build
	(cd uncrustify/build && cmake ..)
	make -C uncrustify/build -j8

.PHONY: uncrustify_apply
uncrustify_apply: $(UNCRUSTIFY)
	$(UNCRUSTIFY) -c $(CONFIG_UNCRUSTIFY) -l CPP --replace --no-backup --mtime $(ALL_FILES)

.PHONY: uncrustify_check
uncrustify_check: $(UNCRUSTIFY)
	$(UNCRUSTIFY) -c $(CONFIG_UNCRUSTIFY) -l CPP --check $(ALL_FILES)

################################# CPPLINT #####################################

CPPLINT = venv/bin/cpplint

_CPPLINT_FLAGS = \
				-legal \
				-whitespace \
				-readability/braces \
				-readability/namespace \
				-readability/casting \
				-build/header_guard \
				-runtime/references \
				-runtime/int \
				-build/include_what_you_use \
				-build/include \
				-build/c++11 \
				-runtime/indentation_namespace \

CPPLINT_FLAGS = $(shell echo $(foreach flag, $(_CPPLINT_FLAGS), $(flag)) | xargs | tr -s ' ' | tr ' ' ',')

.PHONY: cpplint
cpplint: venv
	$(CPPLINT) --filter=$(CPPLINT_FLAGS) $(ALL_FILES)

################################# CPPCHECK ####################################

CPPCHECK = cppcheck

.PHONY: cppcheck
cppcheck:
	$(CPPCHECK) --error-exitcode=1 --enable=all --suppress=missingIncludeSystem --suppress=unusedFunction $(IFLAGS) $(SRC_FILES)

CLANG_TIDY = clang-tidy-6.0

WARNS_EXCEPTS = \
				android-cloexec-fopen \
				cppcoreguidelines-owning-memory \
				cppcoreguidelines-special-member-functions \
				cppcoreguidelines-pro-bounds-pointer-arithmetic \
				cppcoreguidelines-pro-bounds-array-to-pointer-decay \
				cppcoreguidelines-pro-bounds-constant-array-index \
				cppcoreguidelines-pro-type-union-access \
				cppcoreguidelines-pro-type-cstyle-cast \
				llvm-header-guard \
				llvm-include-order \
				google-readability-braces-around-statements \
				google-readability-namespace-comments \
				google-runtime-references \
				hicpp-braces-around-statements \
				hicpp-signed-bitwise \
				hicpp-special-member-functions \
				hicpp-no-array-decay \
				hicpp-use-emplace \
				readability-braces-around-statements \
				readability-named-parameter \
				readability-delete-null-pointer \
				readability-simplify-boolean-expr \
				fuchsia-overloaded-operator \
				fuchsia-default-arguments \
				modernize-pass-by-value \
				modernize-use-emplace \
				modernize-use-using \
				modernize-redundant-void-arg \
				cert-err58-cpp \
				cert-msc30-c \
				cert-msc50-cpp \

WARNS = $(shell echo "*$(foreach warn,$(WARNS_EXCEPTS),,-$(warn))" | tr -d ' ')

.PHONY: clang_tidy
clang_tidy:
	$(CLANG_TIDY) \
		-checks="$(WARNS)" \
		-header-filter=".*" \
		-warnings-as-errors="*" \
		-extra-arg=-std=c++11 \
		$(SRC_FILES) -- $(IFLAGS) \

.PHONY: clang_tidy_fix
clang_tidy_fix:
	$(CLANG_TIDY) \
		-checks="$(WARNS)" \
		-header-filter=".*" \
		-fix-errors \
		$(SRC_FILES) -- $(IFLAGS) \
