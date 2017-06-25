/*
*---------------------------------------------------------------------
*
*   File    : erros.h
*   Created : 2017-05-09
*   Modified: 2017-05-31
*
*   Lista de erros de Portugol
*
*---------------------------------------------------------------------
*/

#ifndef _ERROS_H_   /* Make sure this file is not included twice */
#define _ERROS_H_

/*
*---------------------------------------------------------------------
*   INCLUDE FILES
*---------------------------------------------------------------------
*/

#define ARRAY_ERROS_TAM_INICIAL    3    /* Esse precisa ser um inteiro */
#define ARRAY_ERROS_FATOR_REALLOC  2.0  /* ... mas esse não            */
/*
*---------------------------------------------------------------------
*   Constants and macros
*---------------------------------------------------------------------
*/

/*
*---------------------------------------------------------------------
*   Data structures and variables
*---------------------------------------------------------------------
*/

typedef enum {
  tErroLex_pontoIsolado,
  tErroLex_cadeiaNaoFechada,
  tErroLex_comentarioNaoFechado,
  tErroLex_caractereInvalido,
  tErroLex_delimEsperado
} tErroLex;

typedef struct{
  int linha;
  int coluna;
  tErroLex erroLex;
}tErrosEncontrados;


typedef struct {
  int quantosErros;
  int indPrimErro;
}tErrosNumalinha;



FILE *arqErros;
size_t tamArrayErros = 0;
tErrosEncontrados *errosEncontrados = NULL;
int totErrosEncontrados = 0;

/*
*---------------------------------------------------------------------
*   Function prototypes
*---------------------------------------------------------------------
*/

tErrosNumalinha erroslinha (int);
void reallocaArrayErros (void);
void registraErroLex (int, int, tErroLex);
void imprimeErro (int);
void imprimeEntrada (const char *);
char* retornaTipoErro(tErroLex);

/*
*---------------------------------------------------------------------
*   Functions
*---------------------------------------------------------------------
*/

tErrosNumalinha errosNalinha (int linha) { // Recebe a linha a ser verificada
  int iErro; // Incrementador
  static int indiceProxErro = 0; // Proximo erro
  tErrosNumalinha errosNalinha = {0, 0}; // Inicializa a estrutura

  for (iErro = indiceProxErro; iErro < totErrosEncontrados; iErro++) { // Percorre encontrando erros na linha
    if (errosEncontrados[iErro].linha > linha) // Se o erro encontrado não estiver na linha
      break;
    if (errosEncontrados[iErro].linha == linha) { // Senão
      if (errosNalinha.quantosErros == 0) // Se a quantidade de erros = 0 (não teve erro ainda)
        errosNalinha.indPrimErro = iErro; // O primeiro erro é inicializado na posição atual
      errosNalinha.quantosErros++; // Quantidade de erros na linha
      indiceProxErro = iErro + 1; // Indica o proximo erro
    }
  }
  return (errosNalinha); // Retorna a estrutura que mostra o primeiro erro, e quantos erros tem na linha
}

void reallocaArrayErros (void) {
  size_t novoTam = (size_t) (tamArrayErros == 0 ? ARRAY_ERROS_TAM_INICIAL : tamArrayErros * ARRAY_ERROS_FATOR_REALLOC);

  errosEncontrados = realloc (errosEncontrados, novoTam);
  if (errosEncontrados == NULL) {
  printf ("Erro em %s::%s - realloc falhou", __FILE__, __FUNCTION__);
    exit (EXIT_FAILURE);
  }
  tamArrayErros = novoTam;
}

void registraErroLex (int lin, int col, tErroLex erro) {
  tErrosEncontrados
    *pErro;

  if (totErrosEncontrados == tamArrayErros)
    reallocaArrayErros();
  pErro = errosEncontrados + totErrosEncontrados;
  pErro->linha = lin;      /* errosEncontrados [totErrosEncontrados].linha = lin;    */
  pErro->coluna = col;     /* errosEncontrados [totErrosEncontrados].coluna = col;   */
  pErro->erroLex = erro;   /* errosEncontrados [totErrosEncontrados].erroLex = erro; */
  totErrosEncontrados++;
}

void imprimeErro (int indArrayErros) {
  int iCol; // Incrementador coluna

  fprintf (arqErros, "     "); // Imprime colunas em branco antes dos ifens (espaço onde mostra a linha)

  for (iCol = 0; iCol < errosEncontrados[indArrayErros].coluna-1; iCol++)
    fprintf (arqErros, "-"); // Imprime ifens até uma coluna antes do erro

  fprintf (arqErros, "^\n"); // Imprime uma "seta" na posição atual do erro
  fprintf (arqErros, "     "); // Mensagem de erro (espaço das colunas da linha)
  fprintf (arqErros, "Erro lexico na linha %d coluna %d: ", errosEncontrados [indArrayErros].linha, errosEncontrados[indArrayErros].coluna);
  // Descrição do erro indicando a linha, coluna

  fprintf (arqErros, "%s\n", retornaTipoErro(errosEncontrados [indArrayErros].erroLex)); // Identifica qual foi o erro cometido
}

char* retornaTipoErro(tErroLex erro){
    switch (erro){
        case 0:
        return "Ponto isolado";
        case 1:
        return "Cadeia nao fechada";
        case 2:
        return "Comentario nao fechado";
        case 3:
        return "Caracter invalido";
        case 4:
        return "Delimitador esperado";
    }
}


  
#endif /* ifndef _ERROS_H_ */
  