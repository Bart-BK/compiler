/*
*---------------------------------------------------------------------
*
*   File    : tokens.h
*   Created : 2017-05-09
*   Modified: 2017-05-31
*
*   Lista de tokens de Portugol
*
*---------------------------------------------------------------------
*/

#ifndef _TOKENS_DOT_H_   /* Make sure this file is not included twice */
#define _TOKENS_DOT_H_

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
#define QTD_DE_TOKENS 42
#define TAM_TAB_RESUMO 42
/*
*---------------------------------------------------------------------
*   Type definitions
*---------------------------------------------------------------------
*/

typedef enum  {
  tk_EOF,
  tk_IDEN,
  tk_INT,
  tk_DEC,
  tk_CADEIA,
  tk_programa,
  tk_fim_programa,
  tk_inteiro,
  tk_decimal,
  tk_entrada,
  tk_saida,
  tk_para,
  tk_de,
  tk_ate,
  tk_passo,
  tk_fim_para,
  tk_caso,
  tk_entao,
  tk_se,
  tk_senao,
  tk_fim_caso,
  tk_e,
  tk_ou,
  tk_nao,
  tk_virg,
  tk_pt_virg,
  tk_dois_pts,
  tk_abre_par,
  tk_fecha_par,
  tk_menor,
  tk_menor_igual,
  tk_maior,
  tk_maior_igual,
  tk_diferente,
  tk_igual,
  tk_incr,
  tk_decr,
  tk_atrib,
  tk_mais,
  tk_menos,
  tk_vezes,
  tk_dividido
} tToken;


typedef struct node {
    char *lexeme1;
    char *token;
    int linha;
    int coluna;
    tToken codToken;
    int posicaotabSimbolo;
    struct node * next;
} tNode;

tNode * head = NULL;

typedef struct s_posicao{
  int linha;
  int coluna;
  struct s_posicao *proximo;
}tPosicao;


int state = 0;
char lexeme [100];
char * lex1;
int lexLen=0;
int token;
int verdade=1;
char c;
int linha=1, coluna=0;
int maiorToken=0;
int totLexeme=0;
int contLexema=0;
int tabResumo[TAM_TAB_RESUMO];
int totLexema=0;

int vetorPosicaoTabSimbolo[100];
int icrPosicaoTabSimbolo=0;
int decPosicaoTabSimbolo=0;


/*
*---------------------------------------------------------------------
*   Function prototypes
*---------------------------------------------------------------------
*/

void addChar();
char * retornaNomeToken(tToken);
tToken retornaNomeTokenReservado(char[] );
void insereListaToken(tNode * head, char *token,tToken codToken);
void gerarArquivoTabelaDeTokens(tNode *tabDeTokens, const char *nomeDoArquivoFonte, int maiorLexema);
char * formatarTabelaTokens(tNode *tabDeTokens);
char * formatarTabelaResumo();
void inicializaTabelaToken();
void instalaLexeme(char *tk_token, tToken codToken);
void escreveParaArquivo(char *nomeDoArquivo, char *conteudo);
void concatenaEmArquivo(char *nomeDoArquivo, char *conteudo);

/*
*---------------------------------------------------------------------
*   Function definitions
*---------------------------------------------------------------------
*/


char * retornaNomeToken(tToken token){ // Auto explicativo

  switch(token){
    case tk_EOF:
      return "tk_EOF";
    case tk_IDEN:
      return "tk_IDEN";
    case tk_INT:
      return "tk_INT";
    case tk_DEC:
      return "tk_DEC";
    case tk_CADEIA:
      return "tk_CADEIA";
    case tk_programa:
      return "tk_programa";
    case tk_fim_programa:
      return "tk_fim_programa";
    case tk_inteiro:
      return "tk_inteiro";
    case tk_decimal:
      return "tk_decimal";
    case tk_entrada:
      return "tk_entrada";
    case tk_saida:
      return "tk_saida";
    case tk_para:
      return "tk_para";
    case tk_de:
      return "tk_de";
    case tk_ate:
      return "tk_ate";
    case tk_passo:
      return "tk_passo";
    case tk_fim_para:
      return "tk_fim_para";
    case tk_caso:
      return "tk_caso";
    case tk_entao:
      return "tk_entao";
    case tk_se:
      return "tk_se";
    case tk_senao:
      return "tk_senao";
    case tk_fim_caso:
      return "tk_fim_caso";
    case tk_e:
      return "tk_e";
    case tk_ou:
      return "tk_ou";
    case tk_nao:
      return "tk_nao";
    case tk_virg:
      return "tk_virg";
    case tk_pt_virg:
      return "tk_pt_virg";
    case tk_dois_pts:
      return "tk_dois_pts";
    case tk_abre_par:
      return "tk_abre_par";
    case tk_fecha_par:
      return "tk_fecha_par";
    case tk_menor:
      return "tk_menor";
    case tk_menor_igual:
      return "tk_menor_igual";
    case tk_maior:
      return "tk_maior";
    case tk_maior_igual:
      return "tk_maior_igual";
    case tk_diferente:
      return "tk_diferente";
    case tk_igual:
      return "tk_igual";
    case tk_incr:
      return "tk_incr";
    case tk_decr:
      return "tk_decr";
    case tk_atrib:
      return "tk_atrib";
    case tk_mais:
      return "tk_mais";
    case tk_menos:
      return "tk_menos";
    case tk_vezes:
      return "tk_vezes";
    case tk_dividido:
      return "tk_dividido";
  }
}

