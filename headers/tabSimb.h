/*
*---------------------------------------------------------------------
*
*   File    : tabSimb.h
*   Created : 2017-05-09
*   Modified: 2017-05-31
*
*   Definicoes para a tabela de simbolos.
*
*---------------------------------------------------------------------
*/

#ifndef _TABSIMB_DOT_H_   /* Make sure this file is not included twice */
#define _TABSIMB_DOT_H_

/*
*---------------------------------------------------------------------
*   INCLUDE FILES
*---------------------------------------------------------------------
*/

/*
*---------------------------------------------------------------------
*   Constants and macros
*---------------------------------------------------------------------
*/

#define TAMANHO_TAB_HASH 256

/*
*---------------------------------------------------------------------
*   Type definitions
*---------------------------------------------------------------------
*/

/*
*---------------------------------------------------------------------
*   Data structures and variables
*---------------------------------------------------------------------
*/


/*typedef struct sSimbolo { // ORIGINAL
  tToken token;
  char *lexema;
}	tSimbolo;*/

typedef struct s_registroTabDeSimbolos{
  int posicaoNaTabDeSimbolos;
  tToken token;
  char* lexema;
  struct s_posicao posicaoCabeca;
  struct s_registroTabDeSimbolos *proximo;
  struct s_registroTabDeSimbolos *proximoNaListaDeColisao;
}tRegistroTabDeSimbolos;

typedef struct{
  tRegistroTabDeSimbolos *tabela[TAMANHO_TAB_HASH];
  int proximaPosicao;
  tRegistroTabDeSimbolos *cabeca;
  tRegistroTabDeSimbolos *calda;
  int maiorToken;
  int maiorLexema;
  int maiorNumDeOcorrencias;
}tTabelaDeSimbolos;

/*
*---------------------------------------------------------------------
*   Function prototypes
*---------------------------------------------------------------------
*/


void instalaTabelaDeSimbolo(tTabelaDeSimbolos *tabDeSimbolos,tToken toke);
void inicializarRegistroTabSimbolos(tRegistroTabDeSimbolos *registro, tToken token, char *lexema, int linha, int coluna);
void inicializarTabelaDeSimbolos(tTabelaDeSimbolos *tab);
void inserirNaListaDePosicoes(tPosicao *posicaoCabeca, int linha, int coluna, tTabelaDeSimbolos *tabDeSimbolos);
void inserirNaListaDeColisao(tRegistroTabDeSimbolos *registroBase, tRegistroTabDeSimbolos *novoRegistro);
int pegarProximaPosicao(tTabelaDeSimbolos *tabDeSimbolos);
void inserirNaTabelaDeSimbolos(tTabelaDeSimbolos *tabDeSimbolos, tRegistroTabDeSimbolos *novoRegistro);
char * formatarTabelaSimbolos(tTabelaDeSimbolos *tabDeSimbolos);
void gerarArquivoTabelaDeSimbolos(tTabelaDeSimbolos *tabDeSimbolos, const char *nomeDoArquivoFonte);

unsigned long djb2Hash(unsigned char *str);
unsigned long pegaValorHash(char *chave);

/*
*---------------------------------------------------------------------
*   Function definitions
*---------------------------------------------------------------------
*/
unsigned long pegaValorHash(char *chave){
  unsigned long valor = djb2Hash((unsigned char *) chave);
  return  valor % TAMANHO_TAB_HASH;
}

unsigned long djb2Hash(unsigned char *str){
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
      hash = ((hash << 5) + hash) + c; // hash * 33 + c

    return hash;
}

