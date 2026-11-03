#include <stdio.h>
#include <stddef.h>    // Required for ptrdiff_t and size_t
#include <stdbool.h>   // Required for bool (C99 standard)
#include <stdint.h>    // Required for intptr_t, uintptr_t, intmax_t
#include <sys/types.h> // Required for off_t, time_t, ssize_t
#include <stdlib.h>    // Required for getenv
#include <string.h>    // Required for strncmp

/**
 * Checks whether the current system locale is set to Polish.
 * Detects standard locale environment variables: LC_ALL, LC_MESSAGES, LANG.
 * Defaults to English if none of these variables indicate Polish.
 */
static bool is_polish_locale(void) {
    const char *locale = getenv("LC_ALL");
    if (!locale || !*locale) {
        locale = getenv("LC_MESSAGES");
    }
    if (!locale || !*locale) {
        locale = getenv("LANG");
    }

    if (locale && (strncmp(locale, "pl", 2) == 0 || strncmp(locale, "PL", 2) == 0)) {
        return true;
    }
    return false;
}

int main(void) {
    const bool pl = is_polish_locale();

    /* -------------------------------------------------------------
     * 1. Basic Character and Integer Types
     * ------------------------------------------------------------- */
    if (pl) {
        printf("=== Podstawowe typy calkowite i znakowe ===\n");
        printf("Rozmiar char:        %zu bajt(y)   /* Zawsze 1 bajt (zgodnie ze standardem C) */\n", sizeof(char));
        printf("Rozmiar short:       %zu bajt(y)   /* Zwykle 16-bitowa liczba calkowita */\n", sizeof(short));
        printf("Rozmiar int:         %zu bajt(y)   /* Podstawowa jednostka calkowita procesora (zwykle 32 bity) */\n", sizeof(int));
        printf("Rozmiar long:        %zu bajt(y)   /* 32 bity na ILP32 (32-bit), 64 bity na LP64 (64-bit) */\n", sizeof(long));
        printf("Rozmiar long long:   %zu bajt(y)   /* Gwarantowane minimum 64 bity (od C99) */\n", sizeof(long long));
        printf("Rozmiar intmax_t:    %zu bajt(y)   /* Najwiekszy typ calkowity obslugiwany przez kompilator */\n", sizeof(intmax_t));
        printf("Rozmiar bool:        %zu bajt(y)   /* Typ logiczny true/false (ze stdbool.h) */\n\n", sizeof(bool));
    } else {
        printf("=== Basic Character and Integer Types ===\n");
        printf("Size of char:        %zu byte(s)   /* Always 1 byte by C standard definition */\n", sizeof(char));
        printf("Size of short:       %zu byte(s)   /* Typically 16-bit signed integer */\n", sizeof(short));
        printf("Size of int:         %zu byte(s)   /* Natural CPU integer word size (typically 32-bit) */\n", sizeof(int));
        printf("Size of long:        %zu byte(s)   /* 32-bit on ILP32 (32-bit CPU), 64-bit on LP64 (64-bit CPU) */\n", sizeof(long));
        printf("Size of long long:   %zu byte(s)   /* Guaranteed at least 64 bits (since C99) */\n", sizeof(long long));
        printf("Size of intmax_t:    %zu byte(s)   /* Maximum-width integer type supported by the compiler */\n", sizeof(intmax_t));
        printf("Size of bool:        %zu byte(s)   /* Boolean type true/false (from stdbool.h) */\n\n", sizeof(bool));
    }

    /* -------------------------------------------------------------
     * 2. Floating-Point Types
     * ------------------------------------------------------------- */
    if (pl) {
        printf("=== Typy zmiennoprzecinkowe ===\n");
        printf("Rozmiar float:       %zu bajt(y)   /* Pojedyncza precyzja IEEE 754 (zwykle 32 bity) */\n", sizeof(float));
        printf("Rozmiar double:      %zu bajt(y)   /* Podwojna precyzja IEEE 754 (zwykle 64 bity) */\n", sizeof(double));
        printf("Rozmiar long double: %zu bajt(y)   /* Rozszerzona precyzja (zalezna od platformy: 64, 80 lub 128 bitow) */\n\n", sizeof(long double));
    } else {
        printf("=== Floating-Point Types ===\n");
        printf("Size of float:       %zu byte(s)   /* Single-precision IEEE 754 (typically 32-bit) */\n", sizeof(float));
        printf("Size of double:      %zu byte(s)   /* Double-precision IEEE 754 (typically 64-bit) */\n", sizeof(double));
        printf("Size of long double: %zu byte(s)   /* Extended precision (platform dependent: 64, 80, or 128 bits) */\n\n", sizeof(long double));
    }

    /* -------------------------------------------------------------
     * 3. Pointers and Architecture-Defining Types
     * ------------------------------------------------------------- */
    if (pl) {
        printf("=== Wskazniki i typy definiujace architekture ===\n");
        printf("Rozmiar wskaznika:   %zu bajt(y)   /* Definiuje szerokosc szyny adresowej: 4B = 32-bit, 8B = 64-bit */\n", sizeof(void*));
        printf("Rozmiar size_t:      %zu bajt(y)   /* Typ bez znaku zwracany przez sizeof, do indeksowania pamieci */\n", sizeof(size_t));
        printf("Rozmiar ssize_t:     %zu bajt(y)   /* Typ ze znakiem, zwracany przez wywolania systemowe read()/write() */\n", sizeof(ssize_t));
        printf("Rozmiar ptrdiff_t:   %zu bajt(y)   /* Typ ze znakiem, wynik odejmowania dwoch wskaznikow */\n", sizeof(ptrdiff_t));
        printf("Rozmiar intptr_t:    %zu bajt(y)   /* Typ calkowity ze znakiem, mieszczacy wskaznik bez straty danych */\n\n", sizeof(intptr_t));
    } else {
        printf("=== Pointers and Architecture-Defining Types ===\n");
        printf("Size of pointer:     %zu byte(s)   /* Defines CPU address width: 4B = 32-bit, 8B = 64-bit */\n", sizeof(void*));
        printf("Size of size_t:      %zu byte(s)   /* Unsigned type returned by sizeof, used for memory indexing */\n", sizeof(size_t));
        printf("Size of ssize_t:     %zu byte(s)   /* Signed size type returned by read()/write() system calls */\n", sizeof(ssize_t));
        printf("Size of ptrdiff_t:   %zu byte(s)   /* Signed type representing difference between two pointers */\n", sizeof(ptrdiff_t));
        printf("Size of intptr_t:    %zu byte(s)   /* Signed integer guaranteed to hold a void* pointer */\n\n", sizeof(intptr_t));
    }

    /* -------------------------------------------------------------
     * 4. System and OS Types (OpenWrt / Linux specifics)
     * ------------------------------------------------------------- */
    if (pl) {
        printf("=== Typy systemowe i POSIX (wazne dla OpenWrt) ===\n");
        printf("Rozmiar time_t:      %zu bajt(y)   /* Format czasu: 4B oznacza problem roku 2038 (Y2038), 8B jest odporne */\n", sizeof(time_t));
        printf("Rozmiar off_t:       %zu bajt(y)   /* Rozmiar przesuniecia pliku: 4B = max 2GB/4GB, 8B = duze pliki (LFS) */\n", sizeof(off_t));
    } else {
        printf("=== System and POSIX Types (Important for OpenWrt) ===\n");
        printf("Size of time_t:      %zu byte(s)   /* Timestamp format: 4B has Y2038 issue; 8B is safe past year 2038 */\n", sizeof(time_t));
        printf("Size of off_t:       %zu byte(s)   /* File offset: 4B limits files to 2GB/4GB; 8B enables large files (LFS) */\n", sizeof(off_t));
    }

    return 0;
}
