#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define tamanhoSenha 3

//Função para verificar se os dígitos da senha estão no intervalo de 0 a 9
bool validarEntrada(int tentativa[]){
    for(int i = 0; i<tamanhoSenha; i++){
        if(tentativa[i] < 0 || tentativa[i] > 9){
            return false;
        } 
    }
    return true;
}

//Função para verificar se a senha está correta
bool verificarSenha(int tentativa[], int senha[]){
    bool acertou = true;
    int contador = 0;

    for(int i = 0; i<tamanhoSenha; i++){
        bool encontrou = false;

        //Esse if verifica se a senha inteira está correta
        if(tentativa[0] == senha[0] && tentativa[1] == senha[1] && tentativa[2] == senha[2]){
            return acertou;
        }

        //Esse if verifica se há algum dígito correto na posição certa
        if(tentativa[i] == senha[i]){
            printf("O digito %d esta correto na posicao %d \n", tentativa[i], i + 1);
        }
        //Caso contrário, o else verifica se há algum dígito correto, mas na posição errada 
        else{
            acertou = false;
            for(int j = 0; j<tamanhoSenha; j++){
                if(tentativa[i] == senha[j]){
                    encontrou = true;
                    break;
                }
            }
            //Caso a variável encontrou == true, ela retorna a mensagem de dígito correto, se não retorna a mensagem de dígito errado
            if(encontrou){
                printf("O digito %d esta correto, mas na posicao errada \n", tentativa[i]);
            } else{
                printf("O digito %d nao faz parte da senha \n", tentativa[i]);
            }
        }
    }
    return acertou;
}

int main(){
    int senha[3] = {4, 2, 9};
    int tentativa[tamanhoSenha];

    while(true){
        printf("Digite a combinacao de 3 digitos para abrir o cofre (Digitos separados por espaco): \n");

        char linha[100]; // Buffer para capturar entrada
        char resto; //Variável para capturar se há mais que 3 dígitos

        //Verifica se há algum erro na entrada
        //A função fgets() serve para receber dados do usuário e aloca na variável linha
        if (!fgets(linha, sizeof(linha), stdin)) {
            printf("Erro ao ler entrada. Tente novamente.\n");
            continue;
        }
        
        //A função sscanf aloca o que está na variável linha nas outras variáveis
        int lidos = sscanf(linha, "%d %d %d %c", &tentativa[0], &tentativa[1], &tentativa[2], &resto);

        //Esse if verifica se a senha tem mais que 3 dígitos ou não está no intervalo de 0 a 9, retornando uma mensagem de erro
        if(lidos!=tamanhoSenha || !validarEntrada(tentativa)){
            printf("Entrada invalida. Tente novamente. \n");
            continue;
        }

        //Caso o retorno da função verificarSenha == true, imprime a mensagem de fim do programa 
        if(verificarSenha(tentativa, senha)){
            printf("Parabens! Conseguiu desvendar o cofre! \n");
            break;
        }
    }
    return 0;
}