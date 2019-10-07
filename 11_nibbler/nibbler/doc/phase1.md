# Phase 1 - Soucoupe volante

Le but de cette phase est de mettre en place notre mode de développement, de poser les bases pour la suite.

Je soutiens ici que l'on souhaite avoir un premier résultat rapide (moins de 5 jours) pour ensuite travailler dessus et l'ameéliorer.

## Interface de communication

Il s'agit ici de mettre en place l'interface de communication entre le core et une seule librairie graphique.

Voici l'interface que l'on va adopter:

```h
#ifndef INTERFACE_H
# define INTERFACE_H

typedef enum	e_case
{
	EMPTY,
	WALL,
	PLAYER,
	BOMB,
	FRUIT,
	EXPLOSION,
}				t_case;

typedef enum	e_action
{
	NOTHING,
	UP,
	RIGHT,
	DOWN,
	LEFT,
	DROP_BOMB,
}				t_action;

void		libg_begin(void);
void		libg_end(void);

void		libg_drawmap(int width, int height, t_case **map);

t_action	libg_action(void);

#endif
```

Les fonctions libg_{begin|end} sont appelées respectivement au début et à la fin de l'utilisation de la librairie.

La fonction libg_drawmap permet d'afficher une grille de jeu de manière statique.

La fonctions libg_action demande à la librarie graphique si une entrée quelconque de l'utilisateur a été faite à un intervalle régulier.

Cette interface doit être respecté par une librairie graphique en ncurses ou dans un terminal classique afin de pouvoir avoir une version fonctionnelle fiable pour la suite. Cette version sera peut-être supprimé par la suite.

## Graphics Loader

Il s'agit ici de créer une classe qui va abstraire l'utilisation des sous lib et qui va s'occuper de toute la partie chargement, vérification ainsi que la création des erreurs (exceptions) adaptés.

C'est notamment dans cette classe que sera utiliseé les fonctions dl*, (dlopen, dlclose, dlsym et dlerror)

## Core

Il faut mettre en place tout une série de classe afin de pouvoir bouger un personnage et que des premières bombes puissent exploser tranquillement.
