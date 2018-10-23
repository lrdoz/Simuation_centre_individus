# Rendu TP Simulation centre individue

## Bilan

### Résumé

Dans ce repertoire vous trouverez nos trois implémentation des TP1, 2 et 3.
Chaque implémentation de core se trouve dans un repertoire spécifique du tp.
< MOCHE
Pour permettre une parfaite hiérarchie objet, nous avons du délaisser l'aspect performance de notre implémentation.
En effet, de nombreux calcul ont été laissé au agent, permettant leur indépendance, cependant si l'environement sans été
occupé, le nombre d'accept à la grille aurait été fortement réduit

Exemple: Le TP1 il était possible de faire tourner 120 000 agent sur la première version, suite au réfacto ont peut en faire tourner que 80 000.

Hormis ce léger problème l'enssemble des tps sont fonctionnels et implémentes toutes les fonctionnalités.>

### Implémentation

###

## TP1 - Particule

### TP1 - Objectif

L'objectif du tp est de similué un environnement contenant des agents se déplaçant et interagissant avec d'autres agents.
Les agents sont des billes, possédant un vecteur de déplacement, et se déplaçant dans leur environnement.
L'environnement peut être torique ou non torique, càd que les boules peuvent rebondir (ou non) contre les murs.
Lorsque deux agents se collisionnent, différents comportements peuvent être là aussi adoptés (voir question 3).

Le fichier Properties.json gère les différentes options pour lancer la simulation :
 * "torus": si le monde est torique ou non
 * "gridSizeX": taille de la grille en abscisse
 * "gridSizeY": taille de la grille en ordonnée
 * "boxSize": taille de la box
 * "delay":
 * "scheduling": ordonnancement pour donner la parole aux particules (1 : ordonné, 2: aléatoire juste, 3: aléatoire injuste)
 * "nbTicks": nombre de tours de parole
 * "time": vitesse des particules
 * "trace": trace des tours dans le terminal
 * "seed": seed pour le random
 * "refresh": taux de rafraichissement de la vue
 * "grid": afficher la grille ou non
 * "nbParticles": nombre de particules

### TP1 - Implémentation

![](/image/particule.png)

![](/image/particule_package.png)

#### TP1 - Execution + Configuration

1. Pour l'éxécution il simplement nécessaire de faire :
    ```make particule```

### TP1 - Question

1. Combien d'agents peut-on raisonnablement faire tourner simultanément? (fréquence d'un tour par population)

2. Tracer quelques courbes montrant l'évolution du nombre de collisions par tick, por le même nombre de billes
    mais selon les tailles d'environement.

3. Variation sur le comportement:
    * Si une bille est là où je dois aller, je ne fais rien
    * Si une bille est la où je dois aller, j'inverse ma direction
    * Si une bille est la où je dois aller, j'inverse ma direction avec l'autre

    Que se passe t-il dans ces diffénts cas? Quel est le comportement qui fournit le meilleur rendu?

### TP1 - Reponse

1. Raisonnablement : ~ 80.000 agents, avec un taux de rafraichissement de 2 images par seconde.

2. prout

3. Comportement :
    * Premier comportement : Les billes forme des tas, en effet elles immobilisent lors d'une colision.
    * Deuxième comportement : Les billes immobile le resteront et les autres ce déplasseront toujours sur le même vecteurs.
    * Troisième comportement : Les billes ont un comportement plus aléatoire et naturel.
    * Bonus :
        On a voulu tester d'autre comportement, on a donc essayé, soit d'appliquer le comportement 2 ou 3, de manière aléatoire.
        Les billes ont un comportement linéaire, mais garde un aspect aléatoire.

    Le comportement avec un meilleur rendu visuel est le quatrième comportement, car il est plus linéraire, mais garde un aspect aléatoire.
    Cependant, le comportement trois est plus naturel, les billes ont un déplacement arbitraire au siens de l'environement.

## TP2 - Shark Vs Fish

### TP2 - Objectif

L'objectif du Tp est de similué un environement proi prédateur, pour ce faire nous avons 2 agents.
Les poissons, ils pouvent se déplacer et se reproduire dans l'environement et les requins, qui
peuvent se déplacer, se reproduire et manger les poissons dans l'environement.

### TP2 - Implémentation

![](/image/wator.png)

![](/image/wator_package.png)

#### TP2 - Execution + Configuration

1. Pour l'éxécution il simplement nécessaire de faire :
    ```make wator```

### TP2 - Question

1. Est-il préférable d'initialiser les agents avec les mêmes valeurs pour les 3 différents compteurs
    ou initialiser ces compteurs aléatoirement?

2. Testez différents variantes comportementales. Quels sont les comportements qui donnent les
    meilleures dynamique?
    * Une action à chaque tick : soit manger, soit se reproduire, soit bouger
    * Se reproduire en bougeant
    * Se reproduire en mangeant
    Vous fournirez notamment la Courbe d'évolution du nombre de Fishes et de Sharks et de la courbe
    d'évolution du nombre de Fishes sur le nombre de Sharks pour chacun de ces cas.

### TP2 - Reponse

1. Il n'est pas préférable d'initialisé les même valeurs, en effet selon la taille de la grille et la disposition, les requins
    vont disparaitre, ou les poisson.
    Il est plus préférable d'adapter les valeur au environement.

2. Comportement :
    * Premier comportement : Dans ce type de comportement les poissons forment des attroupement, qui grandit et rapetit, sans jamais disparaitre
    * Deuxième comportement :
    * Troisième comportement : On constate la formation de nombreux, vague de requin poursuivant un amas de poisson jusqu'a son extermination.

## TP3 - Pack Man

### TP3 - Objectif

L'objectif du tp est de mettre un system temps réel, avec une intéraction humaine sur le l'environement.
Pour se faire, nous créer un agent pouvant être maitrisé par un individue, et des agents trackant l'humain.
L'individue, peut ce déplacer dans l'environement, manger certain agent, et mourir.

### TP3 - Implémentation

![](/image/hunter.png)

![](/image/hunter_package.png)

#### TP3 - Execution + Configuration

1. Pour l'éxécution il simplement nécessaire de faire :
    ```make hunter```

## TP4 NetLog
