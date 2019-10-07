# Phase 3 - Alpage

Nous avons 5 buts dans cette phase:

- Mise en place de murs destructibles
- Mise en place de la mecanique des bombes
- Faire en sorte que toutes les coordonnées du jeu deviennent des flottants
- Mettre en place et travailler sur une librairie graphique basé sur OpenGL
- Pouvoir mettre en fullscreen
- Travailler sur le gameplay et la mise en place des règles

## Mise en place de murs destructibles

Il faut que les bombes puissent détruire des murs destructibles comme dans un vrai Bomberman.

## Mise en place de la mecanique des bombes

Les bombes vont avoir un certain nombre d'attributs:

- Un joueur peut traverser ses propres bombes
- Un joueur ne peut pas traverser les bombes de ses adversaires
- Une bombe fait une explosion en croix de 5x5 cases
- L'explosion des bombes se propage de manière progressive (0.5s pour s'étendre d'une case par exemple)

**Explosion des bombes**
```
+-------+
|   #   |
|   #   |
| ##### |
|   #   |
|   #   |
+-------+
```

## Adaptation de l'interface et changement des libraries déjà implémentées

Il s'agit ici de changer les coordonnées en flottants à savoir:

```h

typedef struct			s_item
{
	t_case			type;
	size_t			x;
	size_t			y;
}						t_item;

```

into

```h

typedef struct			s_item
{
	t_case			type;
	float			x;
	float			y;
}						t_item;

```

Il faut alors changer l'interface et adapter les librairies implémentées avec cette nouvelle interface. Pour les libraries à affichage discret (à savoir sdl, ncurses), un simple arrondi sera fait.

## Librarie OpenGL

La librarie OpenGL devra afficher des modèles 3d dans un gameplay 2d, à la Super Mario.
Il faut que le jeu fasse professionnel, travaillé, et détaillé.

La librairie devra alors avoir des animations de déplacement, des animations pour les bombes qui vont exploser ainsi que les explosions elles-mêmes.

Il doit bien évidemment implémenter l'interface actuelle et il faut que l'on puisse le mettre en fullscreen (void en dessous).

## Fullscreen

Il faut que l'on puisse mettre en fullscreen les implémentations des librairies qui le permettent. Par exemple (SDL2, OpenGL). Ce paramètre, le fullscreen ne doit pas être envoyé au Core, la librairie devra faire tous les calculs pour afficher correctement les entités qu'on lui donne, que ce soit dans le menu ou dans le jeu.

## Gameplay

Core doit être capable de suivre un jeu de règles stricts qui vont dicter comment fonctionne une partie. L'idée est de mettre en place ici l'essence même de notre jeu. Réussir à construire une interface viable qui donne un gameplay unique lorsaue l'on change des paramètres.
