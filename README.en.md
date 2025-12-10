<div align="center">
  <img height="200" src="https://raw.githubusercontent.com/ayogun/42-project-badges/main/badges/ft_printfm.png" alt="ft_printf" />
</div>

# ft_printf - Custom Printf Recreation

The `ft_printf` project consists of recreating the standard `printf()` function in C. This project is an excellent introduction to **variadic functions** and handling variable arguments.

## Status
<div align="center">

![42 Bangkok](https://img.shields.io/badge/42-Bangkok-000000?style=for-the-badge&logo=42&logoColor=white)
![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Norminette](https://img.shields.io/badge/Norminette-passing-success?style=for-the-badge)

[![Français](https://img.shields.io/badge/🇫🇷_Français-Cliquez_ici-blue?style=for-the-badge)](README.md)

</div>

---

## Overview

The goal is to create your own version of `printf()`, capable of handling different data types and conversions. This exercise improves understanding of variadic functions and allows practice in writing extensible and robust code.

## Useful Resources

- [Notion's Oceano - ft_printf](https://suspectedoceano.notion.site/printf-06cba643d653410bb03417532ca71c25)
- [Ft_printf Tester Francinette](https://github.com/xicodomingues/francinette)

---

## 📋 Mandatory Part

<table>
  <tr>
    <th>Program name</th>
    <td>libftprintf.a</td>
  </tr>
  <tr>
    <th>Turn in files</th>
    <td>Makefile, *.h, *.c</td>
  </tr>
  <tr>
    <th>Makefile</th>
    <td>Yes</td>
  </tr>
  <tr>
    <th>External functs.</th>
    <td>malloc, free, write, va_start, va_arg, va_copy, va_end</td>
  </tr>
  <tr>
    <th>Libft authorized</th>
    <td>Yes</td>
  </tr>
  <tr>
    <th>Description</th>
    <td>Implement your own version of the printf() function from libc.</td>
  </tr>
</table>

### Important Rules
- Global variables are forbidden.
- Subfunctions should be defined as `static`.
- All .c files must compile with the flags `-Wall -Wextra -Werror`.
- Use `ar` to create the library; `libtool` is not permitted.

---

## 📂 Project Structure

```
ft_printf/
├── 📄 Makefile              # Compilation → libftprintf.a
├── 📄 ft_printf.h           # Header (prototypes + includes)
├── 📄 ft_printf.c           # Main function + parsing
│
└── 📁 utils/                # Utility functions (7 files)
    ├── ft_putchar.c         # Print 1 character
    ├── ft_putstr.c          # Print string
    ├── ft_putnbr.c          # Print signed int
    ├── ft_putunbr.c         # Print unsigned
    ├── ft_putunsigned.c     # Print unsigned (alias)
    ├── ft_puthex.c          # Print hexadecimal
    └── ft_putpointer.c      # Print pointer
```

---

## 🎯 Implemented Conversions

The `ft_printf` function supports the following conversions:

<details open>
<summary><b>Click to see conversions</b></summary>

| Format | Type | Description | Example |
|:------:|:-----|:------------|:--------|
| **%c** | `char` | Print a character | `ft_printf("%c", 'A')` → `A` |
| **%s** | `char*` | Print a string | `ft_printf("%s", "Hello")` → `Hello` |
| **%p** | `void*` | Print a pointer (0x...) | `ft_printf("%p", ptr)` → `0x7ffe...` |
| **%d** | `int` | Print signed decimal | `ft_printf("%d", -42)` → `-42` |
| **%i** | `int` | Print integer (= %d) | `ft_printf("%i", 42)` → `42` |
| **%u** | `unsigned int` | Print unsigned number | `ft_printf("%u", 42)` → `42` |
| **%x** | `unsigned int` | Lowercase hexadecimal | `ft_printf("%x", 255)` → `ff` |
| **%X** | `unsigned int` | Uppercase hexadecimal | `ft_printf("%X", 255)` → `FF` |
| **%%** | N/A | Print % character | `ft_printf("%%")` → `%` |

</details>

---

## 🛠️ Compilation and Usage

### Compile the Library

```bash
# Compile
make

# Clean object files
make clean

# Clean everything
make fclean

# Recompile completely
make re
```

### Use in Your Code

```c
#include "ft_printf.h"

int main(void)
{
    int age = 25;
    char *name = "Alice";
    void *ptr = &age;

    // Usage examples
    ft_printf("Name: %s\n", name);          // Name: Alice
    ft_printf("Age: %d years\n", age);      // Age: 25 years
    ft_printf("Hex: %x / %X\n", 255, 255);  // Hex: ff / FF
    ft_printf("Pointer: %p\n", ptr);        // Pointer: 0x7ffe...
    ft_printf("Unsigned: %u\n", 42);        // Unsigned: 42
    ft_printf("Percentage: 50%%\n");        // Percentage: 50%

    // Returns number of characters printed
    int count = ft_printf("Test");          // count = 4

    return (0);
}
```

### Compile with ft_printf

```bash
gcc main.c -L. -lftprintf -o program
./program
```

---

## 💡 Implementation Highlights

<details>
<summary><b>🔹 Recursive Approach</b></summary>

All numeric conversions use recursion for elegant and compact code:

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
        printed += ft_putnbr(nb / 10);  // Recursion
    printed += ft_putchar((nb % 10) + '0');
    return (printed);
}
```

</details>

<details>
<summary><b>🔹 NULL Handling</b></summary>

NULL strings and NULL pointers are handled correctly:

```c
ft_printf("%s", NULL)    // → (null)
ft_printf("%p", NULL)    // → (nil)
```

</details>

<details>
<summary><b>🔹 Return Value</b></summary>

Like `printf()`, the function returns the number of characters printed:

```c
int count = ft_printf("Hello World");  // count = 11
```

</details>

---

## ⚠️ Limitations

This implementation **DOES NOT support** bonuses:

- ❌ Flags (`-`, `0`, `+`, ` `, `#`)
- ❌ Field width (`%10d`, `%-5s`)
- ❌ Precision (`%.2f`, `%.5s`)
- ❌ Size modifiers (`%ld`, `%lld`)
- ❌ Advanced formats (`%f`, `%e`, `%g`)

This is a **basic** version with the 9 essential conversions.

---

## 📊 Statistics

<div align="center">

| Metric | Value |
|:------:|:-----:|
| **Files** | 8 .c |
| **Lines** | ~273 |
| **Conversions** | 9 |
| **Bonus** | No |

</div>

---

## 🚨 Disclaimer

**🇬🇧 This project has an educational purpose and you should under no circumstances copy and paste.**
**Cheat is bad. Don't cheat.**

**🇫🇷 Ce projet a un but éducatif et vous ne devez en aucun cas faire du copier-coller.**
**Tricher c'est mal. Ne trichez pas.**

---

<div align="center">

**Made with ❤️ for 42 Bangkok**

[![Back to top](https://img.shields.io/badge/⬆-Back_to_top-red?style=for-the-badge)](#ft_printf---custom-printf-recreation)

</div>
