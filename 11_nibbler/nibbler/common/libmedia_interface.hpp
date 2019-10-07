#ifndef LIBMEDIA_INTERFACE_HPP
# define	LIBMEDIA_INTERFACE_HPP

/**
 *
 *	This interface is generic and global to all the code present in this project, for the core and for all the libraries connected to Core.
 *
 *	The library will always get initiated with the libmedia_begin function and always finish with the libmedia_end function.
 *
 *	A game loop is present in the Core, and every function will be called in a frame. None of the functions must block the current thread/process.
 *
 *	while (running)
 *	{
 *		[...]	Handle input and its log
 *		[...]	process input
 *		[...]	libmedia_draw{game|menu}(...);
 *		[...]	manage log from libmedia
 *		[...]	wait until next frame
 *	}
 *
 *	The functions libmedia_draw{game|menu} will draw the {game|menu} according to the argument.
 *
 *	On every function f called, the function libmedia_getlog will be called to log messages in order that they appears in the previous function f.
 *
 *	The program is always is one of the two following modes:
 *		- game
 *		- menu
 *
 *	The functions getlog and getinput are called until nothing is given. They work like a FIFO structure. For log for example, we want to log strings in order.
 *
 *	If the library is crashing somehow and returns a t_input with has_crash boolean field set to 1 (or a non zero value), the core will still call the libmedia_end().
 */

# ifdef __cplusplus
extern "C" {
# endif	// ifdef __cplusplus

// Header needed for size_t
# ifdef __cplusplus
#  include <cstddef>
#  include <cstdint>
# else	// ifdef __cplusplus
#  include <stddef.h>
#  include <stdint.h>
# endif	// ifdef __cplusplus


typedef	size_t t_id;


/*****************************************************************************/
/**                                   GAME                                  **/
/*****************************************************************************/

typedef enum			e_case{
	EMPTY,
	WALL,
	PLAYER,
	BOMB,
	FRUIT,
	EXPLOSION,

	/* To determine the sprite of the snake entity,
	 * we compose it with binary masks, on 1 byte.
	 *
	 * the 4 lesser bits represent the direction.
	 * 1 or 2 of those bits can be activated.
	 *
	 * the 2 upper bits represent either the head,
	 * the tail or the body of the snake.
	 * the head and the tail must have 1 direction bit set,
	 * and the body must have 2 direction bit.
	 *
	 *
	 * the value is constructed by the following operation:
	 * SPRITE_NAME = SPRITE_VALUE + DIRECTION_VALUE,
	 *
	 * thus,
	 * SNAKE_HEAD_*	= 0x40 + 1bit for direction
	 * SNAKE_TAIL_*	= 0x80 + 1bit for direction
	 * SNAKE_*		= 0xC0 + 2bit for direction
	 */
	SNAKE_HEAD_UP	 = 0x48,
	SNAKE_HEAD_RIGHT = 0x44,
	SNAKE_HEAD_DOWN	 = 0x42,
	SNAKE_HEAD_LEFT	 = 0x41,

	SNAKE_TAIL_UP	 = 0x88,
	SNAKE_TAIL_RIGHT = 0x84,
	SNAKE_TAIL_DOWN	 = 0x82,
	SNAKE_TAIL_LEFT	 = 0x81,

	SNAKE_UP_DOWN	 = 0xCA,
	SNAKE_RIGHT_LEFT = 0xC5,

	SNAKE_UP_RIGHT	 = 0xCC,
	SNAKE_RIGHT_DOWN = 0xC6,
	SNAKE_DOWN_LEFT	 = 0xC3,
	SNAKE_LEFT_UP	 = 0xC9
}						t_case;

typedef struct			s_item{
	t_case type;
	float  x;
	float  y;
}						t_item;

typedef enum			e_game_action{
	GAME_UP,
	GAME_DOWN,
	GAME_RIGHT,
	GAME_LEFT,
	GAME_DROP_BOMB
}						t_game_action;

typedef t_game_action t_game_input;

/*****************************************************************************/
/**                                   MENU                                  **/
/*****************************************************************************/

typedef enum			e_menu_action{
	MENU_CLICK
}						t_menu_action;

typedef enum			e_status_b{
	NORMAL,
	SELECTED
}						t_status_b;

typedef struct			s_button{
	const char * title;
	t_status_b	 status;
}						t_button;

typedef struct			s_menu{
	const char * title;
	t_button *	 li_buttons;
	size_t		 nb_buttons;
}						t_menu;

typedef struct			s_input_menu{
	t_menu_action act;
	t_id		  bid;
}						t_menu_input;

/*****************************************************************************/
/**                                  COMMON                                 **/
/*****************************************************************************/

typedef enum	e_type_input{
	NO_INPUT,
	CRASH,
	RCHANGE,
	ECHAP,
	GAME,
	MENU,
	EXIT
}				t_type_input;

typedef struct	s_input{
	t_type_input type;
	union {
		int	rchange;
		// change runtime library
		// must be set to the curresponding digit on the keyboard
		// if no button was pressed, must be zero
		t_menu_input menu;
		t_game_input game;
	} u_input_raw;
	// union of actions depending of mode
}				t_input;


class ILibMedia{
	public:
		virtual void         libmedia_begin(void) = 0;
		virtual void         libmedia_end(void)	  = 0;
		virtual void         libmedia_drawgame(size_t width, size_t height, t_item * items, size_t nb_items,
			uint32_t score) = 0;
		virtual void         libmedia_drawmenu(t_menu menu) = 0;
		virtual t_input      libmedia_input(void)  = 0;
		virtual const char * libmedia_getlog(void) = 0;

		virtual~ILibMedia(void);
};

ILibMedia * getLib();

# ifdef __cplusplus
}
# endif	// __cplusplus

#endif	// ifndef LIBMEDIA_INTERFACE_HPP
