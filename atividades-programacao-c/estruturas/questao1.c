#include <stdio.h>

typedef struct {
    int hora;
    int minutos;
    int segundos;
} Horario;

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct {
    Data data;
    Horario horario;
    char descricao[200];
} Compromisso;

int main(void) {
    Compromisso compromisso = {{29, 10, 2026}, {14, 30, 0}, "Reuniao de equipe"};
    printf("Compromisso: %s\n", compromisso.descricao);
    printf("Data: %02d/%02d/%04d\n", compromisso.data.dia, compromisso.data.mes, compromisso.data.ano);
    printf("Horario: %02d:%02d:%02d\n", compromisso.horario.hora, compromisso.horario.minutos, compromisso.horario.segundos);
    return 0;
}
