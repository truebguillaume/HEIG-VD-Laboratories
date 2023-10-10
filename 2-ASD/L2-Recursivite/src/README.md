# Notes de design
## Architecture
Les fichiers `pieces.cpp` et `pieces.h` étant en lecture seule (comme écrit dans l'énoncé),
un fichier supplémentaire (`piece_utils.h` & `piece_utils.cpp`) est nécessaire pour fournir les fonctions utilitaires nécessaires
au bon fonctionnement du programme.

## Tests
Afin de pouvoir répartir correctement le travail entre les membres du groupe, il a été décidé d'utiliser des
tests unitaires pour garantir le fonctionnement correct de chaque fonction ayant une difficulté de compréhension.

Pour permettre cela, la librairie `doctest` est utilisée. Elle est importée en tant que fichier header (`.h`) 
dans le dossier source à l'addresse suivante: [src/doctest.h](./doctest.h).

> **Note**
> Le fichier est généré automatiquement, il n'a pas été écrit a la main.
