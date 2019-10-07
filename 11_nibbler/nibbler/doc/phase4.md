# Phase 4 - psylle (Charmeur de serpents)

La phase 4 est une phase courte.

Il y a 2 buts dans cette phase:

- Relire et finir le projet Nibbler.
- Mettre en place la musique

## Partie de Nibbler

Il faut qu'au lancement d'une partie on ait le choix entre une partie customisable (lancement d'un menu/paramètres) ou une partie de Snake (avec des paramètres bien choisis).

## Projet Nibbler

Il faut que la spécification du projet Nibbler (sur l'intra) soit respectée. Il faut donc relire le document attentivement et lister les features qui resteront à implémenter, et donc les implémenter.

## libmedia update sound

On doit alors rajouter une fonction dans libmedia qui permet de jouer un son

```h

#ifndef LIBMEDIA_INTERFACE_H
# define	LIBMEDIA_INTERFACE_H

[...]

typedef enum	e_sound {
	[...] // remplir la liste
}				t_sound;

void		libmedia_playsound(t_sound sound);

[...]

#endif

```

Il faut décider du comportement suivant: que fait-on si un son est joué si le son précédent est encore en train d'être jouer.

Il peut y avoir 3 comportements:

- On joue par dessus le son précédent (on ignore)
- On coupe le son précédent et on joue le nouveau
- Ça dépend des sons joués

Il faut donc réfléchir à tout ça et décider du comportement.

## Supprimer la librairie std

La librairie est inutile et ressemble à la librairie ncurses. Elle ne présente aucun intérêt.
Ncurses est donc la nouvelle librarie utilisé par défaut.

## Résoudre tous les bugs

Il s'agit ici de tracker les issues marqués par le label bug et de les résoudre. (Sur github)
 