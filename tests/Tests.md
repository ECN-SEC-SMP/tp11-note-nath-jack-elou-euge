# Tests

## Game

### Protocoles

#### Initialisation :

- Choix du nombre de joueurs  
`Choisissez un nombre de joueurs inférieur ou égale à 16.`  
> Entrer numéro n  
> => L'interface doit demander n noms  

- Choix nom des joueurs  
`Joueur #n choisissez votre pseudonyme`  
> Entrer une chaine de caractère  
> => l'interface doit redemander si le même nom a déjà été rentré  

- Déplacement d'un robot  
> Un robot doit se déplacer dans la direction correspondante lors d'un appuis sur une touche fléché.  
> Un robot s'arrête quand il rencontre un mur ou un autre robot.  

- Gagner  
> Une manche est concidéré gagné quand le robot de la couleur de la Target cible arrive dessus.  
> Un robot ne peut pas gagner en 1 mouvement.

- Perdre
> Une manche est concidéré perdue quand le joueur utilise plus de coup que ce qu'il avait annoncé.  