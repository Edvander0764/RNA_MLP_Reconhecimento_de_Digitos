#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h>

#define ENTRADAS 16
#define OCULTOS 2
#define AMOSTRAS 6
#define EPOCAS 1000
#define TAXA 0.1

// ---------- FUNÇÕES DE ATIVAÇÃO ----------

float sigmoide(float x) {
    return 1.0 / (1.0 + exp(-x));
}

float dsigmoide(float y) {
    return y * (1.0 - y);
}

// ---------- PROGRAMA PRINCIPAL ----------

int main() {

    SetConsoleOutputCP(CP_UTF8);
    srand(time(NULL));

    // ---------- CONJUNTO DE TREINO ----------

    float X[AMOSTRAS][ENTRADAS] = {
        // Dígito 0
        {1,1,1,1,
         1,0,0,1,
         1,0,0,1,
         1,1,1,1},

        {1,1,1,1,
         1,0,0,1,
         1,0,0,1,
         1,1,1,1},

        {1,1,1,1,
         1,0,0,1,
         1,0,0,1,
         1,1,1,1},

        // Dígito 1
        {0,1,0,0,
         1,1,0,0,
         0,1,0,0,
         1,1,1,0},

        {0,1,0,0,
         1,1,0,0,
         0,1,0,0,
         1,1,1,0},

        {0,1,0,0,
         1,1,0,0,
         0,1,0,0,
         1,1,1,0}
    };

    float d[AMOSTRAS] = {0,0,0,1,1,1};

    // ---------- PESOS E BIAS ----------

    float w1[OCULTOS][ENTRADAS];
    float w2[OCULTOS];
    float b1[OCULTOS];
    float b2;

    for (int i = 0; i < OCULTOS; i++) {
        for (int j = 0; j < ENTRADAS; j++)
            w1[i][j] = ((float)rand() / RAND_MAX) - 0.5;

        w2[i] = ((float)rand() / RAND_MAX) - 0.5;
        b1[i] = ((float)rand() / RAND_MAX) - 0.5;
    }

    b2 = ((float)rand() / RAND_MAX) - 0.5;

    // ---------- TREINAMENTO ----------

    printf("\n================ TREINAMENTO ================\n");

    for (int epoca = 0; epoca < EPOCAS; epoca++) {

        int erros = 0;
        float erro_quadratico_total = 0.0;

        for (int a = 0; a < AMOSTRAS; a++) {

            // ----- FORWARD -----
            float h[OCULTOS];

            for (int i = 0; i < OCULTOS; i++) {
                float soma = b1[i];
                for (int j = 0; j < ENTRADAS; j++)
                    soma += w1[i][j] * X[a][j];
                h[i] = sigmoide(soma);
            }

            float y = b2;
            for (int i = 0; i < OCULTOS; i++)
                y += w2[i] * h[i];
            y = sigmoide(y);

            // ----- ERRO -----
            float erro = d[a] - y;
            erro_quadratico_total += erro * erro;

            if ((y < 0.5 && d[a] == 1) || (y >= 0.5 && d[a] == 0))
                erros++;

            // ----- BACKPROP -----
            float delta_saida = erro * dsigmoide(y);

            printf("\nÉpoca %d | Amostra %d", epoca + 1, a + 1);
            printf("\n  Saída esperada: %.1f", d[a]);
            printf("\n  Saída obtida  : %.6f", y);
            printf("\n  Erro da saída : %.6f", erro);
            printf("\n  Gradiente saída (δ): %.6f", delta_saida);

            float delta_oculto[OCULTOS];
            for (int i = 0; i < OCULTOS; i++) {
                delta_oculto[i] = delta_saida * w2[i] * dsigmoide(h[i]);
                printf("\n  Gradiente neurônio oculto %d: %.6f", i + 1, delta_oculto[i]);
            }

            // ----- ATUALIZAÇÃO -----
            for (int i = 0; i < OCULTOS; i++)
                w2[i] += TAXA * delta_saida * h[i];

            b2 += TAXA * delta_saida;

            for (int i = 0; i < OCULTOS; i++) {
                for (int j = 0; j < ENTRADAS; j++)
                    w1[i][j] += TAXA * delta_oculto[i] * X[a][j];
                b1[i] += TAXA * delta_oculto[i];
            }
        }

        float eqm = erro_quadratico_total / AMOSTRAS;

        printf("\n\nResumo da Época %d", epoca + 1);
        printf("\n  Erros: %d", erros);
        printf("\n  Erro Quadrático Médio : %.6f\n", eqm);
        printf("---------------------------------------------\n");

        if (erros == 0) {
            printf("\n>>> CONVERGIU NA ÉPOCA %d <<<\n", epoca + 1);
            break;
        }
    }

    // ---------- TESTE ----------

    while (1) {

        printf("\n================= TESTE =================\n");
        printf("Digite a matriz 4x4 (0 ou 1):\n");

        float entrada[ENTRADAS];

        for (int i = 0; i < ENTRADAS; i++) {
            do {
                printf("Entrada [%d]: ", i + 1);
                scanf("%f", &entrada[i]);
            } while (entrada[i] != 0 && entrada[i] != 1);
        }

        float h[OCULTOS];
        for (int i = 0; i < OCULTOS; i++) {
            float soma = b1[i];
            for (int j = 0; j < ENTRADAS; j++)
                soma += w1[i][j] * entrada[j];
            h[i] = sigmoide(soma);
        }

        float y = b2;
        for (int i = 0; i < OCULTOS; i++)
            y += w2[i] * h[i];
        y = sigmoide(y);

        printf("\nSaída da rede: %.6f\n", y);
        printf("Resultado: DIGITO %d\n", (y >= 0.5));

        printf("\nTestar novamente? (1 = sim / 0 = nao): ");
        int continuar;  
        scanf("%d", &continuar);
        if (!continuar) break;
    }
    return 0;
}
