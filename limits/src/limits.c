#include <stdio.h>
#include <stddef.h>  // Wymagane dla ptrdiff_t i size_t
#include <stdbool.h> // Wymagane dla bool (C99)

int main() {
    printf("=== Rozmiary podstawowe ===\n");
    printf("Rozmiar short:       %zu bajt(y)\n", sizeof(short));
    printf("Rozmiar int:         %zu bajt(y)\n", sizeof(int));
    printf("Rozmiar long:        %zu bajt(y)\n", sizeof(long));
    // 3. long long - Gwarantowane min. 64 bity (ważne, bo 'long' bywa 32-bitowy na Windows)
    // 2. float - Aby zobaczyć różnicę precyzji względem double
    printf("Rozmiar float:       %zu bajt(y)\n", sizeof(float));
    printf("Rozmiar long long:   %zu bajt(y)\n", sizeof(long long));
    printf("Rozmiar double:      %zu bajt(y)\n", sizeof(double));
    printf("Rozmiar long double: %zu bajt(y)\n", sizeof(long double));

    // Poprawna nazwa typu to ptrdiff_t (z nagłówka stddef.h)
    printf("Rozmiar ptrdiff_t:   %zu bajt(y)\n", sizeof(ptrdiff_t));

    // 1. char - Zawsze 1 bajt, ale warto to widzieć jako punkt odniesienia
    printf("Rozmiar char:        %zu bajt(y)\n", sizeof(char));

    // 4. void* (wskaźnik) - To definiuje, czy system jest 32- czy 64-bitowy
    printf("Rozmiar wskaznika:   %zu bajt(y)\n", sizeof(void*));

    // 5. size_t - Typ zwracany przez sizeof, służy do indeksowania tablic
    printf("Rozmiar size_t:      %zu bajt(y)\n", sizeof(size_t));

    // 6. bool - Wymaga biblioteki stdbool.h
    printf("Rozmiar bool:        %zu bajt(y)\n", sizeof(bool));

    return 0;
}
