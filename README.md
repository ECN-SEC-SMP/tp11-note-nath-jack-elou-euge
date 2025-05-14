# TP 11 noté - Ricochet Robots

## Contributeurs

- [Jack HASCOËT](https://github.com/Jaaackoo)
- [Natha ANDRE](https://github.com/Nandros)
- [Eugénie ROQUAIN](https://github.com/euge13301)
- [Eloi TOURANGIN](https://github.com/ioleto)

## Table des matières

1. [Build & Compilation](#build--compilation)
2. [Tests](#tests)
3. [Explications et algorithmes](#explications-et-algorithmes)
    - [Classe Game](#classe-game)
    - [Classe Board](#classe-board)
        - [Algorithmes de génération](#algorithmes-de-génération)
4. [Exemples d'utilisation](#exemples-dutilisation)

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

## Classe Game

 Notre classe Game comprend deux classes : Board et Display. Elle permet d'initialiser le jeu et ainsi démarrer une partie.

 Dans notre classe Board on a 4 attributs :

- moveRobot() qui permet d'avancer les pions Robot en ligne jusqu'à un obstacle
- generateBoard() qui permet de générer de facon aléatoire notre plateau de jeu avec des obstacles, les cibles et les pions Robots
- CheckWall(x,y) qui prend en argument les coordonnées de la case et qui vérifie si notre pion robot est face à un mur
- CheckTarget(x,y) qui prend en argument les coordonnées de la case et qui vérifie si la case x,y à un pion robot ou non

 La classe Board utilise les enum Colors et Shapes qui ont respectivement chacune des couleurs des cibles et robots ainsi que les formes deux cibles

 Dans notre classe Display on a 2 arguments :

- Updates()
- Print()

 Notre classe Robot possède deux arguments :

- getShape()
- getColor()
- Robot(Enum Colors) qui lui attribut une couleur
- Robot(Color c, Shape s)

### Classe Board

La classe `Board` représente une grille de jeu de 16x16 cases utilisée pour un jeu de type puzzle. Elle contient des méthodes pour générer la grille, placer des murs, des angles, des robots, et des cibles.

#### Fonctionnement

1. **Attributs principaux :**
   - `board[16][16]` : Tableau 2D de cases représentant la grille de jeu. Chaque case peut contenir des murs, un robot, ou une cible.

2. **Méthodes privées :**
   - `generateBoardStep1` : Ajoute les murs extérieurs de la grille et les murs formant un carré central.
   - `generateBoardStep2` : Ajoute deux murs extérieurs aléatoires (un vertical et un horizontal) dans chaque quart de la grille.
   - `generateBoardStep3` : Ajoute 4 "angles" (deux murs formant un coin) dans chaque quart de la grille, en s'assurant qu'ils ne touchent pas d'autres murs ou angles.
   - `generateBoardStep4` : Ajoute un angle supplémentaire dans un quart choisi aléatoirement, en respectant les mêmes contraintes.

3. **Méthodes publiques :**
   - `generateBoard` : Génère la grille complète en appelant les étapes 1 à 4.
   - `placeRobots` : Place aléatoirement 4 robots sur la grille, ainsi qu'une cible dans un angle de deux murs.
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
fonction ø <- generateBoard(B)
algorithme
    appeler generateBoardStep1(B)
    appeler generateBoardStep2(B)
    appeler generateBoardStep3(B)
    appeler generateBoardStep4(B)
fin fonction
```

```algo
fonction ø <- generateBoardStep1(B)
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
fonction ø <- generateBoardStep2(B)
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
fonction ø <- generateBoardStep3(B)
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
fonction ø <- generateBoardStep4(B)
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
fonction ø <- placeRobots(B, robots)
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
### Fonctionnement de la classe Robot

La classe `Robot` représente ses caractéristiques : couleur (Color), forme (Shape), coordonnées en 2D (x, y)

#### Fonctionnement

1. **Attributs principaux :**
   -

2. **Méthodes privées :**
   - `color` :  couleur du robot
   - `shape` : forme du robot
   - `x` : position en x du robot
   - `y` : position en y du robot

3. **Méthodes publiques :**
   - Constructeur et destructeur : `Robot()` : Crée un robot vert de forme RobotSign, `Robot(Color c)` crée le robot avec la couleur de notre choix.
   - `getColor()`, `getShape()`, `getX()`, `getY()` : Retourne respectivement la couleur, la forme, ses coordonnées en x et y.
   - `setColor(Color)`, `setShape(Shape)`, `setX(int)`, `setY(int)` : Change respectivement la couleur, la forme, ses coordonnées en x et y.

### Fonctionnement de la classe Display

La classe `Display` sert à générer un affichage visuel en console d’un plateau de jeu, avec une représentation graphique ASCII des murs, des robots et des cibles (les targets). Elle utilise des codes ANSI pour afficher les couleurs et des caractères Unicode pour les formes.

#### Fonctionnement

1. **Attributs principaux :**
   - `board[SIZE_BOARD][SIZE_BOARD]` : Tableau 2D de cases représentant la grille de jeu. Chaque case peut contenir des murs, un robot, ou une cible. SIZE_BOARD = int(16)
   - `dispBoard[BOARD_DISP_SIZE][BOARD_DISP_SIZE]` : Affichage visuel du plateau.
   - `DispCaseDir_t` : enum privé pour gérer la direction des cases.

2. **Méthodes privées :**
   - `put_walls` : Parcourt chaque Case pour afficher les murs selon les directions -> Nord, Sud, Est, Ouest.
   - `put_robots` : Vérifie si un robot est présent dans la case. Si oui, récupère sa couleur et sa forme, prépare une chaîne à afficher.
   - `put_targets` : Affichage des cibles.

3. **Méthodes publiques :**
   - `update(Case board[SIZE_BOARD][SIZE_BOARD])` : Met à jour le plateau. Dans l'ordre :
        1 - Génère ligne par ligne les caractères ASCII à afficher.
        2 - Appelle trois fonctions privées pour : afficher les murs, afficher les robots, afficher les cibles.
   - `print` : Place aléatoirement 4 robots sur la grille, ainsi qu'une cible dans un angle de deux murs.
   - Constructeur et destructeur `Display()`: initialise l’affichage (mise en forme console avec ANSI) et réinitialise les couleurs et efface l’écran.

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
fonction ø <- update(Case board[SIZE_BOARD][SIZE_BOARD])
    paramètre paramètre lien Board B
    résultat ø
algorithme
    Copie les cases du plateau board dans this->board
    Pour chaque quart de la grille Faire
        Générer x aléatoire dans les limites du quart
        Générer y aléatoire dans les limites du quart
        si i et j sont nuls alors
            Affiche un coin gauche/haut
        fin si
        si i = est nul et j = (SIZE_BOARD * 2) alors
            Affiche un coin gauche/haut        
        fin si
        si i = (SIZE_BOARD * 2) et j est nul alors
            Affiche un coin gauche/bas
        fin si
        si i = (SIZE_BOARD * 2) et j = (SIZE_BOARD * 2) alors
            Affiche un coin droite/bas
        fin si

        si i est nul et j pair alors
            Affiche mur horizontal
        si i = (SIZE_BOARD * 2) et j pair alors
            Affiche mur horizontal
        si i est pair et j = (SIZE_BOARD * 2) alors
            Affiche mur vertical
        si i et j sont pairs alors
            Affiche mur vertical
        
        si i est pair
            Affiche ligne horizontale
        Si j est pair
            Affiche ligne verticale
        Sinon mettre un espace

        si l'élément affiché n'est pas un espace
            Applique couleur gris aux lignes de la grille
            Applique couleur noir clair au premier-plan
            Enregistre dans la grille d'affichage dispBoard à la bonne position
        fin si
    fin pour
    
    Place les murs sur le plateau
    Place les robots sur le plateau
    Positionne les cibles surle plateau
    Positionne le centre du plateau
fin fonction


```algo
fonction ø <- print
    paramètre ø
    résultat ø
algorithme
    réinitialiser de l'affichage
    affichage du temps de jeu écoulé
    pour chaque case du plateau faire
        affichage du plateau dans le terminal
    fin pour
    pour chaque case du plateau faire
        affichage des lignes permanentes (textes en bas du plateau)
    fin pour
fin fonction

```algo
fonction ø <- printTime
    paramètre ø
    résultat ø
algorithme
    enregistrer la position du curseur
    réinitialiser la couleur d'arrière-plan par défaut
fin fonction

```algo
fonction ø <- addLine
    paramètre line
    résultat affiche la line
algorithme
    initailisation : i = 0
    tant que permaLine est vide
        i ++
        si i > nombre de permaLine alors
            i = -1
        fin si
    fin tant que
fin fonction

```algo
fonction ø <- updateLine
    paramètre indice de line, line
    résultat affiche la line
algorithme
    si l'indice de la ligne >= nombre max de permaLine alors
        on retourne rien
    sinon
        on modifie permaline à l'indice donné
    fin si
fin fonction

```algo
fonction ø <- clearLine
    paramètre indice de line
    résultat ø
algorithme
    si l'indice de la ligne >= nombre max de permaLine alors
        on retourne rien
    fin si
    on met "" à l'indice donné dans le conteneur permaline
fin fonction

```algo
fonction ø <- clearLine
    paramètre indice de line
    résultat ø
algorithme
    si l'indice de la ligne >= nombre max de permaLine alors
        on retourne rien
    fin si
    on met "" à l'indice donné dans le conteneur permaline
fin fonction

```algo
fonction ø <- put_time
    paramètre ø
    résultat ø
algorithme
    récupére une référence à l'instance unique du timer
    t contient le temps restant en millisecondes
    conversion de t en seconde

    timeStr est un temps formaté

    assigne strLength à la taille de timeStr

    pour i<nombre d'espaces à afficher avant timeStr pour centrer timeStr
        affiche timeStr
    fin pour
fin fonction

```algo
fonction ø <- put_walls
    paramètre curCase, x, y
    résultat ø
algorithme
    pour chaque case du plateau
        curCase predn la valeur de la case actuelle
        x et y prennent les coordonnées du plateau

        si curCase est faux
            continuer
        si curcase.getNorth est vrai
            afficher un mur horizontal au coordonnées : dispBoard[x - 1][y]
        si curcase.getSouth 
            afficher un mur horizontal au coordonnées : dispBoard[x + 1][y]
        si curCase.getEast est vrai
            afficher un mur horizontal au coordonnées : dispBoard[x][y + 1]
        si curCase.getWest est vrai
            afficher un mur horizontal au coordonnées : dispBoard[x][y - 1]
        fin si
    fin pour

    initialisation des valeurs booléenne wbot, wtop, wrgt, wlft
    pour chaque case
        to_put prend un espace vide
        si la case = coin supérieur gauche du plateau alors
            wrgt : recherche d'un mur horizontal à droite de ce coin
            wbot : recherche d'un mur vertical en dessous
            si wrgt && wbot alors
                affiche coin complet
            si wbot alors
                Un coin avec seulement un mur vertical
            si wrgt alors
                Un coin avec seulement un mur horizontal
            fin si
        fin si
    fin pour
fin fonction