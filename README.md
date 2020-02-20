Fdf project 42 by hcabel.

Ce projet consiste à afficher graphiquement la représentation schématique d’un terrain en relief.

Les fonctions autoriser :
Open, Read, Write, Close, Malloc, Free, Perror, Strerror, Exit,
Toutes les fonctions de la lib math ,Toutes les fonctions de la miniLibX.

![screen map 42.fdf](img/screen1)

Il suffit de crée de maps comme cela :
0 0 0 0 0 0 0
1 2 3 0 3 2 1
0 0 0 0 0 0 0
12 43 0 -14 0 89 0
1 1 1 1 1 1 1
1 2 2 2 2 2 1
1 2 3 3 3 3 1

Bref se que vous voulez sachant que chaque nouveaux nombre est un nouveaux point et que la valeur correspond
à sont axes de hauteur ( z ).
( la map doit êtres un carré ou un rectangle :D )

pour lancer:
make && ./fdf world/mars.fdf
