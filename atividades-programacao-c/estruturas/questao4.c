#include <stdio.h>
#include <math.h>

typedef struct {
    double r;
    double a;
} Polar;

typedef struct {
    double x;
    double y;
} Cartesiana;

int main(void) {
    Polar polar;
    Cartesiana cartesiana;
    printf("Digite o raio (r): ");
    if (scanf("%lf", &polar.r) != 1) return 1;
    printf("Digite o angulo em radianos (a): ");
    if (scanf("%lf", &polar.a) != 1) return 1;
    cartesiana.x = polar.r * cos(polar.a);
    cartesiana.y = polar.r * sin(polar.a);
    printf("Coordenadas cartesianas: x = %.4f, y = %.4f\n", cartesiana.x, cartesiana.y);
    return 0;
}
