IGraphic => interface qui donne le pointeur sur n'importe quelle lib graphique
DLLoader =>	classe qui permet de load une librairie, (et d'obtenir un pointeur IGraphic *)

Sdl/graphicSdl => classe qui hérite de IGraphic.

Voilà comment ca se passe :
1) le DLLoader load la librairie qu'on lui passe en parametre constructeur
2) ensuite on fait apelle a la DLLoader.getInstance().
	2)1) getInstance va utiliser la fonction create qui est présente dans sdl.c pour nous renvoyer un (GraphicSdl *) (un pointeur sur la classe sdl)
3) comme graphicSdl hérite de IGraphic, on peut cast le (GraphicSdl *) en un (IGraphic *)!
4) Ca permet donc au DLLoader de nous renvoyer un (IGraphic *) qui en fait sera soit la classe sdl, soit la classe opengl, soit la class ncurses (..)




Ce qu'on attend de toi c'est que tu garde le même principe sauf que au lieu de load des libraires graphiques, c'est des libraires
d'IA qu'il faudra load, mais l'idée est la même.
Je pense qu'il faudra que tu vois avec theo et thibaud quelle interface ils veulent pour leur IA...


Renseigne toi sur :
DLLoader.cpp :
dlhandle = dlopen(lib.c_str(), RTLD_LAZY);

Il me semble que si on change le RTLD_LAZY ca rend le truc plus simple.