tToken retornaNomeTokenReservado(char lexema[]){

    int i; // Incrementador
    char* aux = (char *)malloc(sizeof(char)*strlen(lexema)+1); // +1 /0
    strcpy(aux,lexema);

    for(i = 0; i < strlen(aux); i++){
      aux[i] = tolower(aux[i]); // Tornas todas as letras minusculas
    }

    if(strcmp(aux, "int")==0)
      return tk_INT;
    else if(strcmp(aux, "dec")==0)
      return tk_DEC;
    else if(strcmp(aux, "e")==0)
      return tk_e;
    else if(strcmp(aux, "se")==0)
      return tk_se;
    else if(strcmp(aux, "para")==0)
      return tk_para;
    else if(strcmp(aux, "de")==0)
      return tk_de;
    else if(strcmp(aux, "fim_para")==0)
      return tk_fim_para;
    else if(strcmp(aux, "passo")==0)
      return tk_passo;
    else if(strcmp(aux, "ate")==0)
      return tk_ate;
    else if(strcmp(aux, "senao")==0)
      return tk_senao;
    else if(strcmp(aux, "caso")==0)
      return tk_caso;
    else if(strcmp(aux, "fim_caso")==0)
      return tk_fim_caso;
    else if(strcmp(aux, "entao")==0)
      return tk_entao;
    else if(strcmp(aux, "ou")==0)
      return tk_ou;
    else
      return tk_IDEN;
}


