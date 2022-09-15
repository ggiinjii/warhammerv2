# ReadMe

**Contact:**
AUBERT ROMAIN -
aubertromainpro@gmail.com

Bonjour,
Voici le projet WarHammer que j'ai développé dans le cadre de ma candidature pour l'entreprise Eugen System.

Pour rappel, voici la problématique :

Créer un projet Console sous Visual Studio 2017 ou 2019 qui fera tourner un petit jeu de simulation simple de bataille entre deux unités (chevalier contre orc).
Vous êtes libre d'utiliser des librairies externes de votre choix si vous estimez en avoir besoin, à condition que le projet que vous allez fournir à la fin puisse
se lancer sans avoir besoin d'installer un autre logiciel.
Vous devez nous rendre un fichier zip contenant un repo git local. Celui-ci devra contenir sur la branche master la solution Visual que nous aurons juste
à compiler et lancer pour tester votre programme.
Voici une description des règles à respecter. Si certaines règles ne vous semblent pas claires ou qu'il manque de précisions, vous êtes libre de faire des choix
à condition de nous les préciser dans votre mail de retour.

**Caractéristiques du chevalier**
- Il dispose de 20 points de vie et d'un bouclier de 50 points.
- Il dispose d'une épée lui permettant de faire 5 points de dégâts par tour.
- Il dispose d'une capacité "charge" lui permettant de faire le double de dégâts ce tour-ci. Cette capacité ne peut être utilisée que tous les 3 tours de jeu.
Elle a 60% de chance de réussir. Si elle ne réussit pas, il faudra attendre les 3 tours mentionnés ci-dessus pour la tenter de nouveau.
- Les dégâts pris par le chevalier sont d'abord infligés au bouclier et lorsque le bouclier n'a plus de points, l'unité perd des points de vie.

**Caractéristiques de l'orc**
- L'orc dispose de 60 points de vie mais n'a pas de bouclier.
- Il dispose d'une hache lui permettant de faire 8 points de dégâts par tour.
- Il dispose d'une capacité "stun" lui permettant d'étourdir l'ennemi pendant un tour. Un ennemi étourdi ne pourra pas faire de dégât ce tour-ci.
Cette capacité ne peut être utilisée que tous les 5 tours de jeu. Elle a 20% de chance de réussir.
Si elle ne réussit pas, il faudra attendre les 5 tours mentionnés ci-dessus pour la tenter de nouveau.

**Déroulement de la partie**
- Un tour de jeu est constitué de 2 éléments successifs : lancement de capacités spéciales, puis combat entre les unités.
- Il y a autant de tour de jeu que nécessaire pour que l'un des côtés gagne la partie.
- Un côté gagne la partie quand l'unité adverse a été tuée.
- Pour le combat entre 2 unités, chaque unité inflige directement les dégâts à l'unité ennemie (en prenant en compte les éventuels effets des capacités).


**Contraintes supplémentaires**
- Afin de vérifier que votre programme fonctionne normalement, il serait appréciable de pouvoir suivre l'évolution de la partie en affichant notamment les informations
de chaque unité à chaque tour de jeu.
- Il faut que le programme soit correctement architecturé pour qu'il soit facile d'ajouter de nouvelles classes et/ou de nouvelles caractéristiques.

**Bonus**
- Pour rendre le jeu plus "dynamique", il pourrait être sympa de pouvoir faire des choix avant le lancement de la partie/pendant la partie. Vous êtes libre de faire une/des
propositions et de les implémenter.

------------------------------------------------------------------------------------------------------------------------------------------

## Le projet
J'ai créer un projet console en Visual 2019 permettant à 2 camps identifié comme l'alliance et la Horde de faire s'affronter un champion les représentants dans une arene.
Crée en C++ et intégrant des librairies externes, il est compilable et exécutable en Debug ou Release.
Afin que ce dernier soit robuste, j'ai ajouter des tests Unitaires me permettant un développement plus stable. Toutes les fonctions nouvellement ajouté sont testé m'assurant aucune régression lors de mes développements.
Un systeme de monitoring a également été pensé via SonarScanner mais nécéssite une licence payante, rendant impossible sa mise en place dans un contexte personnel.

**CI**

	Job:  	Build&Test - teste la compilation Release et lance les Test Unitaires, Echoue si un test Echoue

**Dependance**

