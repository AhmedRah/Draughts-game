# Projet Reseau Jeu de dame
<h3>RAHMOUNI Ahmed & BAH Elhadj Oumar</h3>

<h4>Introduction</h4>
Dans ce projet , on creer un jeu de dame multi-joueurs , a travers un serveur local sur le port 8888 .<br/>
Le programme est compose de plusieurs fichiers dans different repertoires :<br/>
    - repertoire include : contient tout nos fichiers  .h ,qui definissent la majorite des fonctions utiliser dans nos fichiers sources.<br/>
    - repertoire obj : contient les fichiers binaires , et fichiers systems.<br/>
    - repertoire bin : Contient les fichiers executables <italic>(Prog server et Prog Client)</italic><br/>
    - repertoire src : Contient tout nos fichiers .c ,i.e: server.c client.c<br/> 
    - Dans le repertoire root du rendu , vous trouverez le makefile pour la compilation ainsi que les fichiers datas , pour les identifications , chargement des parties ...<br/> 

<h4>Fonctionnement</h4>
Notre rendu est divisee en plusieurs fichiers principaux : <br/>
1)client et serveur &  com_functions :<br/>
- les deux partagent la majorite des fonctions de gestion de communication ainsi que les varibales globales.<br/>
2) Game.c et headerfiles.h :<br/>
- ces fichiers contiennent le jeu , les mechanismes de deplacement , creeations des parties , chargement des parties , valdiations des deplacements ...<br/>
3) identification.c &.h :<br/>
- ces fichiers traitent tout ce qui concerne l'identification des joueurs, contient deux fonctions (log_in() et sign_in())<br/>