void inserirNaTabelaDeSimbolos(tTabelaDeSimbolos *tabDeSimbolos, tRegistroTabDeSimbolos *novoRegistro){

  unsigned long indice = pegaValorHash(novoRegistro->lexema);

  // Se tabela estiver vazia
  if(tabDeSimbolos->cabeca == NULL && tabDeSimbolos->calda == NULL){
    novoRegistro->posicaoNaTabDeSimbolos = pegarProximaPosicao(tabDeSimbolos);
    tabDeSimbolos->tabela[indice] = novoRegistro;
    vetorPosicaoTabSimbolo[icrPosicaoTabSimbolo]=novoRegistro->posicaoNaTabDeSimbolos;
    icrPosicaoTabSimbolo++;

    tabDeSimbolos->cabeca =  novoRegistro;
    tabDeSimbolos->calda =  novoRegistro;
  }
  else if( tabDeSimbolos->tabela[indice] == NULL){
    novoRegistro->posicaoNaTabDeSimbolos = pegarProximaPosicao(tabDeSimbolos);
    tabDeSimbolos->tabela[indice] = novoRegistro;

    tabDeSimbolos->calda->proximo = novoRegistro;
    tabDeSimbolos->calda = novoRegistro;
     vetorPosicaoTabSimbolo[icrPosicaoTabSimbolo]=novoRegistro->posicaoNaTabDeSimbolos;
    icrPosicaoTabSimbolo++;
  }
  else{
    if(strcmp(tabDeSimbolos->tabela[indice]->lexema, novoRegistro->lexema) == 0){
      inserirNaListaDePosicoes(&tabDeSimbolos->tabela[indice]->posicaoCabeca,
                               novoRegistro->posicaoCabeca.linha,
                               novoRegistro->posicaoCabeca.coluna, tabDeSimbolos);
      novoRegistro->posicaoNaTabDeSimbolos = tabDeSimbolos->tabela[indice]->posicaoNaTabDeSimbolos;
      vetorPosicaoTabSimbolo[icrPosicaoTabSimbolo]=novoRegistro->posicaoNaTabDeSimbolos;
      icrPosicaoTabSimbolo++;
    }
    else{
      tRegistroTabDeSimbolos *reg = tabDeSimbolos->tabela[indice]->proximoNaListaDeColisao;
      while(reg != NULL && strcmp(reg->lexema, novoRegistro->lexema)!=0){
        reg = reg->proximoNaListaDeColisao;
      }
      if(reg == NULL){
        inserirNaListaDeColisao(tabDeSimbolos->tabela[indice], novoRegistro);
        novoRegistro->posicaoNaTabDeSimbolos = pegarProximaPosicao(tabDeSimbolos);

        tabDeSimbolos->calda->proximo = novoRegistro;
        tabDeSimbolos->calda = novoRegistro;
        vetorPosicaoTabSimbolo[icrPosicaoTabSimbolo]=novoRegistro->posicaoNaTabDeSimbolos;
        icrPosicaoTabSimbolo++;
      }
      else{
        inserirNaListaDePosicoes(&reg->posicaoCabeca, novoRegistro->posicaoCabeca.linha,
                                 novoRegistro->posicaoCabeca.coluna, tabDeSimbolos);
        novoRegistro->posicaoNaTabDeSimbolos = reg->posicaoNaTabDeSimbolos;
        vetorPosicaoTabSimbolo[icrPosicaoTabSimbolo]=novoRegistro->posicaoNaTabDeSimbolos;
        icrPosicaoTabSimbolo++;
      }
    }
  }

  if( strlen( retornaNomeToken(novoRegistro->token) ) > tabDeSimbolos->maiorToken )
    tabDeSimbolos->maiorToken = strlen( retornaNomeToken(novoRegistro->token) );

  if( strlen(novoRegistro->lexema) > tabDeSimbolos->maiorLexema )
    tabDeSimbolos->maiorLexema = strlen(novoRegistro->lexema);
}
int pegarProximaPosicao(tTabelaDeSimbolos *tabDeSimbolos){
  int pos = tabDeSimbolos->proximaPosicao;
  tabDeSimbolos->proximaPosicao++;

  return pos;
}

void inserirNaListaDeColisao(tRegistroTabDeSimbolos *registroBase, tRegistroTabDeSimbolos *novoRegistro){

  novoRegistro->proximoNaListaDeColisao = NULL;

  if(registroBase->proximoNaListaDeColisao == NULL){
    registroBase->proximoNaListaDeColisao = novoRegistro;
  }
  else{
    tRegistroTabDeSimbolos *calda =  registroBase->proximoNaListaDeColisao;

    while(calda->proximoNaListaDeColisao != NULL){
      calda = calda->proximoNaListaDeColisao;
    }

    calda->proximoNaListaDeColisao = novoRegistro;
  }
}

