#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define TAM_TAB 4 //Define o tamanho do tabuleiro em 4x4

//Estrutura que representa a carta do jogo
typedef struct carta{
    char nome[50]; // Nome da carta
    int virada; // para identificar se a carta está virada(1) ou oculta(0)
}Carta;

//Temas disponíveis para o jogador
const char *stdValley[] = {
    "Penny", "Leah", "Harvey", "Caroline", "Clint", "Gunther", "Lewis", "Robin"
};

const char *folclore[] = {
    "Saci", "Cuca", "Curupira", "Mula", "Iara", "Lobisomem", "Boto", "Boitata"
};

const char *animais[] = {
    "Gato", "Cachorro", "Capivara", "Arara-Azul", "Lobo-Guara", "Piaba", "Cavalo", "Coruja"
};

//Função que retorna o tema escolhido pelo jogador
const char** escolherTema(int tema){
    if (tema == 1) {
        return stdValley;
    } else if (tema == 2) {
        return folclore;
    } else if (tema == 3) {
        return animais;
    } else {
        return NULL;
    }
}

//FUnção para embaralhar as cartas do jogo
void embaralharCartas(Carta *cartas, int n){
    srand(time(NULL)); // Semente que gera números aleatórios para a distribuição das cartas a cada rodada

    for(int i = n - 1; i > 0; i--){
        int j = rand() % (i + 1);
        Carta temp = cartas[i];
        cartas[i] = cartas[j];
        cartas[j] = temp;
    }
}
//Função para gerar o tabuleiro
void gerarTabuleiro(Carta ***tabuleiro, const char **temaEscolhido){
    int totalElementos = TAM_TAB * TAM_TAB; //Total de cartas
    Carta *cartas = malloc(totalElementos * sizeof(Carta)); // Vetor de cartas

    //Para duplicar as palavras e formar pares
    for(int i = 0; i < totalElementos / 2; i++){
        strcpy(cartas[i * 2].nome, temaEscolhido[i]);
        strcpy(cartas[i * 2 + 1].nome, temaEscolhido[i]);
        cartas[i * 2].virada = 0;
        cartas[i * 2 + 1].virada = 0;
    }

    embaralharCartas(cartas, totalElementos); // Embaralha as cartas

    //Matriz dinâmica que aloca a memória para o tabuleiro
    *tabuleiro = malloc(TAM_TAB * sizeof(Carta*));
    for(int i = 0; i < TAM_TAB; i++){
        (*tabuleiro)[i] = malloc(TAM_TAB * sizeof(Carta));
        for(int j = 0; j < TAM_TAB; j++){
            (*tabuleiro)[i][j] = cartas[i * TAM_TAB + j];
        }
    }

    free(cartas); // Libera memória do vetor temporário
}

// Função para exibir o tabuleiro na tela
void mostrarTabuleiro(Carta **tabuleiro){
    printf("\nTabuleiro:\n");
    printf("|||    [ 0,0 ]    |||    [ 0,1 ]    |||    [ 0,2 ]    |||    [ 0,3 ]    \n");
    
    for(int i = 0; i < TAM_TAB; i++){
        for(int j = 0; j < TAM_TAB; j++){
            if(tabuleiro[i][j].virada){
                printf("|||    %-11s", tabuleiro[i][j].nome);
            } else{
                printf("|||    [  *  ]    ");
            }
        }
        printf("\n");
    }
}

// Função para liberar memória do tabuleiro
void limparTabuleiro(Carta **tabuleiro){
    for(int i = 0; i < TAM_TAB; i++){
        free(tabuleiro[i]);
    }
    free(tabuleiro);
}

int main(){
    int jogar = 0;
    
    while(true){
        int tema;
        int contador = 0;
        const char **temaEscolhido;
        Carta **tabuleiro;

        // Pergunta se o jogador quer iniciar o jogo
        if(jogar == 0){
            printf("\nDeseja iniciar o jogo?\n1 - Sim\n2 - Nao\n> ");
            scanf("%d", &jogar);

            if(jogar == 2){
                printf("\nEncerrando o programa...");
                break;
            }
        }

        // Escolha de tema
        printf("\nBem-vindo ao Jogo da Memoria do Felps e da Carolima!\n\n");
        printf("Digite o numero do tema que deseja escolher:\n");
        printf("1 - Personagens do Stardew Valley \n2 - Personagens do Folclore Brasileiro \n3 - Animais\n> ");
        scanf("%d", &tema);

        temaEscolhido = escolherTema(tema);
        if(temaEscolhido == NULL){
            printf("Tema invalido!\n");
            continue;
        }

        gerarTabuleiro(&tabuleiro, temaEscolhido); // Cria o tabuleiro

        int paresEncontrados = 0;
        int totalPares = (TAM_TAB * TAM_TAB) / 2;

        while(paresEncontrados < totalPares){
            int x1, y1, x2, y2;
            mostrarTabuleiro(tabuleiro);
            
            // Jogador escolhe duas cartas
            printf("\nEscolha a primeira carta(linha e coluna): ");
            scanf("%d %d", &x1, &y1);
            printf("Escolha a segunda carta(linha e coluna): ");
            scanf("%d %d", &x2, &y2);

            // Validação das jogadas
            if(x1 < 0 || x1 >= TAM_TAB || y1 < 0 || y1 >= TAM_TAB || 
                x2 < 0 || x2 >= TAM_TAB || y2 < 0 || y2 >= TAM_TAB || 
                tabuleiro[x1][y1].virada || tabuleiro[x2][y2].virada || (x1 == x2 && y1 == y2)){
                printf("\nJogada invalida! Tente novamente.\n");
                continue;
            }

            // Revela as cartas
            tabuleiro[x1][y1].virada = 1;
            tabuleiro[x2][y2].virada = 1;
            mostrarTabuleiro(tabuleiro);

            // Verifica se as cartas são iguais
            if(strcmp(tabuleiro[x1][y1].nome, tabuleiro[x2][y2].nome) == 0){
                printf("\nPar encontrado!\n");
                paresEncontrados++; // Incrementa o número de pares
            } else{
                printf("\nNao eh um par! As cartas serao ocultadas novamente.\n");
                // Caso as cartas não sejam iguais, elas são ocultadas novamente
                tabuleiro[x1][y1].virada = 0;
                tabuleiro[x2][y2].virada = 0;
            }
            
            // Verifica se o jogador encontrou todos os pares
            if(paresEncontrados == totalPares){
                break;
            }

            getchar();
            printf("\nNumero de tentativas: %d\n", ++contador);
            printf("\nPressione Enter para continuar...\n");
            getchar();
        }

        printf("\nParabens! Voce encontrou todos os pares!\n");
        printf("Quantidade de tentativas: %d\n", contador);
        limparTabuleiro(tabuleiro);

        printf("\nDeseja jogar novamente?\n1 - Sim\n2 - Nao\n> ");
        scanf("%d", &jogar);

        if(jogar == 2){
            printf("\nObrigado por jogar!");
            break;
        }
    }

    return 0;
}