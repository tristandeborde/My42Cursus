# Rules

Ce document présente la liste des règles ainsi que ces conséquences sur le gameplay.

Chaque règle appartient à un groupe de règles représenté par un domaine et un préfix. Par exemple Move avec (M-).

On pourrait également représenter un sous groupe de règles en allongeant le préfixe pour gagner en compréhension. Par exemple (MP-) pour les déplacements d'un joueur.

On définit des règles par des types, à savoir booléen, entier, custom ou une liste de types.

Il se peut que des types pour les règles soient trop long pour être mis dans le tableau (et cela réduirait la lisibilité). Il y a donc un tableau d'association entre des noms choisis et leur vrai type.

## Party

| Identifiant | Nom court | Type | Default | Description |
|:----------- |:--------- |:---- |:-------:|:----------- |
| P1001 | Window Width | Integer(15 - 40) | 20 | Le nombre de cases sur une ligne |
| P1002 | Window Height | Integer(15 - 40) | 20 | Le nombre de cases sur une colonne |
| P1003 | Nb Players | Integer(1 - 8) | 4 | Le nombre de joueurs au total dans une partie |
| P1004 | Bot Difficulty | C_Bot | noob | Un degré d'intelligence d'un bot |
| P1005 | Surround Walls | Boolean | True | La présence de murs autour de la carte, si ce paramètre est faux, toute entité allant vers un bord se retrouve téléportée vers le côté opposé |
| P1006 | Destructible Walls | Boolean | True | La présence au lancement de la partie de murs destructibles par des bombes par exemple |
| P1007 | Game End | L_End | [ No_HP, Collision ] | Les conditions de fin d'une partie |
| P1010 | Has Body | Boolean | False | Le joueur a un corps (initial de taille 1) qui augmente de 1 lorsqu'il mange un fruit |
| P1011 | Speed Increase | Boolean | True | La vitesse du joueur augmente au fur et à mesure que le temps s'écoule |
| P1012 | Drop Bomb | Boolean | True | Le joueur peut poser une bombe à l'endroit où il est |
| P1021 | Spawn Obj Init | L_Objects | [] | La liste des objets qui peuvent apparaître au début d'une partie |
| P1022 | Spawn Obj Game | L_Objects | [] | La liste des objets qui peuvent apparaître au cours d'une partie |
| P1023 | Frequency Obj Init | C_Freq | normal | Paramètre influant sur la quantité d'objets apparaissant au début de la partie |
| P1024 | Frequency Obj Game | C_Freq | normal | Paramètre influant sur la quantité d'objets apparaissant au cours de la partie |

## Move

| Identifiant | Nom court | Type | Default | Description |
|:----------- |:--------- |:---- |:-------:|:----------- |
| M2001 | Autorun | Boolean | False | Le joueur se déplace de manière automatique dans une direction. Il ne peut alors que changer cette direction (comme dans un Snake) |

## Tableau d'association

| Nom utilisé | Vrai type |
|:----------- |:--------- |
| C_Bot | Custom { noob } |
| C_Freq | Custom { very rare, rare, normal, frequent, very frequent, one by one } |
| C_Object | Custom { fruit, bomb } |
| L_Objects | List { C_Object } |
| C_End | Custom { collision, no HP, score limit } |
| L_End | List { C_End } |
