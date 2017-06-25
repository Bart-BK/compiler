/*
*---------------------------------------------------------------------
*
*   File    : Lexic.c
*   Created : 2017-05-09
*   Modified: 2017-05-31
*
*   Corpo do código principal
*
*---------------------------------------------------------------------
*/

/*
*---------------------------------------------------------------------
*   INCLUDE FILES
*---------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "headers/tokens.h"
#include "headers/erros.h"
#include "headers/tabSimb.h"


/*
*---------------------------------------------------------------------
*   Data structures and variables
*---------------------------------------------------------------------
*/


FILE *arqEntrada;


/*
*---------------------------------------------------------------------
*   Function prototypes
*---------------------------------------------------------------------
*/

char proximo_caractere();
void retrair(int);
void analisadorLexico();

/*
*---------------------------------------------------------------------
*   Main
*---------------------------------------------------------------------
*/

int main(int argc, char const *argv[])
{
    if(argc != 2){
        printf("\nReferencie o arquivo. Ex: ./Portugol teste-01.ptg\n");
        return 1;
    }
    if ((arqEntrada = fopen(argv[1], "r")) == NULL)
        printf("Erro, arquivo nao encontrado\n");
    else {

      tTabelaDeSimbolos tabDeSimbolos; // Estrutura tabela de simbolos
      inicializarTabelaDeSimbolos(&tabDeSimbolos); // Inicializa a tabela

      inicializaTabelaToken(); // Inicializa a tabela de tokens
      analisadorLexico(&tabDeSimbolos); // Faz a análise léxica

      gerarArquivoTabelaDeSimbolos(&tabDeSimbolos,argv[1]); //Gera arquivo de simbolos
      gerarArquivoTabelaDeTokens(head, argv[1], tabDeSimbolos.maiorLexema); // Gera arquivo de tokens
      imprimeEntrada(argv[1]);

      printf("Análise ocorreu com sucesso, arquivos gerados:\n\n%s.err\n%s.tbl\n%s.tok\n\n", argv[1], argv[1] , argv[1]);
    }
    fclose(arqEntrada);

    return 0;
}

/*
*---------------------------------------------------------------------
*   Function definitions
*---------------------------------------------------------------------
*/

void imprimeEntrada (const char *nomeArquivoEntrada) {
  
  rewind(arqEntrada); // Volta pro inicio do arquivo para a análise

  char *arquivoSaidaErro = (char *) malloc(4 + strlen(nomeArquivoEntrada)); // Alocação do arquivo de saida
  sprintf(arquivoSaidaErro,"%s.err", nomeArquivoEntrada); // O arquivo de erro recebe o nome do arquivo de entrada + .err

  arqErros = fopen(arquivoSaidaErro,"w"); // Tenta abrir o arquivo de erro para escrita

  if(arqErros == NULL){ // Se não conseguir criar o arquivo
      printf("Erro ao criar arquivo de erro!");
      exit(0);
  }

  fprintf(arqErros, "Erros lexicos encontrados em \"%s\"\n\n", arquivoSaidaErro); // Primeira linha do arquivo

  // Variáveis

  int iErro; // Incrementador de erro
  int linhaAtual = 1; // Linha atual
  char linha[100]; // Array para receber a linha
  tErrosNumalinha erros; // Estrutura que indica erros em uma linha
  int errosJaImpressos = 0; // Erros já impressos
  char strlinha[4]; // Variável para imprimir a linha

  while ((fgets(linha, sizeof(linha), arqEntrada))!=NULL ) { // Faz a leitura de cada linha do arquivo de entrada
    erros = errosNalinha(linhaAtual); // Analise de erros na linha
    if (erros.quantosErros == 0){ // Se não houver erros na linha
        sprintf(strlinha, "%3d", (int)linhaAtual); // strlinha recebe a linha atual
        fprintf(arqErros,"[%s]%s",strlinha, linha); // Imprime a linha no arquivo
        }
    else for (iErro = 0; iErro < erros.quantosErros; iErro++) { // Se houver erros, 
        sprintf(strlinha, "%3d", (int)linhaAtual); //strlinha recebe a linha atual
        fprintf(arqErros,"[%s]%s",strlinha, linha); // Imprime a linha no arquivo
        imprimeErro(erros.indPrimErro + errosJaImpressos++); // Identifica a posição do erro
    }
    errosJaImpressos = 0; // Reseta os erros na linha
    linhaAtual++; // Incrementa a linha atual
  }

  fprintf(arqErros, "\nTotal de erros encontrados: %d", totErrosEncontrados); // Imprime a quantidade de erros encontrados em todo o arquivo
  free(arquivoSaidaErro);
  fclose(arqErros);
}

