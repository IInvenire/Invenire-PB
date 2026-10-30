#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct {
    int hora, minutos, segundos;
} Horario;

typedef struct {
    int dia, mes, ano;
} Data;

typedef struct {
    Data data;
    Horario horario;
    char descricao[200];
} Compromisso;

typedef struct {
    char nome[100];
    int idade;
    char endereco[200];
} Pessoa;

struct Vetor {
    double x, y, z;
};

typedef struct {
    double r, a;
} Polar;

typedef struct {
    double x, y;
} Cartesiana;

int main(void) {
    int opcao;
    do {
        printf("\n=== EXERCICIOS COM STRUCT EM C ===\n");
        printf("1 - Data, horario e compromisso\n");
        printf("2 - Cadastro de pessoa\n");
        printf("3 - Soma de vetores\n");
        printf("4 - Coordenadas polares para cartesianas\n");
        printf("0 - Sair\nEscolha: ");
        if (scanf("%d", &opcao) != 1) return 1;
        getchar();

        switch (opcao) {
            case 1: {
                Compromisso c;
                printf("Digite dia mes ano: ");
                if (scanf("%d %d %d", &c.data.dia, &c.data.mes, &c.data.ano) != 3) return 1;
                printf("Digite hora minutos segundos: ");
                if (scanf("%d %d %d", &c.horario.hora, &c.horario.minutos, &c.horario.segundos) != 3) return 1;
                getchar();
                printf("Descricao: ");
                if (!fgets(c.descricao, sizeof(c.descricao), stdin)) return 1;
                c.descricao[strcspn(c.descricao, "\n")] = '\0';
                printf("Compromisso: %s - %02d/%02d/%04d as %02d:%02d:%02d\n",
                       c.descricao, c.data.dia, c.data.mes, c.data.ano,
                       c.horario.hora, c.horario.minutos, c.horario.segundos);
                break;
            }
            case 2: {
                Pessoa p;
                printf("Nome: ");
                if (!fgets(p.nome, sizeof(p.nome), stdin)) return 1;
                p.nome[strcspn(p.nome, "\n")] = '\0';
                printf("Idade: ");
                if (scanf("%d", &p.idade) != 1) return 1;
                getchar();
                printf("Endereco: ");
                if (!fgets(p.endereco, sizeof(p.endereco), stdin)) return 1;
                p.endereco[strcspn(p.endereco, "\n")] = '\0';
                printf("Nome: %s\nIdade: %d\nEndereco: %s\n", p.nome, p.idade, p.endereco);
                break;
            }
            case 3: {
                struct Vetor a, b, soma;
                printf("Primeiro vetor (x y z): ");
                if (scanf("%lf %lf %lf", &a.x, &a.y, &a.z) != 3) return 1;
                printf("Segundo vetor (x y z): ");
                if (scanf("%lf %lf %lf", &b.x, &b.y, &b.z) != 3) return 1;
                soma.x = a.x + b.x;
                soma.y = a.y + b.y;
                soma.z = a.z + b.z;
                printf("Soma: (%.2f, %.2f, %.2f)\n", soma.x, soma.y, soma.z);
                break;
            }
            case 4: {
                Polar p;
                Cartesiana c;
                printf("Raio: ");
                if (scanf("%lf", &p.r) != 1) return 1;
                printf("Angulo em radianos: ");
                if (scanf("%lf", &p.a) != 1) return 1;
                c.x = p.r * cos(p.a);
                c.y = p.r * sin(p.a);
                printf("Cartesianas: x = %.4f, y = %.4f\n", c.x, c.y);
                break;
            }
            case 0: printf("Encerrando...\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
    return 0;
}
