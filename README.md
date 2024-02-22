# C-Pascal-Compiler
Ce dépôt contient le code source d'un compilateur simple de pascal en C. Le compilateur est capable de générer du code intermédiaire (p-code) à partir d'un programme pascal. Le p-code est ensuite exécuté par une machine virtuelle.

## Contributeurs
* Said NAJIM
* Ilyas ABDELLAOUI
* Ahmed LAZREK
* Yahya NAHLI

## Fonctionnalités

* Analyse lexicale
* Analyse syntaxique
* Analyse sémantique
* Génération de P-code
* Interprétation du P-code

## Structure du projet

* `compilateur.c`: contient le code source du compilateur (analyseur lexical, syntaxique, sémantique, et generateur du p-code).
* `tokens.h`: Définition des tokens du langage
* `errors.h`: Définition des erreurs du langage
* `run.c`: Code pour exécuter le compilateur

## Exemple d'exécution

1. Ecriture d'un programme pascal dans le dossier `\tests` (par exemple `code1.p`).
2. Compilation du compilateur avec la commande `gcc run.c -o run`.
3. Exécution du compilateur avec la commande `run code1.p`.


## Définitions des symboles non-terminaux
- `PROGRAM` ::= program ID ; BLOCK .
- `BLOCK` ::= CONSTS VARS INSTS
- `CONSTS` ::= const ID = NUM ; { ID = NUM ; } | ε (epsilon)
- `VARS` ::= var ID { , ID } ; | ε
- `INSTS` ::= begin INST { ; INST } end
- `INST` ::= INSTS | AFFEC | SI | TANTQUE | ECRIRE | LIRE | ε
- `AFFEC` ::= ID := EXPR
- `SI` ::= if COND then INST
- `TANTQUE` ::= while COND do INST
- `ECRIRE` ::= write ( EXPR { , EXPR } )
- `LIRE` ::= read ( ID { , ID } )
- `COND` ::= EXPR RELOP EXPR
- `RELOP` ::= = | <> | < | > | <= | >=
- `EXPR` ::= TERM { ADDOP TERM }
- `ADDOP` ::= + | -
- `TERM` ::= FACT { MULOP FACT }
- `MULOP` ::= * | /
- `FACT` ::= ID | NUM | ( EXPR )
- `ID` ::= lettre { lettre | chiffre }
- `NUM` ::= chiffre { chiffre }
- `Chiffre` ::= 0 |..| 9
- `Lettre` ::= a | b |..| z | A |..| Z

Les symboles non-terminaux sont en majuscules et représentent des concepts syntaxiques, tandis que les terminaux sont en minuscules et représentent des éléments de base tels que des mots-clés, des opérateurs, des identifiants et des nombres. Le symbole ε (epsilon) représente une production vide.

## **Règles sémantiques**

- **Règle 1**: Toutes les déclarations dans `CONSTS` et `VARS`
- **Règle 2**: PAS DE DOUBLE DÉCLARATIONS
- **Règle 3**: Après `BEGIN`, tous les symboles doivent être déjà déclarés
- **Règle 4**: Une constante ne peut changer de valeur dans le programme
- **Règle 5**: L'ID du programme ne peut être utilisé dans le programme

## Jeu d'instructions

### Instructions arithmétiques

- `ADD` : Additionne le sous-sommet de la pile avec le sommet, et laisse le résultat au sommet de la pile.
- `SUB` : Soustrait le sommet de la pile du sous-sommet de la pile, et laisse le résultat au sommet de la pile.
- `MUL` : Multiplie le sous-sommet de la pile par le sommet, et laisse le résultat au sommet de la pile.
- `DIV` : Divise le sous-sommet de la pile par le sommet, et laisse le résultat au sommet de la pile.

### Instructions de comparaison

- `EQL` : Laisse 1 au sommet de la pile si le sous-sommet de la pile est égal au sommet, sinon laisse 0.
- `NEQ` : Laisse 1 au sommet de la pile si le sous-sommet de la pile n'est pas égal au sommet, sinon laisse 0.
- `GTR` : Laisse 1 au sommet de la pile si le sous-sommet de la pile est plus grand que le sommet, sinon laisse 0.
- `LSS` : Laisse 1 au sommet de la pile si le sous-sommet de la pile est plus petit que le sommet, sinon laisse 0.
- `GEQ` : Laisse 1 au sommet de la pile si le sous-sommet de la pile est supérieur ou égal au sommet, sinon laisse 0.
- `LEQ` : Laisse 1 au sommet de la pile si le sous-sommet de la pile est inférieur ou égal au sommet, sinon laisse 0.

### Instructions de manipulation de la pile

- `PRN` : Imprime la valeur au sommet de la pile et la dépile.
- `INN` : Lit un entier et le stocke à l'adresse trouvée au sommet de la pile, puis dépile.
- `INT c` : Incrémente de la constante `c` le pointeur de pile (la constante `c` peut être négative).
- `LDI v` : Empile la valeur `v`.
- `LDA a` : Empile l'adresse `a`.
- `LDV` : Remplace le sommet de la pile par la valeur trouvée à l'adresse indiquée par le sommet (déréférence).
- `STO` : Stocke la valeur au sommet de la pile à l'adresse indiquée par le sous-sommet de la pile, puis dépile deux fois.

### Instructions de branchement

- `BRN i` : Effectue un branchement inconditionnel à l'instruction `i`.
- `BZE i` : Effectue un branchement à l'instruction `i` si le sommet de la pile est égal à 0, puis dépile.

### Autre instruction

- `HLT` : Arrête l'exécution du programme.