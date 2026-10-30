#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[100];
    int idade;
    char endereco[200];
} Pessoa;

int main(void) {
    Pessoa pessoa;
    printf("Digite o nome: ");
    fgets(pessoa.nome, sizeof(pessoa.nome), stdin);
    pessoa.nome[strcspn(pessoa.nome, "\n")] = '\0';
    printf("Digite a idade: ");
    if (scanf("%d", &pessoa.idade) != 1) return 1;
    getchar();
    printf("Digite o endereco: ");
    fgets(pessoa.endereco, sizeof(pessoa.endereco), stdin);
    pessoa.endereco[strcspn(pessoa.endereco, "\n")] = '\0';
    printf("\nNome: %s\nIdade: %d\nEndereco: %s\n", pessoa.nome, pessoa.idade, pessoa.endereco);
    return 0;
}