void inserirNaListaDePosicoes(tPosicao *posicaoCabeca, int linha, int coluna,
                              tTabelaDeSimbolos *tabDeSimbolos){
  int ocorrencias = 2;

  tPosicao *pos = posicaoCabeca;

  while(pos->proximo != NULL){
    pos = pos->proximo;
    ocorrencias ++;
  }

  tPosicao *novaPosicao = (tPosicao*)malloc(sizeof(tPosicao));
  novaPosicao->linha = linha;
  novaPosicao->coluna = coluna;
  novaPosicao->proximo = NULL;

  pos->proximo = novaPosicao;

  if( ocorrencias > tabDeSimbolos->maiorNumDeOcorrencias ){
    tabDeSimbolos->maiorNumDeOcorrencias = ocorrencias;
  }
}

void inicializarTabelaDeSimbolos(tTabelaDeSimbolos *tab){

  tab->proximaPosicao=1;

  tab->cabeca = NULL;
  tab->calda = NULL;

  int i;
  for(i=0; i<TAMANHO_TAB_HASH; i++){
    tab->tabela[i] = NULL;
  }

  tab->maiorToken = 5;
  tab->maiorLexema = 6;
  tab->maiorNumDeOcorrencias = 1;
}

void inicializarRegistroTabSimbolos(tRegistroTabDeSimbolos *registro, tToken token,
                                    char *lexema, int linha, int coluna){

  tPosicao pos = {linha, coluna, NULL};
  char *lex = (char *) malloc(sizeof(char) * (strlen(lexema)+1) );
  strcpy(lex, lexema);
  tRegistroTabDeSimbolos reg = {-1, token, lex, pos, NULL, NULL};
  *registro = reg;
}

void gerarArquivoTabelaDeSimbolos(tTabelaDeSimbolos *tabDeSimbolos, const char *nomeDoArquivoFonte){

  char *titulo = (char *) malloc(24 + strlen(nomeDoArquivoFonte)); // Alocação título
  sprintf(titulo, "Tabela de Simbolos - \"%s\"\n\n", nomeDoArquivoFonte); // Titulo recebe o nome do arquivo

  char *nomeDoArquivo = (char *) malloc(5 + strlen(nomeDoArquivoFonte)); // Alocação variavel
  sprintf(nomeDoArquivo,"%s.tbl", nomeDoArquivoFonte); // Variavel recebe o nome do arquivo

  escreveParaArquivo(nomeDoArquivo, titulo); 
  concatenaEmArquivo(nomeDoArquivo, formatarTabelaSimbolos(tabDeSimbolos));

  free(titulo);
  free(nomeDoArquivo);

}

