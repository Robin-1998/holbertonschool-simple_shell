# 🖨️ Simple Shell 🖨️

## 📄 Description 📄

Ce projet est une implémentation basique d’un shell Unix en langage C.
Il permet d'exécuter des commandes en ligne de commande, comme ls, pwd, echo, etc., en utilisant les appels système de la bibliothèque standard POSIX.
Le shell fonctionne en mode interactif (avec un prompt) et non-interactif (lecture depuis un fichier ou une redirection).

---
## 📊 Flowchart 📊
```mermaid
flowchart TD
    A[Start] --> B(Affiche le prompt $)
    B --> C(lit la ligne de l'utilisateur)
    C --> D(analyse la ligne)
    D --> E{commande interne commande externe }
    E --> | Interne | F(executer la commande)
    E --> | Externe | G(Fork - execve)
    G --> H(wait processus fils)
    H --> I(free avant de reprendre la boucle)
    I --> B
    F --> I

---

## 💻 Commande de Compilation 💻

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## 📋 Requirements 📋

Langage de programmation : C

Compilateur : GCC -Wall -Werror -Wextra -pedantic -std=gnu89

Conformité aux normes : C89

code should use the Betty style

Respect des contraintes de performance et d'optimisation mémoire

Un seul repository pour le projet



## 📜 Exemple d'utilisation du simple shell 📜

Voici un exemple d'utilisation du simple shell :

Exemple 1 : Affichage de /bin/ls
```bash
$ /bin/ls
```

Sortie en STDOUT :
```bash

```

## 📚 Man Page 📚

Vous pouvez consulter la man page de la fonction simple shell en exécutant la commande suivante :

```man ./man_1_simple_shell```

## 🧠 Valgrind 🧠

Test mémoire tampon.
Commande :
```bash
valgrind ./hsh
```

Résultat :

```bash
==128186== Memcheck, a memory error detector
==128186== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==128186== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==128186== Command: ./hsh
==128186==
$
==128186==
==128186== HEAP SUMMARY:
==128186==     in use at exit: 0 bytes in 0 blocks
==128186==   total heap usage: 3 allocs, 3 frees, 2,168 bytes allocated
==128186==
==128186== All heap blocks were freed -- no leaks are possible
==128186==
==128186== For lists of detected and suppressed errors, rerun with: -s
==128186== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

Aucune fuite mémoire détectée.

## 🎯 Auteurs 🎯

- 👨‍💻 : **Lefoulon Thérèse-Marie** – [GitHub](https://github.com/Timi-Holberton)

- 👨‍💻 : **David Robin** – [GitHub](https://github.com/StrawberSam)
