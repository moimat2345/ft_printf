<div align="center">
  <img src="https://raw.githubusercontent.com/ayogun/42-project-badges/main/covers/cover-ft_printf.png" alt="ft_printf" />
</div>

# ft_printf - Ma Recréation de printf()

Le projet `ft_printf` consiste à recréer la fonction standard `printf()` en C. Ce projet est une excellente introduction aux **fonctions variadiques** et à la gestion des arguments variables.

## Statut
<div align="center">

![42 Bangkok](https://img.shields.io/badge/42-Bangkok-000000?style=for-the-badge&logo=42&logoColor=white)
![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Norminette](https://img.shields.io/badge/Norminette-passing-success?style=for-the-badge)

<br>

### 🌍 Language / Langue

[![English](https://img.shields.io/badge/🇬🇧_Read_in_English-red?style=for-the-badge&logoColor=white)](README.md)

</div>

---

## Vue d'ensemble

L'objectif est de créer sa propre version de `printf()`, capable de gérer différents types de données et conversions. Cet exercice améliore la compréhension des fonctions variadiques et permet de pratiquer l'écriture de code extensible et robuste.

## Ressources utiles

- [Notion's Oceano - ft_printf](https://suspectedoceano.notion.site/printf-06cba643d653410bb03417532ca71c25)
- [Ft_printf Tester Francinette](https://github.com/xicodomingues/francinette)

---

## 📋 Partie Obligatoire

<table>
  <tr>
    <th>Nom du programme</th>
    <td>libftprintf.a</td>
  </tr>
  <tr>
    <th>Fichiers à rendre</th>
    <td>Makefile, *.h, *.c</td>
  </tr>
  <tr>
    <th>Makefile</th>
    <td>Oui</td>
  </tr>
  <tr>
    <th>Fonctions externes</th>
    <td>malloc, free, write, va_start, va_arg, va_copy, va_end</td>
  </tr>
  <tr>
    <th>Libft autorisée</th>
    <td>Oui</td>
  </tr>
  <tr>
    <th>Description</th>
    <td>Implémenter sa propre version de la fonction printf() de la libc.</td>
  </tr>
</table>

### Règles importantes
- Les variables globales sont interdites.
- Les sous-fonctions doivent être définies comme `static`.
- Tous les fichiers .c doivent compiler avec les flags `-Wall -Wextra -Werror`.
- Utiliser `ar` pour créer la bibliothèque ; `libtool` n'est pas autorisé.

---

## 📂 Structure du Projet

```
ft_printf/
├── 📄 Makefile              # Compilation → libftprintf.a
├── 📄 ft_printf.h           # Header (prototypes + includes)
├── 📄 ft_printf.c           # Fonction principale + parsing
│
└── 📁 utils/                # Fonctions utilitaires (7 fichiers)
    ├── ft_putchar.c         # Affiche 1 caractère
    ├── ft_putstr.c          # Affiche une chaîne
    ├── ft_putnbr.c          # Affiche int signé
    ├── ft_putunbr.c         # Affiche unsigned
    ├── ft_putunsigned.c     # Affiche unsigned (alias)
    ├── ft_puthex.c          # Affiche hexadécimal
    └── ft_putpointer.c      # Affiche pointeur
```

---

## 🎯 Conversions Implémentées

La fonction `ft_printf` supporte les conversions suivantes :

<details open>
<summary><b>Cliquez pour voir les conversions</b></summary>

| Format | Type | Description | Exemple |
|:------:|:-----|:------------|:--------|
| **%c** | `char` | Affiche un caractère | `ft_printf("%c", 'A')` → `A` |
| **%s** | `char*` | Affiche une chaîne | `ft_printf("%s", "Hello")` → `Hello` |
| **%p** | `void*` | Affiche un pointeur (0x...) | `ft_printf("%p", ptr)` → `0x7ffe...` |
| **%d** | `int` | Affiche un nombre décimal signé | `ft_printf("%d", -42)` → `-42` |
| **%i** | `int` | Affiche un entier (= %d) | `ft_printf("%i", 42)` → `42` |
| **%u** | `unsigned int` | Affiche un nombre non signé | `ft_printf("%u", 42)` → `42` |
| **%x** | `unsigned int` | Hexadécimal minuscule | `ft_printf("%x", 255)` → `ff` |
| **%X** | `unsigned int` | Hexadécimal MAJUSCULE | `ft_printf("%X", 255)` → `FF` |
| **%%** | N/A | Affiche le caractère % | `ft_printf("%%")` → `%` |

</details>

---

## 🛠️ Compilation et Utilisation

### Compiler la bibliothèque

```bash
# Compiler
make

# Nettoyer les fichiers objets
make clean

# Tout nettoyer
make fclean

# Recompiler complètement
make re
```

### Utiliser dans votre code

```c
#include "ft_printf.h"

int main(void)
{
    int age = 25;
    char *name = "Alice";
    void *ptr = &age;

    // Exemples d'utilisation
    ft_printf("Nom: %s\n", name);           // Nom: Alice
    ft_printf("Age: %d ans\n", age);        // Age: 25 ans
    ft_printf("Hex: %x / %X\n", 255, 255);  // Hex: ff / FF
    ft_printf("Pointeur: %p\n", ptr);       // Pointeur: 0x7ffe...
    ft_printf("Unsigned: %u\n", 42);        // Unsigned: 42
    ft_printf("Pourcentage: 50%%\n");       // Pourcentage: 50%

    // Retourne le nombre de caractères imprimés
    int count = ft_printf("Test");          // count = 4

    return (0);
}
```

### Compiler avec ft_printf

```bash
gcc main.c -L. -lftprintf -o program
./program
```

---

## 💡 Points Clés de l'Implémentation

<details>
<summary><b>🔹 Approche Récursive</b></summary>

Toutes les conversions numériques utilisent la récursion pour un code élégant et compact :

```c
int ft_putnbr(int n)
{
    long nb = n;
    int printed = 0;

    if (nb < 0)
    {
        printed += ft_putchar('-');
        nb = -nb;
    }
    if (nb >= 10)
        printed += ft_putnbr(nb / 10);  // Récursion
    printed += ft_putchar((nb % 10) + '0');
    return (printed);
}
```

</details>

<details>
<summary><b>🔹 Gestion du NULL</b></summary>

Les chaînes NULL et pointeurs NULL sont gérés correctement :

```c
ft_printf("%s", NULL)    // → (null)
ft_printf("%p", NULL)    // → (nil)
```

</details>

<details>
<summary><b>🔹 Valeur de Retour</b></summary>

Comme `printf()`, la fonction retourne le nombre de caractères imprimés :

```c
int count = ft_printf("Hello World");  // count = 11
```

</details>

---

## ⚠️ Limitations

Cette implémentation **NE supporte PAS** les bonus :

- ❌ Flags (`-`, `0`, `+`, ` `, `#`)
- ❌ Largeur de champ (`%10d`, `%-5s`)
- ❌ Précision (`%.2f`, `%.5s`)
- ❌ Modificateurs de taille (`%ld`, `%lld`)
- ❌ Formats avancés (`%f`, `%e`, `%g`)

C'est une version **basique** avec les 9 conversions essentielles.

---

## 📊 Statistiques

<div align="center">

| Métrique | Valeur |
|:--------:|:------:|
| **Fichiers** | 8 .c |
| **Lignes** | ~273 |
| **Conversions** | 9 |
| **Bonus** | Non |

</div>

---

## 🚨 Avertissement

**🇫🇷 Ce projet a un but éducatif et vous ne devez en aucun cas faire du copier-coller.**
**Tricher c'est mal. Ne trichez pas.**

**🇬🇧 This project has an educational purpose and you should under no circumstances copy and paste.**
**Cheat is bad. Don't cheat.**

---

<div align="center">

**Made with ❤️ for 42 Bangkok**

[![Back to top](https://img.shields.io/badge/⬆-Retour_en_haut-blue?style=for-the-badge)](#ft_printf---ma-recréation-de-printf)

</div>
