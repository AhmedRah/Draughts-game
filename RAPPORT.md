# Projet Reseau Jeu de dame
<h3>RAHMOUNI Ahmed & BAH Elhadj Oumar</h3>

<h4>Introduction</h4>
Dans ce projet , on creer un jeu de dame multi-joueurs , a travers un serveur local sur le port 8888 .
Le programme est compose de plusieurs fichiers dans different repertoires :
    - repertoire include : contient tout nos fichiers  .h ,qui definissent la majorite des fonctions utiliser dans nos fichiers sources.
    - repertoire obj : contient les fichiers binaires , et fichiers systems.
    - repertoire bin : Contient les fichiers executables <italic>(Prog server et Prog Client)</italic>
    - repertoire src : Contient tout nos fichiers .c ,i.e: server.c client.c 
    - Dans le repertoire root du rendu , vous trouverez le makefile pour la compilation ainsi que les fichiers datas , pour les identifications , chargement des parties ... 

<h4>Fonctionnement</h4>
Notre rendu est divisee en plusieurs fichiers principaux : 
1)client et serveur &  com_functions :
- les deux partagent la majorite des fonctions de gestion de communication ainsi que les varibales globales.
2) Game.c et headerfiles.h :
- ces fichiers contiennent le jeu , les mechanismes de deplacement , creeations des parties , chargement des parties , valdiations des deplacements ...
3) identification.c &.h :
- ces fichiers traitent tout ce qui concerne l'identification des joueurs, contient deux fonctions (log_in() et sign_in())