char * formatarTabelaTokens(tNode *tabDeTokens){

  int qtdlinhas = (contLexema) + 4 ;
  int qtdColunas = 41 + maiorToken + totLexeme ;

  int divisoes[7] = {0, 6, 12, 18, 21 +maiorToken, 24 +maiorToken + totLexeme, qtdColunas-2};

  int indiceDaProximaDivisao=0;

  char * tabelaFormatada = (char *) malloc(sizeof(char) * ( ( qtdlinhas * qtdColunas ) + 1 ) );

  int i,j;
  for (i = 0; i < qtdlinhas; i++) {
    indiceDaProximaDivisao=0;

    for (j = 0; j < qtdColunas; j++) {
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

  memcpy(&tabelaFormatada[ qtdColunas + 2 ], "LIN", 3);
  memcpy(&tabelaFormatada[ qtdColunas + divisoes[1] + 2 ], "COL", 3);
  memcpy(&tabelaFormatada[ qtdColunas + divisoes[2] + 2 ], "COD", 3);
  memcpy(&tabelaFormatada[ qtdColunas + divisoes[3] + 2 ], "TOKEN", 5);
  memcpy(&tabelaFormatada[ qtdColunas + divisoes[4] + 2 ], "LEXEMA", 6);
  memcpy(&tabelaFormatada[ qtdColunas + divisoes[5] + 2 ], "POS TAB SIMB", 12);

  int ultimalinha=0;
  i=3;

  char strlinha [4];
  char strColuna [4];
  char strCod [4];
  char strPosicao [4];
  char *nomeTok;
  char strPosicaoTab [4];

  tNode * current = head;

  //registroTabDeTokens *reg = tabDeTokens->cabeca;
  current = current->next;
  while(current != NULL){

    sprintf(strlinha, "%3d", (int)current->linha);
    sprintf(strColuna, "%3d", (int)current->coluna);
    sprintf(strCod, "%3d", (int)current->codToken);//codigo na tabela de toekns falta fazer
    //codigo na tabela de toekns falta fazer

    nomeTok = current->token;

    if(current->linha != ultimalinha){
      memcpy(&tabelaFormatada[ qtdColunas * i + 2 ], strlinha, strlen(strlinha));
      ultimalinha=current->linha;
    }
    memcpy(&tabelaFormatada[ qtdColunas * i + divisoes[1] + 2 ], strColuna, strlen(strColuna));
    memcpy(&tabelaFormatada[ qtdColunas * i + divisoes[2] + 2 ], strCod, strlen(strCod));
    memcpy(&tabelaFormatada[ qtdColunas * i + divisoes[3] + 2 ], nomeTok, strlen(nomeTok));




    if(strcmp(current->lexeme1,"")!=0 ){
      memcpy(&tabelaFormatada[ qtdColunas * i + divisoes[4] + 2 ], current->lexeme1,
             strlen(current->lexeme1));
        sprintf(strPosicao, "%3d", (int)current->posicaotabSimbolo);
        memcpy(&tabelaFormatada[ qtdColunas * i + divisoes[5] + 7 ], strPosicao,
        strlen(strPosicao));

    }
    i++;
    current = current->next;
  }

  return tabelaFormatada;
}

void gerarArquivoTabelaDeTokens(tNode *tabDeTokens, const char *nomeDoArquivoFonte, int maiorLexema){

  char *titulo = (char *) malloc(35 + strlen(nomeDoArquivoFonte));
  sprintf(titulo, "Lista de tokens reconhecidos \"%s\"\n\n", nomeDoArquivoFonte);

  char *nomeDoArquivo = (char *) malloc(5 + strlen(nomeDoArquivoFonte));
  sprintf(nomeDoArquivo,"%s.tok", nomeDoArquivoFonte);

  char *totalDeErros =  (char *) malloc(64);

  escreveParaArquivo(nomeDoArquivo, titulo);
  concatenaEmArquivo(nomeDoArquivo, formatarTabelaTokens(tabDeTokens));
  concatenaEmArquivo(nomeDoArquivo, "\nRESUMO\n\n");
  concatenaEmArquivo(nomeDoArquivo, formatarTabelaResumo());


  free(titulo);
  free(nomeDoArquivo);
  free(totalDeErros);
}


/*****************************************************************************************************************************
* addChar
/*****************************************************************************************************************************/
void addChar()
{
    if (lexLen <= 98)
    {
        lexeme[lexLen++] = c;
        lexeme[lexLen] = 0;
    }

}


void inicializaTabelaToken(){
    head = malloc(sizeof(tNode));
        if (head == NULL) {
            return;
        }
            head->lexeme1 = NULL;
            head->token = NULL;
            head->linha = 0;
            head->coluna = 0;
            head->posicaotabSimbolo=-1;
}

void instalaLexeme(char *tk_token, tToken codToken){

   lex1 = (char *) malloc((strlen(lexeme)+1) );
    strcpy(lex1, lexeme);
    contLexema++;
   if(maiorToken < strlen(tk_token))
        maiorToken = strlen(tk_token);
   if(totLexeme < strlen(lex1))
        totLexeme = strlen(lex1);
   tabResumo[codToken]++;
   totLexema++;
   insereListaToken(head, tk_token, codToken);
}

void insereListaToken(tNode * head, char *token,  tToken codToken) {
    tNode * current = head;

    while (current->next != NULL) {
        current = current->next;
    }
    current->next = malloc(sizeof(tNode));
    current->next->token = token;
    current->next->linha = linha;
    current->next->coluna = coluna-lexLen+1;
    current->next->codToken = codToken;

    if(strcmp(token,"tk_IDEN")==0 || strcmp(token,"tk_DEC")==0 || strcmp(token,"tk_CADEIA")==0 || strcmp(token,"tk_INT")==0){
        current->next->lexeme1 = lex1;
        current->next->posicaotabSimbolo = vetorPosicaoTabSimbolo[decPosicaoTabSimbolo];
        decPosicaoTabSimbolo++;
    }else{
        current->next->lexeme1 = "";
        current->next->posicaotabSimbolo = 0;
    }
    current->next->next = NULL;
}


char * formatarTabelaResumo(){

  int qtdlinhas = QTD_DE_TOKENS + 5 ;
  int qtdColunas = 33;

  int divisoes[4] = {0, 6, 24, qtdColunas-2};

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
        if( i==0 || i==2 || i==qtdlinhas-3 || i==qtdlinhas-1 ){

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

  memcpy(&tabelaFormatada[ qtdColunas + 2 ], "COD", 3);
  memcpy(&tabelaFormatada[ qtdColunas + divisoes[1] + 2 ], "TOKEN", 5);
  memcpy(&tabelaFormatada[ qtdColunas + divisoes[2] + 2 ], "USOS", 4);
  memcpy(&tabelaFormatada[ qtdColunas*45 + 4 ], "0", 1);
  memcpy(&tabelaFormatada[ qtdColunas*45 + 8 ], "TOTAL", 5);

  char strCod [4];
  char *nomeTok;
  char strUsos [4];
  char strTotal [5];

   for( i=1; i<TAM_TAB_RESUMO; i++){
    sprintf(strUsos, "%3d", (int)tabResumo[i]);
    sprintf(strCod, "%3d", i);
    nomeTok = retornaNomeToken(i);

    memcpy(&tabelaFormatada[ qtdColunas * (i+2) + 2 ], strCod, strlen(strCod));
    memcpy(&tabelaFormatada[ qtdColunas * (i+2) + divisoes[1] + 2 ], nomeTok, strlen(nomeTok));
    memcpy(&tabelaFormatada[ qtdColunas * (i+2) + divisoes[2] + 3 ], strUsos, strlen(strUsos));
  }

  sprintf(strTotal, "%4d", (int)totLexema);
  memcpy(&tabelaFormatada[ qtdColunas * 45 + divisoes[2] + 2 ], strTotal, strlen(strTotal));
  return tabelaFormatada;
}

#endif /* ifndef _TOKENS_DOT_H_ */


