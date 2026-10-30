#include <stdio.h>

struct Vetor {
    double x;
    double y;
    double z;
};

int main(void) {
    struct Vetor a, b, soma;
    printf("Digite x, y e z do primeiro vetor: ");
    if (scanf("%lf %lf %lf", &a.x, &a.y, &a.z) != 3) return 1;
    printf("Digite x, y e z do segundo vetor: ");
    if (scanf("%lf %lf %lf", &b.x, &b.y, &b.z) != 3) return 1;
    soma.x = a.x + b.x;
    soma.y = a.y + b.y;
    soma.z = a.z + b.z;
    printf("Soma = (%.2f, %.2f, %.2f)\n", soma.x, soma.y, soma.z);
    return 0;
}
