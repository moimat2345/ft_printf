<div align="center">

# 🖨️ ft_printf - My Custom Printf

![42 Bangkok](https://img.shields.io/badge/42-Bangkok-000000?style=for-the-badge&logo=42&logoColor=white)
![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Norminette](https://img.shields.io/badge/Norminette-passing-success?style=for-the-badge)
![Lines](https://img.shields.io/badge/Lines-273-blue?style=for-the-badge)

[![Français](https://img.shields.io/badge/🇫🇷_Français-Cliquez_ici-blue?style=for-the-badge)](README.md)

</div>

---

## 📝 Overview

<table>
<tr>
<td>

**ft_printf** is a recreation of the libc `printf()` function. This project introduces **variadic functions** (`va_list`, `va_start`, `va_arg`, `va_end`) in C.

✨ **Simple and efficient** implementation in **273 lines**

**Supported conversions:** 9 basic formats
**Approach:** Recursive for numeric conversions
**Compilation:** `-Wall -Wextra -Werror`

</td>
<td width="300">

```
📊 Statistics

Files:        8 .c
Lines:        273
Conversions:  9
Bonus:        No
Archive:      libftprintf.a
```

</td>
</tr>
</table>

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

## 🎯 Supported Conversions

<div align="center">

| Format | Type | Description | Example |
|:------:|------|-------------|---------|
| ![](https://img.shields.io/badge/-%25c-blue?style=flat-square) | `char` | Single character | `ft_printf("%c", 'A')` → `A` |
| ![](https://img.shields.io/badge/-%25s-blue?style=flat-square) | `char*` | String | `ft_printf("%s", "Hello")` → `Hello` |
| ![](https://img.shields.io/badge/-%25d-green?style=flat-square) | `int` | Signed decimal | `ft_printf("%d", -42)` → `-42` |
| ![](https://img.shields.io/badge/-%25i-green?style=flat-square) | `int` | Integer (= %d) | `ft_printf("%i", 42)` → `42` |
| ![](https://img.shields.io/badge/-%25u-green?style=flat-square) | `unsigned int` | Unsigned number | `ft_printf("%u", 42)` → `42` |
| ![](https://img.shields.io/badge/-%25x-orange?style=flat-square) | `unsigned int` | Lowercase hexadecimal | `ft_printf("%x", 255)` → `ff` |
| ![](https://img.shields.io/badge/-%25X-orange?style=flat-square) | `unsigned int` | Uppercase hexadecimal | `ft_printf("%X", 255)` → `FF` |
| ![](https://img.shields.io/badge/-%25p-red?style=flat-square) | `void*` | Pointer (0x...) | `ft_printf("%p", ptr)` → `0x7ffe...` |
| ![](https://img.shields.io/badge/-%25%25-purple?style=flat-square) | N/A | Literal % character | `ft_printf("%%")` → `%` |

</div>

---

## ⚙️ How it Works

### Code Architecture

```c
int ft_printf(const char *str, ...)
{
    va_list args;
    int printed = 0;

    va_start(args, str);
    while (*str)
    {
        if (*str == '%')
            printed += ft_format(str, args);  // Dispatch
        else
            printed += ft_putchar(*str);      // Print normal
        str++;
    }
    va_end(args);
    return (printed);  // Number of characters printed
}
```

### Format Dispatching

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

## 💡 Implementation Details

<table>
<tr>
<td width="50%">

### 🔹 Recursive Approach

All numeric conversions use **recursion**:

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
        printed += ft_putnbr(nb / 10); // Recursion
    printed += ft_putchar((nb % 10) + '0');
    return (printed);
}
```

**Advantages:**
- Elegant and compact code
- No buffer needed
- No length calculation

</td>
<td width="50%">

### 🔹 NULL Handling

**NULL strings (`%s`):**
```c
int ft_putstr(char *s)
{
    if (!s)
        return (ft_putstr("(null)"));
    // ...
}
```

**NULL pointers (`%p`):**
```c
int ft_putpointer(void *ptr)
{
    if (!ptr)
        return (ft_putstr("(nil)"));
    // Display 0x...
}
```

**Result:**
- `ft_printf("%s", NULL)` → `(null)`
- `ft_printf("%p", NULL)` → `(nil)`

</td>
</tr>

<tr>
<td>

### 🔹 Hexadecimal

**Two variants:**

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

**Direct indexing:** `base[num % 16]`

</td>
<td>

### 🔹 Pointers

**Format:**
```c
int ft_putpointer(void *ptr)
{
    int printed = 0;

    if (!ptr)
        return (ft_putstr("(nil)"));

    printed += ft_putstr("0x");  // Prefix
    printed += ft_puthex((unsigned long long)ptr, 0);
    return (printed);
}
```

**`unsigned long long` cast:** 32/64-bit portability

</td>
</tr>
</table>

---

## 🔢 Return Value

**All functions return the number of characters printed:**

```c
int count;

count = ft_printf("Hello");           // → 5
count = ft_printf("%d", 42);          // → 2
count = ft_printf("%s %d", "Age:", 25); // → 7 ("Age: 25")
count = ft_printf("%p", NULL);        // → 5 ("(nil)")
```

If `NULL` is passed as format → returns `-1`

---

## 🛠️ Compilation

```bash
# Compile the library
make

# Clean object files
make clean

# Clean everything
make fclean

# Recompile completely
make re
```

**Makefile:**
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

## 💻 Usage

### Complete Example

```c
#include "ft_printf.h"

int main(void)
{
    int age = 25;
    char *name = "Alice";
    void *ptr = &age;

    ft_printf("Name: %s\n", name);          // Name: Alice
    ft_printf("Age: %d years\n", age);      // Age: 25 years
    ft_printf("Hex: %x / %X\n", 255, 255);  // Hex: ff / FF
    ft_printf("Pointer: %p\n", ptr);        // Pointer: 0x7ffe...
    ft_printf("Unsigned: %u\n", -1);        // Unsigned: 4294967295
    ft_printf("Percentage: 50%%\n");        // Percentage: 50%

    // Returns number of characters
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

## ⚠️ Limitations (No Bonus)

This implementation **DOES NOT support**:

❌ Flags (`-`, `0`, `+`, ` `, `#`)
❌ Field width (`%10d`, `%-5s`)
❌ Precision (`%.2f`, `%.5s`)
❌ Modifiers (`%ld`, `%lld`, `%hd`)
❌ Advanced formats (`%f`, `%e`, `%g`, `%n`)

This is a **basic** version with the 9 essential conversions.

---

## 📋 Function Details

<details>
<summary><b>📁 utils/ft_putchar.c</b></summary>

```c
int ft_putchar(char c)
{
    return (write(1, &c, 1));
}
```

**Simple:** writes 1 character to stdout, returns 1

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

**NULL handling:** prints `(null)` if `s == NULL`

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
        printed += ft_putnbr(nb / 10);  // Recursion
    printed += ft_putchar((nb % 10) + '0');
    return (printed);
}
```

**Long cast:** avoids overflow with INT_MIN
**Recursive:** divides by 10 until single digit

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

**Unsigned:** identical to `ft_putnbr` but without negative handling

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

**Uppercase parameter:** 0 for lowercase, 1 for uppercase
**Recursive:** divides by 16 (hexadecimal base)

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

**Format:** `0x` + address in lowercase hexadecimal
**NULL:** prints `(nil)` instead of `0x0`

</details>

---

<div align="center">

## 📊 Summary

| Metric | Value |
|:------:|:-----:|
| ![](https://img.shields.io/badge/Lines-273-blue?style=flat-square) | ![](https://img.shields.io/badge/Files-8_.c-informational?style=flat-square) |
| ![](https://img.shields.io/badge/Conversions-9-blueviolet?style=flat-square) | ![](https://img.shields.io/badge/Bonus-No-red?style=flat-square) |
| ![](https://img.shields.io/badge/Recursive-✓-success?style=flat-square) | ![](https://img.shields.io/badge/NULL_safe-✓-success?style=flat-square) |

---

**Made with ❤️ for 42 Bangkok**

[![Back to top](https://img.shields.io/badge/⬆-Back_to_top-red?style=for-the-badge)](#-ft_printf---my-custom-printf)

</div>
