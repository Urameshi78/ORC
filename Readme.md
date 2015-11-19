Les fichiers sources / include se trouvent dans OCR_QT
QT5 ainsi que OpenCv 2.4 ont été utiliser pour ce Projet

Petit rappel :

Utilisation d'un seuillage automatique
Utilisation du perceptron



IMPORTANT : Il y a different champs en dur dans le code, ces champs correspondent à l'emplacement ou le fichier sera crée.
Utilisation du path Absolue obligatoire a cause de QT ><

Pour lancer le projet : sudo ./qtcreator , ensuite ouvrez le OCR.pro situé dans OCR_QT puis cliqué sur la fleche verte en bas a gauche. (mod release de preference)

ocr.pro contient le meme type d'information qu'un Makefile

COMMENT UTILISEZ LA GUI ???

3 "ECRAN" et une fenetre apparaissent.

La fenetre : Indiquez le caractere que vous voulez reconnaitre.
(C'est le path pour Predicaracter)

LOAD : RE-SET LE PATH POUR PREDICARACTER

LEARN : Indiquez le chemin absolu de vos sample_set 

QUIT  : obvious
