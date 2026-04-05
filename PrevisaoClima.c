#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void obterMatrizDeProbabilidade(float matriProbabilidade[2][2]);
void obterEstadoInicial(float *estadoInicial);
void obterProximoEstado(float *probabilidadeProximoEstado, float matrizProbabilidade[2][2], char estadoAtual[6]);
void grava(char *info);
void limparArquivo();

#define ITERACOES 365

FILE *bd;

int main()
{
    srand(time(NULL));

    float matrizProbabilidade[2][2];
    obterMatrizDeProbabilidade(matrizProbabilidade);

    float *estadoInicial = malloc(sizeof(float *) * 2);
    obterEstadoInicial(estadoInicial);

    char estadoAtual[6] = "Sol";
    int controlador = 1;

    int contadorSol = 1;
    int contadorChuva = 0;

    limparArquivo();
    grava("dia,estado\n1,Sol");
    while (controlador <= ITERACOES)
    {
        obterProximoEstado(estadoInicial, matrizProbabilidade, estadoAtual);

        if (strcmp(estadoAtual, "Sol") == 0)
            contadorSol++;
        else
            contadorChuva++;

        controlador++;

        char info[100];
        snprintf(info, sizeof(info), "%d,%s", controlador, estadoAtual);

        grava(info);
    }

    printf("Foram %d dias de Sol e %d dias de chuva", contadorSol, contadorChuva);

    return 0;
}

void obterMatrizDeProbabilidade(float matriProbabilidade[2][2])
{
    matriProbabilidade[0][0] = 0.8;
    matriProbabilidade[0][1] = 0.2;
    matriProbabilidade[1][0] = 0.4;
    matriProbabilidade[1][1] = 0.6;

    return;
}

void obterEstadoInicial(float *estadoInicial)
{
    //(1,0) 100% do estado ser Sol
    //(0,1) 100% do estado ser chuva
    estadoInicial[0] = 1;
    estadoInicial[1] = 0;

    return;
}

void obterProximoEstado(float *probabilidadeProximoEstado, float matrizProbabilidade[2][2], char estadoAtual[6])
{
    float p0 = probabilidadeProximoEstado[0];
    float p1 = probabilidadeProximoEstado[1];
    probabilidadeProximoEstado[0] = p0 * matrizProbabilidade[0][0] + p1 * matrizProbabilidade[1][0];
    probabilidadeProximoEstado[1] = p0 * matrizProbabilidade[0][1] + p1 * matrizProbabilidade[1][1];

    float numeroEscolhido = (float)rand() / (float)RAND_MAX;

    if (numeroEscolhido <= probabilidadeProximoEstado[0] && strcmp(estadoAtual, "Sol") != 0)
    {
        strcpy(estadoAtual, "Sol");
        probabilidadeProximoEstado[0] = matrizProbabilidade[0][0];
        probabilidadeProximoEstado[1] = matrizProbabilidade[0][1];
    }

    if (numeroEscolhido > probabilidadeProximoEstado[0] && strcmp(estadoAtual, "Sol") == 0)
    {
        strcpy(estadoAtual, "Chuva");
        probabilidadeProximoEstado[0] = matrizProbabilidade[1][0];
        probabilidadeProximoEstado[1] = matrizProbabilidade[1][1];
    }

    printf("\nO estado atual e %s\n", estadoAtual);
    printf("A probabilidade de mudanca para o proximo estado sao: (%f, %f)\n\n", probabilidadeProximoEstado[0], probabilidadeProximoEstado[1]);
}

void grava(char *info)
{
    // abre para adicionar dados
    bd = fopen("previsaoClima.csv", "a");
    fprintf(bd, "%s\n", info);
    // fecha arquivo
    fclose(bd);
}

void limparArquivo() {
    FILE *bd = fopen("previsaoClima.csv", "w");
    if (bd != NULL) {
        fclose(bd);
    }
}