char * formatarTabelaSimbolos(tTabelaDeSimbolos *tabDeSimbolos){

  int espacoOcorrencias = 9*(tabDeSimbolos->maiorNumDeOcorrencias)
                          +tabDeSimbolos->maiorNumDeOcorrencias < 30 ?
                          30 : 9*(tabDeSimbolos->maiorNumDeOcorrencias)+
                          tabDeSimbolos->maiorNumDeOcorrencias;

  int qtdlinhas = (tabDeSimbolos->proximaPosicao) + 3 ;
  int qtdColunas = 16 + tabDeSimbolos->maiorToken + tabDeSimbolos->maiorLexema + espacoOcorrencias;

  int divisoes[5] = {0, 6, 9 + tabDeSimbolos->maiorToken, 12 + tabDeSimbolos->maiorToken
                    + tabDeSimbolos->maiorLexema , qtdColunas-2};

  int indiceDaProximaDivisao=0;

  char * tabelaFormatada = (char *) malloc(sizeof(char) * ( ( qtdlinhas * qtdColunas ) + 1 ) );

  int i,j;
  for (i = 0; i < qtdlinhas; i++)
  {
    indiceDaProximaDivisao=0;

    for (j = 0; j < qtdColunas; j++)
    {
      if(j==qtdColunas-1){
        tabelaFormatada[i*qtdColunas + j] = '\n';
      }
      else{
        if( i==0 || i==2 || i==qtdlinhas-1 ){

          if(j==divisoes[indiceDaProximaDivisao]){
            indiceDaProximaDivisao++;
            tabelaFormatada[i*qtdColunas + j] = '+';
          }
          else{
            tabelaFormatada[i*qtdColunas + j] = '-';
          }

        }
        else{
          if(j==divisoes[indiceDaProximaDivisao]){
            indiceDaProximaDivisao++;
            tabelaFormatada[i*qtdColunas + j] = '|';
          }
          else{
            tabelaFormatada[i*qtdColunas + j] = ' ';
          }
        }
      }
    }
  }

  tabelaFormatada[( qtdlinhas * qtdColunas )] = '\0';

  memcpy(&tabelaFormatada[ qtdColunas + 2 ], "POS", 3);
  memcpy(&tabelaFormatada[ qtdColunas + divisoes[1] +2 ], "TOKEN", 5);
  memcpy(&tabelaFormatada[ qtdColunas + divisoes[2] +2 ], "LEXEMA", 6);
  memcpy(&tabelaFormatada[ qtdColunas + divisoes[3] +2 ], "POS NA ENTRADA (linha,coluna)", 29);

  char strPosicaoTab [4];
  char *nomeTok;
  char ocorrencia[12];
  char *strOcorrencias = (char*) malloc (sizeof(char)*
                         (9*(tabDeSimbolos->maiorNumDeOcorrencias)
                         +tabDeSimbolos->maiorNumDeOcorrencias+1) );

  tRegistroTabDeSimbolos *reg = tabDeSimbolos->cabeca;
  while(reg != NULL){

    sprintf(strPosicaoTab, "%3d", reg->posicaoNaTabDeSimbolos);
    nomeTok = retornaNomeToken(reg->token);

    memcpy(&tabelaFormatada[ qtdColunas*(reg->posicaoNaTabDeSimbolos+2) + 2 ], strPosicaoTab,
         strlen(strPosicaoTab));
    memcpy(&tabelaFormatada[ qtdColunas*(reg->posicaoNaTabDeSimbolos+2) + divisoes[1] + 2 ],
           nomeTok, strlen(nomeTok));
    memcpy(&tabelaFormatada[ qtdColunas*(reg->posicaoNaTabDeSimbolos+2) + divisoes[2] + 2 ],
           reg->lexema, strlen(reg->lexema));

    tPosicao *pos = &reg->posicaoCabeca;
    sprintf(strOcorrencias, "(%3d,%3d) ", pos->linha, pos->coluna);

    while(pos->proximo!=NULL){
      pos = pos->proximo;
      sprintf(ocorrencia, "(%3d,%3d) ", pos->linha, pos->coluna);
      strcat(strOcorrencias, ocorrencia);

    }

    memcpy(&tabelaFormatada[ qtdColunas*(reg->posicaoNaTabDeSimbolos+2) + divisoes[3] + 2 ],
         strOcorrencias, strlen(strOcorrencias));

    reg = reg->proximo;
  }

  free(strOcorrencias);
  return tabelaFormatada;

}

void escreveParaArquivo(char *nomeDoArquivo, char *conteudo){ // Recebe o arquivo, recebe o conteudo
  FILE *f = fopen(nomeDoArquivo, "w");
  if (f == NULL)
  {
    printf("Erro na abertura do arquivo!\n");
    return;
  }

  fprintf(f, "%s", conteudo); // Escreve o conteudo
  fclose(f);

} 

void concatenaEmArquivo(char *nomeDoArquivo, char *conteudo){
  FILE *f = fopen(nomeDoArquivo, "a");
  if (f == NULL)
  {
    printf("Erro na abertura do arquivo!\n");
    return;
  }

  fprintf(f, "%s", conteudo);
  fclose(f);

}

void instalaTabelaDeSimbolo(tTabelaDeSimbolos *tabDeSimbolos,tToken toke){

   if(toke == tk_IDEN || toke == tk_CADEIA || toke == tk_INT || toke == tk_DEC){
    tRegistroTabDeSimbolos *novoReg = (tRegistroTabDeSimbolos *)malloc(sizeof(tRegistroTabDeSimbolos));
    inicializarRegistroTabSimbolos(novoReg, toke, lexeme,linha, coluna-lexLen+1);
    inserirNaTabelaDeSimbolos(tabDeSimbolos, novoReg);
    }
}



#endif /* ifndef _TABSIMB_DOT_H_ */