char proximo_caractere(){ // Pega o próximo caracter
    char getChar=getc(arqEntrada);
    coluna++;
    if(getChar=='\n'){ // Se o caracter for uma quebra de linha, incrementa a linha e reseta a coluna
        linha++;
        coluna=0;
    }
    return getChar;
}

void retrair(int n){ // Devolve caracter
    fseek(arqEntrada, n*(-1), SEEK_CUR); // Volta uma coluna a partir da posição atual no arquivo
    coluna-=n; 
}


void analisadorLexico(tTabelaDeSimbolos *tabDeSimbolos){ // Autômato
    while(verdade){ // Enquanto não chegar no final do arquivo
        switch(state){ // Estados
        case 0: // Estado inicial
            c = proximo_caractere(); // Recebe próximo caracter
            while (isspace(c)){ 
                c = proximo_caractere();
                state = 0;
            }

            // Verificações do estado 0

            if(isalpha(c)){ state = 1;}
            else if(isdigit(c)){ state = 7;}
            else if (c == '.'){ state = 10;}
            else if(c == '\"'){ state = 3;}
            else if(c == '>'){ state = 15;}
            else if(c == '<'){ state = 18;}
            else if(c == '='){ state = 35;}
            else if(c == EOF){ state = 22;}
            else if(c == ':'){ state = 39;}
            else if(c == ';'){ state = 38;}
            else if(c == '('){ state = 42;}
            else if(c == ')'){ state = 43;}
            else if(c == '*'){ state = 40;}
            else if(c == ','){ state = 41;}
            else if(c == '+'){ state = 26;}
            else if(c == '-'){ state = 23;}
            else if(c == '/'){ state = 29;}
            else {state = 38;}
            break;

        case 1://Estado Identificador
            while(isalpha(c) || isdigit(c) || c == '_'){
               addChar();
               c=proximo_caractere();
            }
            state = 2;
            break;

        case 2://Estado final Identificador
            state = 0;
            retrair(1); // Devolve 1
            instalaTabelaDeSimbolo(tabDeSimbolos,retornaNomeTokenReservado(lexeme)); // Insere o lexema na tabela de simbolos
            instalaLexeme(retornaNomeToken(retornaNomeTokenReservado(lexeme)),retornaNomeTokenReservado(lexeme)); // Instala o nome do token e o token reservado
            lexLen=0;
            break;

        case 3: //Estado Cadeia
            addChar();
            c=proximo_caractere();
            while(isalpha(c) || isdigit(c)){
                addChar();
                c=proximo_caractere();
            }
            if(c == '\n'){ state = 5;}
            else if(c == EOF){ state = 6;}
            else if(c == '\"'){
                state = 4;
                addChar();
            }
            break;

        case 4://Estado final Cadeia
            state =0;
            instalaTabelaDeSimbolo(tabDeSimbolos,tk_CADEIA);
            instalaLexeme(retornaNomeToken(tk_CADEIA), tk_CADEIA);
            lexLen=0;
            break;

        case 5://Estado final de erro na cadeia
        case 6://Estado final de erro na cadeia
                retrair(1); // Devolve 1
                state=0;
                instalaTabelaDeSimbolo(tabDeSimbolos,tk_CADEIA);
                instalaLexeme(retornaNomeToken(tk_CADEIA), tk_CADEIA);
                registraErroLex(linha,coluna,tErroLex_cadeiaNaoFechada);
            break;

        case 7://Estado Digito
            while(isdigit(c)){
                addChar();
                c=proximo_caractere();
            }
            if(isalpha(c)){
                state = 9;
                break;
              }
            if(c =='.'){addChar(); state = 11;}
            else state = 8;
            break;

        case 8://Estado final Digito Inteiro
            state =0;
            retrair(1); // Devolve 1
            instalaTabelaDeSimbolo(tabDeSimbolos,tk_INT);
            instalaLexeme(retornaNomeToken(tk_INT),tk_INT);
            lexLen=0;
            break;

        case 9://Estado final erro Digito Inteiro
            registraErroLex(linha,coluna,tErroLex_delimEsperado);
            retrair(1); // Devolve 1
            instalaTabelaDeSimbolo(tabDeSimbolos,tk_INT);
            instalaLexeme(retornaNomeToken(tk_INT), tk_INT);
            lexLen=0;
            state = 0;
            break;

        case 10://Estado Decimal com ponto inicial
            addChar();
            c=proximo_caractere();
            if(isdigit(c)){
                state = 11;
                addChar();
            }else{
                state=14;
            }
            break;

        case 11://Estado Decimal com ponto na frente
            c=proximo_caractere();
            while(isdigit(c)){
                addChar();
                c=proximo_caractere();
            }
            if(isalpha(c)){ state=12;}
            else state = 13;
            break;

        case 12://Estado final erro no Decimal
            retrair(1); // Devolve 1
            instalaTabelaDeSimbolo(tabDeSimbolos,tk_DEC);
            instalaLexeme(retornaNomeToken(tk_DEC), tk_DEC);
            registraErroLex(linha,coluna,tErroLex_delimEsperado);
            lexLen=0;
            state = 0;
            break;

        case 13://Estado final Decimal
            state = 0;
            retrair(1); // Devolve 1
            instalaTabelaDeSimbolo(tabDeSimbolos,tk_DEC);
            instalaLexeme(retornaNomeToken(tk_DEC), tk_DEC);
            lexLen=0;
            break;

        case 14://Estado final de erro Ponto Isolado
            state=0;
            retrair(1); // Devolve 1
            registraErroLex(linha,coluna,tErroLex_pontoIsolado);
            break;

         case 15://Estado Maior
            addChar();
            c=proximo_caractere();
            if(c == '='){state = 16; addChar();}
            else {state=17;}
            break;

         case 16://Estado final Maior Igual
            state = 0;
            retrair(1); // Devolve 1
            instalaLexeme(retornaNomeToken(tk_maior_igual),tk_maior_igual);
            lexLen=0;
            break;

         case 17://Estado final Maior
            state = 0;
            retrair(1); // Devolve 1
            instalaLexeme(retornaNomeToken(tk_maior), tk_maior);
            lexLen=0;
            break;

         case 18: //Estado Menor
            addChar();
            c=proximo_caractere();
            if(c == '='){state = 19; addChar();}
            else if(c == '>'){ state = 20; addChar();}
            else state = 21;
            break;

         case 19://Estado final Menor Igual
            state = 0;
            retrair(1); // Devolve 1
            instalaLexeme(retornaNomeToken(tk_menor_igual),  tk_menor_igual);
            lexLen=0;
            break;

        case 20://Estado final Diferente
            state = 0;
            retrair(1); // Devolve 1
            instalaLexeme(retornaNomeToken(tk_diferente), tk_diferente);
            lexLen=0;
            break;

        case 21://Estado final Menor
            state = 0;
            retrair(1); // Devolve 1
            instalaLexeme(retornaNomeToken(tk_menor), tk_menor);
            lexLen=0;
            break;

        case 22://Estado Final EOF
            state = 0;
            addChar();
            instalaLexeme(retornaNomeToken(tk_EOF), tk_EOF);
            verdade=0;
            lexLen=0;
            break;

        case 23://Estado Menos
            addChar();
            c = proximo_caractere();
            if(c == '-'){state = 24; addChar();}
            else state = 25;
            break;

        case 24://Estado final Decremento
            state = 0;
            retrair(1); // Devolve 1
            instalaLexeme(retornaNomeToken(tk_decr), tk_decr);
            lexLen=0;
            break;

        case 25://Estado final Menos
            retrair(1); // Devolve 1
            instalaLexeme(retornaNomeToken(tk_menos), tk_menos);
            state = 0;
            lexLen=0;
            break;


        case 26://Estado Mais
            addChar();
            c = proximo_caractere();
            if(c == '+'){state = 29; addChar();}
            else state = 28;
            break;

        case 27://Estado final Incremento
            state = 0;
            retrair(1); // Devolve 1
            instalaLexeme(retornaNomeToken(tk_incr),tk_incr);
            lexLen=0;
            break;

        case 28://Estado final Mais
            state = 0;
            retrair(1); // Devolve 1
            instalaLexeme(retornaNomeToken(tk_mais), tk_mais);
            lexLen=0;
            break;

        case 29://Estado Dividido
            addChar();
            c=proximo_caractere();
            if(c == '*'){ state = 31;}
            else if(c == '/'){ state = 34;}
            else state = 30;
            break;

        case 30://Estado final Dividido
            state = 0;
            retrair(1); // Devolve 1
            instalaLexeme(retornaNomeToken(tk_dividido), tk_dividido);
            lexLen=0;
            break;

        case 31:// Estado Comentario de Bloco
            c=proximo_caractere();
            while(isdigit(c) || isalpha(c)){
                c=proximo_caractere();
            }
            if(c == '*'){ state = 32;}
            else if(c == EOF){ state = 33;}
            break;

        case 32://Estado conteudo Comentario de Bloco
            c=proximo_caractere();
            while(isdigit(c) || isalpha(c)){
                addChar();
                c=proximo_caractere();
            }
            if(c == '/'){ 
              state=0;
              lexLen=0;
              break;
            }
            else if(c == EOF){ state = 34;}
            else{state = 31;}
            break;

        case 33: //Estado final erro Comentario de Bloco
            state=0;
            retrair(1); // Devolve 1
            registraErroLex(linha,coluna,tErroLex_comentarioNaoFechado);
            lexLen=0;
            break;

        case 34://Estado Comentario de linha
            c=proximo_caractere();
            while(isdigit(c) || isalpha(c)){
                addChar();
                c=proximo_caractere();
            }
            if(c == '\n'){ 
              state=0;
              lexLen=0;
            }
            else if(c == EOF){state = 22;}
            break;

        case 35://Estado Igual
            addChar();
            c=proximo_caractere();
            if(c == '='){state = 36;}
            else state = 37;
            break;

        case 36://Estado final Comparação
            instalaLexeme(retornaNomeToken(tk_igual), tk_igual);
            state = 0;
            addChar();
            lexLen=0;
            break;

        case 37:// Estado final Atribuição
            instalaLexeme(retornaNomeToken(tk_atrib), tk_atrib);
            state = 0;
            addChar();
            lexLen=0;
            break;

        case 38://Estado final Ponto e Virgula
            instalaLexeme(retornaNomeToken(tk_pt_virg), tk_pt_virg);
            state = 0;
            addChar();
            lexLen=0;
            break;

        case 39://Estado final Dois Pontos
            instalaLexeme(retornaNomeToken(tk_dois_pts), tk_dois_pts);
            state = 0;
            addChar();
            lexLen=0;
            break;

        case 40://Estado final Vezes
            instalaLexeme(retornaNomeToken(tk_vezes), tk_vezes);
            state = 0;
            addChar();
            lexLen=0;
            break;

        case 41://Estado final Virgula
            instalaLexeme(retornaNomeToken(tk_virg), tk_virg);
            state = 0;
            addChar();
            lexLen=0;
            break;

        case 42://Estado final Abre Parentesis
            instalaLexeme(retornaNomeToken(tk_abre_par), tk_abre_par);
            state = 0;
            addChar();
            lexLen=0;
            break;

        case 43://Estado final Fecha Parentesis
            instalaLexeme(retornaNomeToken(tk_fecha_par), tk_fecha_par);
            state = 0;
            addChar();
            lexLen=0;
            break;

        case 44://Caracter invalido
            state = 0;
            registraErroLex(linha, coluna, tErroLex_caractereInvalido);
            lexLen = 0;
            break;
        }
    }
}