- SergiusTheBest/plog --> Logger (https://github.com/SergiusTheBest/plog)
- nlohmann/json --> Parser Json(https://github.com/nlohmann/json)
- SpartanJ /SOIL2--> Chargement Imagejpg/Png/... dans OpenGL (https://github.com/SpartanJ/SOIL2)
- ocornut /imgui--> Ui basé sur OpenGl et glfw  (https://github.com/ocornut/imgui)
- OpenGL 2--> lib 3D
- glfw /glfw --> Librairie OpenGl (https://github.com/glfw/glfw )

**Déroulé du combat**

Pour suivre le déroulé du combat il existe 3 options:
- Un logger a été ajouté ( Librairie PLOG ) afin de pouvoir récupérer dans le dossier Logs le déroulé entier d'un combat avec différent niveau de verbosité ( Information, Debug, Erreur).
Ce fichier peut autant servir au débug qu'a du monitoring.

- Une UI rétro permet également de voir le déroulé du combat sur la console. Chaque tour est joué d'un coup et les PV des combattant sont mit a jour sous leur encadré

- Une UI moderne a également été crée afin de pouvoir profité de la puissance d'OpenGl et de GLWF pour un meilleur rendu. Ainsi en plus de panel de texte, des boutons et des images des personnages choisi s'affiche a l'écran.
Il serait possible avec plus de temps d'ajouter la partie Temps réel a ce combat en modélisant un décors et les personnage, en les animant et en intégrant tout ceci a l'application via OpenGl.

**Les Combattants**

Les combattants ont chacune leur classe fille attitré qui est dérivé de la classe mere Character.
Cela permet l'ajout facilement de nouvelle classe de combattant en créant des classes Heritant de la classe Character.
Les character possedant une capacité spéciale, il est donc possible de créer des personnages avec des capacités spéciale différente en ajoutant qu'une nouvelle classe.
Pour le moment, chaque classe possede une capacité spéciale ( Chevalier --> Charge & Orc --> Stun) mais il serai possible de dissocié la capacité spéciale de la classe.

Pour ce faire il faudrait procéder comme les classes Weapon et Armor. Un pointeur dans la classe Character sur la classe mere des Capacité spéciale et une instanciation lors de la lecture Json de la capacité en question.
Cela necessiterai un ajout a la lecture du Json, une modification de ce dernier et un changement sur les classes fille de la classe Character pour que la fonction LaunchSpecialCapacity ne soit plus hardcodé mais appel les fonctions sur les classes filles des Capacité spéciales.


**Les Armes**

L'architecture logicielle des armes est la même que celle des Personnages Combattant.
Deux classe mere Armor et Weapon sont les classe hérité de toutes les armes que l'ont voudra créer.
Cela permet également une grande souplesse dans l'ajout d'arme différentes.

**Préparation du combat**

Avant de lancer le combat j'ai voulu laisser le joueur faire le choix des combattant.
Chacun des camps ( Alliance et horde ) a plusieurs champions qu'il peut choisir pour le combat.
Ces champions sont définie dans un Fichier Json dans la partie Ressource.

Ce fichier permet de créer plusieurs personnages et leur équipement avec des statistiques différente de maniere efficiente.
Cela permet aussi une flexibilité au niveau des affrontement afin que les orcs n'affronte pas toujours les chevaliers car tous comme les bon orc existes, les mauvais chevalier existe aussi.

La seule limite de ce fichier est que les informations rentrée doivent etre en concordance avec ce que le code permet.
Impossible de créer un personne d'une classe non Existante dans le code, si c'est le cas, le code créra un personnage par défaut ( un chevalier coté Alliance ) avec les stats et équipement que vous avez pu remplir.


**Le Combat**

Le combat fonctionne de la maniere suivante:
- lancement de capacités spéciales si possible par les personnages
- combat entre les unités si aucun des personnages n'est mort
- évolution des conditions liée au personnage (Evolution ou suppréssion des états temporaire )

Lors du combat l'alliance a l'avantage et lancera toujours ses attaques en premier.
Avec plus de temps, il serai possible d'imaginer une stats de vitesse propre a chaque personnage auquel s'ajouterai un lancer de dés a chaque tour permettant de savoir quel personnage est le plus rapide a attaquer a chaque tour ou chaque attaque.

Si un personnage est mort durant l'une des phase, le combat s'arrete et le nom du vainqueur est révélé.


## Evolution possible
**Projet**

Monitoring avec SonarScanner
Evolution vers des version plus récente d'OpenGl
Ajout d'un job de Package a la Ci

**Jeux**

Ajout de Model 3D pour le décors et les personnages.
Animation du combat en temps réel
Ajout de son ambiant
Ajout de combat multiple ( Duo, Trio Armée Vs Armée)
Décorélation des personnages et de l'équipement afin que l'utilisateur puisse créer un personnage de bout en bout et ne plus jouer d'archetypes.
Ajout de différentes condition ( Burn, Frozen, etc)
