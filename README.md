<div align="center">

# 🖨️ ft_printf - Mon Printf Personnalisé

![42 Bangkok](https://img.shields.io/badge/42-Bangkok-000000?style=for-the-badge&logo=42&logoColor=white)
![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Norminette](https://img.shields.io/badge/Norminette-passing-success?style=for-the-badge)
![Lines](https://img.shields.io/badge/Lines-273-blue?style=for-the-badge)

[![English](https://img.shields.io/badge/🇬🇧_English-Click_here-red?style=for-the-badge)](README.en.md)

</div>

---

## 📝 Vue d'ensemble

<table>
<tr>
<td>

**ft_printf** est une recréation de la fonction `printf()` de la libc. Ce projet introduit les **fonctions variadiques** (`va_list`, `va_start`, `va_arg`, `va_end`) en C.

✨ Implémentation **simple et efficace** en **273 lignes**

**Conversions supportées :** 9 formats de base
**Approche :** Récursive pour les conversions numériques
**Compilation :** `-Wall -Wextra -Werror`

</td>
<td width="300">

```
📊 Statistiques

Fichiers:     8 .c
Lignes:       273
Conversions:  9
Bonus:        Non
Archive:      libftprintf.a
```

</td>
</tr>
</table>

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

## 🎯 Conversions Supportées

<div align="center">

| Format | Type | Description | Exemple |
|:------:|------|-------------|---------|
| ![](https://img.shields.io/badge/-%25c-blue?style=flat-square) | `char` | Caractère unique | `ft_printf("%c", 'A')` → `A` |
| ![](https://img.shields.io/badge/-%25s-blue?style=flat-square) | `char*` | Chaîne de caractères | `ft_printf("%s", "Hello")` → `Hello` |
| ![](https://img.shields.io/badge/-%25d-green?style=flat-square) | `int` | Nombre décimal signé | `ft_printf("%d", -42)` → `-42` |
| ![](https://img.shields.io/badge/-%25i-green?style=flat-square) | `int` | Nombre entier (= %d) | `ft_printf("%i", 42)` → `42` |
| ![](https://img.shields.io/badge/-%25u-green?style=flat-square) | `unsigned int` | Nombre non signé | `ft_printf("%u", 42)` → `42` |
| ![](https://img.shields.io/badge/-%25x-orange?style=flat-square) | `unsigned int` | Hexadécimal minuscule | `ft_printf("%x", 255)` → `ff` |
| ![](https://img.shields.io/badge/-%25X-orange?style=flat-square) | `unsigned int` | Hexadécimal MAJUSCULE | `ft_printf("%X", 255)` → `FF` |
| ![](https://img.shields.io/badge/-%25p-red?style=flat-square) | `void*` | Pointeur (0x...) | `ft_printf("%p", ptr)` → `0x7ffe...` |
| ![](https://img.shields.io/badge/-%25%25-purple?style=flat-square) | N/A | Caractère % littéral | `ft_printf("%%")` → `%` |

</div>

---

## ⚙️ Fonctionnement

### Architecture du Code

```c
int ft_printf(const char *str, ...)
{
    va_list args;
    int printed = 0;

    va_start(args, str);
    while (*str)
    {
        if (*str == '%')
            printed += ft_format(str, args);  // Dispatche
        else
            printed += ft_putchar(*str);      // Affiche normal
        str++;
    }
    va_end(args);
    return (printed);  // Nombre de caractères imprimés
}
```

### Dispatching des Formats

```c
int ft_format(const char *str, va_list args)
{
    if (str[1] == 'c')
        return (ft_putchar(va_arg(args, int)));
    else if (str[1] == 's')
        return (ft_putstr(va_arg(args, char *)));
    else if (str[1] == 'd' || str[1] == 'i')
        return (ft_putnbr(va_arg(args, int)));
    else if (str[1] == 'u')
        return (ft_putunbr(va_arg(args, unsigned int)));
    else if (str[1] == 'x')
        return (ft_puthex(va_arg(args, unsigned int), 0));
    else if (str[1] == 'X')
        return (ft_puthex(va_arg(args, unsigned int), 1));
    else if (str[1] == 'p')
        return (ft_putpointer(va_arg(args, void *)));
    else if (str[1] == '%')
        return (ft_putchar('%'));
    return (0);
}
```

---

## 💡 Particularités d'Implémentation

<table>
<tr>
<td width="50%">

### 🔹 Approche Récursive

Toutes les conversions numériques utilisent la **récursion** :

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
        printed += ft_putnbr(nb / 10); // Récursion
    printed += ft_putchar((nb % 10) + '0');
    return (printed);
}
```

**Avantages :**
- Code élégant et compact
- Pas besoin de buffer
- Pas de calcul de longueur

</td>
<td width="50%">

### 🔹 Gestion du NULL

**Chaînes NULL (`%s`) :**
```c
int ft_putstr(char *s)
{
    if (!s)
        return (ft_putstr("(null)"));
    // ...
}
```

**Pointeurs NULL (`%p`) :**
```c
int ft_putpointer(void *ptr)
{
    if (!ptr)
        return (ft_putstr("(nil)"));
    // Affiche 0x...
}
```

**Résultat :**
- `ft_printf("%s", NULL)` → `(null)`
- `ft_printf("%p", NULL)` → `(nil)`

</td>
</tr>

<tr>
<td>

### 🔹 Hexadécimal

**Deux variantes :**

```c
int ft_puthex(unsigned long long num, int uppercase)
{
    char *base;

    if (uppercase)
        base = "0123456789ABCDEF";  // %X
    else
        base = "0123456789abcdef";  // %x

    if (num >= 16)
        ft_puthex(num / 16, uppercase);
    ft_putchar(base[num % 16]);
}
```

**Indexation directe :** `base[num % 16]`

</td>
<td>

### 🔹 Pointeurs

**Format :**
```c
int ft_putpointer(void *ptr)
{
    int printed = 0;

    if (!ptr)
        return (ft_putstr("(nil)"));

    printed += ft_putstr("0x");  // Préfixe
    printed += ft_puthex((unsigned long long)ptr, 0);
    return (printed);
}
```

**Cast `unsigned long long` :** portabilité 32/64-bit

</td>
</tr>
</table>

---

## 🔢 Valeur de Retour

**Toutes les fonctions retournent le nombre de caractères imprimés :**

```c
int count;

count = ft_printf("Hello");           // → 5
count = ft_printf("%d", 42);          // → 2
count = ft_printf("%s %d", "Age:", 25); // → 7 ("Age: 25")
count = ft_printf("%p", NULL);        // → 5 ("(nil)")
```

Si `NULL` est passé comme format → retourne `-1`

---

## 🛠️ Compilation

```bash
# Compiler la bibliothèque
make

# Nettoyer les fichiers objets
make clean

# Tout nettoyer
make fclean

# Recompiler complètement
make re
```

**Makefile :**
```makefile
CC = cc
FLAG = -Wall -Wextra -Werror

SRCS = ft_printf.c \
       utils/ft_putchar.c \
       utils/ft_puthex.c \
       utils/ft_putnbr.c \
       utils/ft_putpointer.c \
       utils/ft_putstr.c \
       utils/ft_putunsigned.c \
       utils/ft_putunbr.c

NAMELIB = libftprintf.a

${NAMELIB}: ${OBJ}
    ar rcs ${NAMELIB} ${OBJ}
```

---

## 💻 Utilisation

### Exemple Complet

```c
#include "ft_printf.h"

int main(void)
{
    int age = 25;
    char *name = "Alice";
    void *ptr = &age;

    ft_printf("Nom: %s\n", name);           // Nom: Alice
    ft_printf("Age: %d ans\n", age);        // Age: 25 ans
    ft_printf("Hex: %x / %X\n", 255, 255);  // Hex: ff / FF
    ft_printf("Pointeur: %p\n", ptr);       // Pointeur: 0x7ffe...
    ft_printf("Unsigned: %u\n", -1);        // Unsigned: 4294967295
    ft_printf("Pourcentage: 50%%\n");       // Pourcentage: 50%

    // Retourne nombre de caractères
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

## ⚠️ Limitations (Pas de Bonus)

Cette implémentation **NE supporte PAS** :

❌ Flags (`-`, `0`, `+`, ` `, `#`)
❌ Largeur de champ (`%10d`, `%-5s`)
❌ Précision (`%.2f`, `%.5s`)
❌ Modificateurs (`%ld`, `%lld`, `%hd`)
❌ Formats avancés (`%f`, `%e`, `%g`, `%n`)

C'est une version **basique** avec les 9 conversions essentielles.

---

## 📋 Détails des Fonctions

<details>
<summary><b>📁 utils/ft_putchar.c</b></summary>

```c
int ft_putchar(char c)
{
    return (write(1, &c, 1));
}
```

**Simple :** écrit 1 caractère sur stdout, retourne 1

</details>

<details>
<summary><b>📁 utils/ft_putstr.c</b></summary>

```c
int ft_putstr(char *s)
{
    int printed = 0;

    if (!s)
        return (ft_putstr("(null)"));
    while (*s)
        printed += ft_putchar(*s++);
    return (printed);
}
```

**Gestion NULL :** affiche `(null)` si `s == NULL`

</details>

<details>
<summary><b>📁 utils/ft_putnbr.c</b></summary>

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

**Cast long :** évite les débordements avec INT_MIN
**Récursif :** divise par 10 jusqu'à un seul chiffre

</details>

<details>
<summary><b>📁 utils/ft_putunbr.c</b></summary>

```c
int ft_putunbr(unsigned int n)
{
    int printed = 0;

    if (n >= 10)
        printed += ft_putunbr(n / 10);
    printed += ft_putchar((n % 10) + '0');
    return (printed);
}
```

**Sans signe :** identique à `ft_putnbr` mais sans gestion du négatif

</details>

<details>
<summary><b>📁 utils/ft_puthex.c</b></summary>

```c
int ft_puthex(unsigned long long num, int uppercase)
{
    char *base;
    int printed = 0;

    if (uppercase)
        base = "0123456789ABCDEF";
    else
        base = "0123456789abcdef";

    if (num >= 16)
        printed += ft_puthex(num / 16, uppercase);
    printed += ft_putchar(base[num % 16]);
    return (printed);
}
```

**Paramètre uppercase :** 0 pour minuscules, 1 pour majuscules
**Récursif :** divise par 16 (base hexadécimale)

</details>

<details>
<summary><b>📁 utils/ft_putpointer.c</b></summary>

```c
int ft_putpointer(void *ptr)
{
    int printed = 0;

    if (!ptr)
        return (ft_putstr("(nil)"));

    printed += ft_putstr("0x");
    printed += ft_puthex((unsigned long long)ptr, 0);
    return (printed);
}
```

**Format :** `0x` + adresse en hexadécimal minuscule
**NULL :** affiche `(nil)` au lieu de `0x0`

</details>

---

<div align="center">

## 📊 Résumé

| Métrique | Valeur |
|:--------:|:------:|
| ![](https://img.shields.io/badge/Lignes-273-blue?style=flat-square) | ![](https://img.shields.io/badge/Fichiers-8_.c-informational?style=flat-square) |
| ![](https://img.shields.io/badge/Conversions-9-blueviolet?style=flat-square) | ![](https://img.shields.io/badge/Bonus-Non-red?style=flat-square) |
| ![](https://img.shields.io/badge/Récursif-✓-success?style=flat-square) | ![](https://img.shields.io/badge/NULL_safe-✓-success?style=flat-square) |

---

**Made with ❤️ for 42 Bangkok**

[![Back to top](https://img.shields.io/badge/⬆-Retour_en_haut-blue?style=for-the-badge)](#-ft_printf---mon-printf-personnalisé)

</div>
