#                        .^.,*.
#                       (   )  )
#                      .~       "-._   _.-'-*'-*'-*'-*'-'-.--._
#                    /'             `"'                        `.
#                  _/'                                           `.
#             __,""                                                ).--.
#          .-'       `._.'                                          .--.\
#         '                                                         )   \`:
#        ;                                                          ;    "
#       :                                                           )
#       | 8                                                        ;
#        =                  )                                     .
#         \                .                                    .'
#          `.            ~  \                                .-'
#            `-._ _ _ . '    `.          ._        _        |
#                              |        /  `"-*--*' |       |  mb
#                              |        |           |       :
#    ~~~~~~~---   ~-~-~-~   -~-~-~-~-~-~~~~~~  ~~~~  ~-~-~-~-~-~-~-
#   ------~~~~~~~~~----------~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~
#    ~~~~~~~~~   ~~~~~~~~~       ~~~~~~~   ~~~~~~~~~  ~~~~~~~~~~~~~~~


NAME_CORE = bombler
DIR_CORE = core/

LIBS = \
		libmedia_ncurses \
		libmedia_sdl2 \
		libmedia_opengl

MAKEFLAGS += --no-print-directory

ALL_DIRS = \
		$(DIR_CORE) \
		$(LIBS) \

.PHONY: all
all:
	@ make compile

###############################################################################
###################               COMPILATION               ###################
###############################################################################

.PHONY: compile
compile:
	@ make -C $(DIR_CORE) BASEPATH=${CURDIR}
	@ test -f $(NAME_CORE) || ln -s $(DIR_CORE)bombler $(NAME_CORE)
	@ $(foreach lib, $(LIBS), make -C $(lib) BASEPATH=${CURDIR};)
	@ $(foreach lib, $(LIBS), test -f $(lib).so || ln -sf $(lib)/$(lib).so $(lib).so;)

.PHONY: clean
clean:
	@ rm -f $(NAME_CORE)
	@ $(foreach dir, $(ALL_DIRS), make -C $(dir) clean;)
	@ $(foreach lib, $(LIBS), rm -f $(lib).so)

.PHONY: fclean
fclean: clean
	@ $(foreach dir, $(ALL_DIRS), make -C $(dir) fclean;)

.PHONY: re
re:
	@ make fclean
	@ make all

###############################################################################
###################                  LINT                   ###################
###############################################################################

.PHONY: lint
lint:
	@ make -f lint.mk

.PHONY: test_local
test_local: fclean
	@ bash tests/test_local.bash
