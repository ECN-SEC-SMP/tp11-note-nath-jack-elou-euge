# TP 11

## Participants

- Jack HASCOËT
- Natha ANDRE
- Eugénie ROQUAIN
- Eloi TOURANGIN

---

## Table des matières

1. [Build & Compilation](#build--compilation)
2. [Tests](#tests)
3. [Explications et algorithmes](#explications-et-algorithmes)
   - [Fonctionnement de la classe Board](#fonctionnement-de-la-classe-board)
   - [Algorithmes de génération](#algorithmes-de-génération)
4. [Exemples d'utilisation](#exemples-dutilisation)

---

## Build & Compilation

### Build

Pour construire le projet, exécutez les commandes suivantes dans un terminal :

```bash
mkdir build
cd build
cmake ..
```

Compiler

```bash
make
```

## Tests

Tests must be done inside class file.

## Explications et algorithmes

### Fonctionnement de la classe Board

La classe `Board` représente une grille de jeu de 16x16 cases utilisée pour un jeu de type puzzle. Elle contient des méthodes pour générer la grille, placer des murs, des angles, des robots, et des cibles.

#### Fonctionnement

1. **Attributs principaux :**
   - `board[16][16]` : Tableau 2D de cases représentant la grille de jeu. Chaque case peut contenir des murs, un robot, ou une cible.

2. **Méthodes privées :**
   - `GenerateBoardStep1` : Ajoute les murs extérieurs de la grille et les murs formant un carré central.
   - `GenerateBoardStep2` : Ajoute deux murs extérieurs aléatoires (un vertical et un horizontal) dans chaque quart de la grille.
   - `GenerateBoardStep3` : Ajoute 4 "angles" (deux murs formant un coin) dans chaque quart de la grille, en s'assurant qu'ils ne touchent pas d'autres murs ou angles.
   - `GenerateBoardStep4` : Ajoute un angle supplémentaire dans un quart choisi aléatoirement, en respectant les mêmes contraintes.

3. **Méthodes publiques :**
   - `GenerateBoard` : Génère la grille complète en appelant les étapes 1 à 4.
   - `PlaceRobots` : Place aléatoirement 4 robots sur la grille, ainsi qu'une cible dans un angle de deux murs.
   - `getBoard` : Retourne la grille de jeu.
   - Constructeur et destructeur : Initialisent et nettoient la grille.

### Algorithmes de génération

Voici l'algorithme en langage naturel pour générer une grille complète :

```algo
type Case
    entier nord
    entier sud
    entier est
    entier ouest
    lien Robot robot
    lien Target cible
fin type

type Board
    tableau[16][16] de Case grille
fin type
```

```algo
fonction ø <- GenerateBoard(B)
algorithme
    appeler GenerateBoardStep1(B)
    appeler GenerateBoardStep2(B)
    appeler GenerateBoardStep3(B)
    appeler GenerateBoardStep4(B)
fin fonction
```

```algo
fonction ø <- GenerateBoardStep1(B)
    paramètre lien Board B
    résultat ø
algorithme
    pour x allant de 0 à 15 faire
        B.grille[x][0].nord <- 1
        B.grille[x][15].sud <- 1
    fin pour

    pour y allant de 0 à 15 faire
        B.grille[0][y].ouest <- 1
        B.grille[15][y].est <- 1
    fin pour

    B.grille[7][7].nord <- 1
    B.grille[7][7].ouest <- 1
    B.grille[7][8].ouest <- 1
    B.grille[7][8].sud <- 1
    B.grille[8][7].nord <- 1
    B.grille[8][7].est <- 1
    B.grille[8][8].est <- 1
    B.grille[8][8].sud <- 1
fin fonction
```

```algo
fonction ø <- GenerateBoardStep2(B)
    paramètre lien Board B
    résultat ø
algorithme
    pour chaque quart de la grille faire
        générer x aléatoire dans les limites du quart
        générer y aléatoire dans les limites du quart

        si le mur ouest est dans le quart alors
            B.grille[x][0].ouest <- 1
        fin si

        si le mur est est dans le quart alors
            B.grille[x][15].est <- 1
        fin si

        si le mur nord est dans le quart alors
            B.grille[0][y].nord <- 1
        fin si

        si le mur sud est dans le quart alors
            B.grille[15][y].sud <- 1
        fin si
    fin pour
fin fonction
```

```algo
fonction ø <- GenerateBoardStep3(B)
    paramètre lien Board B
    résultat ø
algorithme
    pour chaque quart de la grille faire
        compteur angles <- 0
        tant que compteur angles < 4 faire
            générer x et y aléatoires dans les limites du quart
            si la case (x, y) n'est pas occupée par un mur ou un angle alors
                générer un type d'angle aléatoire
                si l'angle est valide (ne touche pas un autre angle ou mur extérieur) alors
                    placer l'angle en activant deux murs adjacents
                    incrémenter compteur angles
                fin si
            fin si
        fin tant que
    fin pour
fin fonction
```

```algo
fonction ø <- GenerateBoardStep4(B)
    paramètre lien Board B
    résultat ø
algorithme
    répéter
        générer x et y aléatoires dans toute la grille (hors murs extérieurs)
        si la case (x, y) n'est pas occupée par un mur ou un angle alors
            générer un type d'angle aléatoire
            si l'angle est valide (ne touche pas un autre angle ou mur extérieur) alors
                placer l'angle en activant deux murs adjacents
                arrêter la boucle
            fin si
        fin si
    jusqu'à ce qu'un angle soit placé
fin fonction
```

```algo
fonction ø <- PlaceRobots(B, robots)
    paramètre lien Board B
    paramètre tableau[4] de Robot robots
    résultat ø
algorithme
    compteur robots placés <- 0
    tant que compteur robots placés < 4 faire
        générer x et y aléatoires dans toute la grille (hors carré central)
        si la case (x, y) est libre (pas de robot, pas de cible) alors
            placer un robot sur la case
            incrémenter compteur robots placés
        fin si
    fin tant que

    répéter
        générer x et y aléatoires dans toute la grille
        si la case (x, y) contient un angle et est libre alors
            placer une cible sur la case
            arrêter la boucle
        fin si
    jusqu'à ce qu'une cible soit placée
fin fonction
```

