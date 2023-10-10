#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

#define afficher(...) do {                      \
        printf("ligne %d : ", __LINE__)  ;      \
        printf(__VA_ARGS__);                    \
        printf("\n");                           \
        } while(0)
#define sommer(A,B) ((A) + (B))

int main(void) {

    afficher("%d", sommer(1, 2));
    afficher("%d", sommer(INT_MIN, -1));
    afficher("%d", sommer(INT_MAX, 1));
    afficher("%lld", sommer(3LL, 4LL));
    afficher("%lld", sommer(LLONG_MIN, -1));
    afficher("%lld", sommer(LLONG_MAX, 1));
    const bool INCLURE_CAS_SPECIAL = true;

    if (INCLURE_CAS_SPECIAL)
        afficher("%lld - %lld", sommer(INT_MIN, -1LL), sommer(INT_MAX, 1LL));
    else
        afficher("%s", "Calcul spécial pas inclus.");

    return EXIT_SUCCESS;
}