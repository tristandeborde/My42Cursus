# Phase 2 - Pantoufle

Le but de cette phase est de commencer une interaction avec l'utilisateur et notamment la mise en place d'un menu, d'une pause ainsi que des paramètres, ainsi que de pouvoir changer au run-time de librairies graphiques.

Il faut qu'à la fin de cette phase, on puisse commencer à utiliser le programme de manière normal, à savoir : on lance le programme, on modifie les paramètres, on lance une partie, on met sur pause, on revient sur le menu, on quitte le programme.

## Logger

Nous allons passer par un Logger pour se simplifier la vie, ce logger a pour but de pouvoir comprendre et à un certain moment debugger notre programme. Nous devrons logger toutes les 'changements' et les appels de fonctions importants. On ne va pas logger les calculs par exemple.

Vu l'organisation de notre système, notre logger devra logger toutes les informations que nous envoie la librairie graphique, afin de pouvoir debugger efficacement la communication entre le core et les librairies graphiques.

## Menu / Paramètres

Il faut que core soit capable d'envoyer ainsi que d'interpréter toutes les actions concernant les menus et les paramètres que l'on peut envoyer à une librairie graphique.

## Implémentation d'une autre librairie graphique

Pour cette phase, il faut qu'une autre interface graphique soit possible. Il est important ici que cette interface graphique ne soit pas dans le terminal mais ouvre une fenêtre, comme par exemple : SDL, SFML, OpenGL...

## Changement d'interface graphique au runtime

Quand on appuie sur la touche 1, on se place sur l'interface graphique nouvellement implémetée qui est aussi l'interface graphique par défaut (celle qui est lancé au démarrage), et quand on appuie sur 2, on se place sur l'interface graphique faite en ncurses.

Il faut que ce changement soit effectif sur les 2 interfaces graphiques.

## Interface de communication

Voici la nouvelle interface de communication, elle est censé être suffisamment documenté pour que l'on puisse la comprendre sans avoir plus d'explication ou de documentation externe.

```h
#ifndef LIBMEDIA_INTERFACE_H
# define	LIBMEDIA_INTERFACE_H

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
# else	// ifdef __cplusplus
#  include <stddef.h>
# endif	// ifdef __cplusplus


typedef size_t t_id;


/*****************************************************************************/
/**                                   GAME                                  **/
/*****************************************************************************/

typedef enum			e_case{
	EMPTY,
	WALL,
	PLAYER,
	BOMB,
	FRUIT,
	EXPLOSION
}						t_case;

typedef struct			s_item{
	t_case type;
	size_t x;
	size_t y;
	// x and y will be changed in phase 3 to double
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
	char *	   title;
	t_status_b status;
}						t_button;

typedef struct			s_menu{
	char *	   title;
	t_button * li_buttons;
	size_t	   nb_buttons;
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
	MENU
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

void					libmedia_begin(void);
void					libmedia_end(void);

void					libmedia_drawgame(size_t width, size_t height, t_item * items, size_t nb_items);
void					libmedia_drawmenu(t_menu menu);

t_input					libmedia_input(void);

const char * libmedia_getlog(void);

# ifdef __cplusplus
}
# endif	// ifdef __cplusplus

#endif	// ifndef LIBMEDIA_INTERFACE_H

```
