#if ! defined( ARVORE_ )
#define ARVORE_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: M�dulo �rvore
*
*  Arquivo gerado:              ARVORE.H
*  Letras identificadoras:      ARV
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: T1 INF1301 2017.1
*  Autores: mv Maur�cio Vieira
*           sb Samuel Bastos
*
*  $ED Descri��o do m�dulo
*     Este m�dulo implementa um conjunto simples de fun��es para criar e
*     explorar �rvores bin�rias.
*     A �rvore possui uma cabe�a que cont�m uma refer�ncia para a ra�z da
*     �rvore e outra para um n� corrente da �rvore.
*     A cada momento o m�dulo admite no m�ximo uma �nica �rvore.
*     Ao iniciar a execu��o do programa n�o existe �rvore.
*     A �rvore poder� estar vazia. Neste caso a raiz e o n� corrente
*     ser�o nulos, embora a cabe�a esteja definida.
*     O n� corrente ser� nulo se e somente se a �rvore estiver vazia.
*
***************************************************************************/
 
#if defined( ARVORE_OWN )
   #define ARVORE_EXT
#else
   #define ARVORE_EXT extern
#endif


/***********************************************************************
*
*  $TC Tipo de dados: ARV Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         ARV_CondRetOK = 0 ,
               /* Executou correto */

         ARV_CondRetNaoCriouRaiz = 1 ,
               /* N�o criou n� raiz */

         ARV_CondRetErroEstrutura = 2 ,
               /* Estrutura da �rvore est� errada */

         ARV_CondRetNaoEhFolha = 3 ,
               /* N�o � folha relativa � dire��o de inser��o desejada */

         ARV_CondRetArvoreNaoExiste = 4 ,
               /* �rvore n�o existe */

         ARV_CondRetArvoreVazia = 5 ,
               /* �rvore est� vazia */

         ARV_CondRetNohEhRaiz = 6 ,
               /* N� corrente � raiz */

         ARV_CondRetNaoPossuiFilho = 7 ,
               /* N� corrente n�o possui filho na dire��o desejada */

         ARV_CondRetFaltouMemoria = 8,
               /* Faltou mem�ria ao alocar dados */

		ARV_CondRetAcessoInvalidoVetor = 9,
			/* Acesso invalido ao vetor de arvores */

		ARV_CondRetArvoreNaoCosturada = 10
			/* Acesso invalido ao vetor de arvores */

   } ARV_tpCondRet ;

/***********************************************************************
*
*  $FC Fun��o: ARV Criar �rvore
*
*  $ED Descri��o da fun��o
*     Cria uma nova �rvore vazia.
*     Caso j� exista uma �rvore, esta ser� destru�da.
*
*  $EP Par�metros
*     $P ptArvore - ponteiro passado por refer�ncia para apontar para a 
*				    �rvore criada
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetFaltouMemoria
*
***********************************************************************/

   ARV_tpCondRet ARV_CriarArvore( void ** ptArvore ) ;


/***********************************************************************
*
*  $FC Fun��o: ARV Destruir �rvore
*
*  $EP Par�metros
*     $P ptArvore - ponteiro passado por refer�ncia que aponta para a 
*                   �rvore que ser� destruida
*
*  $ED Descri��o da fun��o
*     Destr�i o corpo e a cabe�a da �rvore, anulando a �rvore corrente.
*     Faz nada caso a �rvore corrente n�o exista.
*
***********************************************************************/

   void ARV_DestruirArvore( void ** ptArvore ) ;


/***********************************************************************
*
*  $FC Fun��o: ARV Adicionar filho � esquerda
*
*  $EP Par�metros
*     $P ptArvore - ponteiro passado por refer�ncia que aponta para a 
*				    �rvore onde o filho ser� adicionado
*     $P ValorParm - valor a ser inserido no novo n�.
*     $P ValorListaA - primeiro valor da lista do n�.
*     $P ValorListaB - segundo valor da lista do n�.
*     $P ValorListaC - terceiro valor da lista do n�.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetErroEstrutura
*     ARV_CondRetFaltouMemoria
*     ARV_CondRetNaoEhFolha     - caso n�o seja folha para a esquerda
*
***********************************************************************/

   ARV_tpCondRet ARV_InserirEsquerda( void ** ptArvore, char ValorParm, int ValorListaA, int ValorListaB, int ValorListaC ) ;


/***********************************************************************
*
*  $FC Fun��o: ARV Adicionar filho � direita
*
*  $EP Par�metros
*     $P ptArvore - ponteiro passado por refer�ncia que aponta para a 
*				    �rvore onde o filho ser� adicionado
*     $P ValorParm - valor a ser inserido no novo n�
*     $P ValorListaA - primeiro valor da lista do n�.
*     $P ValorListaB - segundo valor da lista do n�.
*     $P ValorListaC - terceiro valor da lista do n�.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetErroEstrutura
*     ARV_CondRetFaltouMemoria
*     ARV_CondRetNaoEhFolha     - caso n�o seja folha para a direita
*
***********************************************************************/

   ARV_tpCondRet ARV_InserirDireita( void ** ptArvore, char ValorParm, int ValorListaA, int ValorListaB, int ValorListaC ) ;


/***********************************************************************
*
*  $FC Fun��o: ARV Ir para n� pai
*
*  $EP Par�metros
*     $P pArvore - ponteiro para a estrutura �rvore
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetArvoreVazia
*     ARV_CondRetNoEhRaiz
*
***********************************************************************/

   ARV_tpCondRet ARV_IrPai( void * pArvore ) ;


/***********************************************************************
*
*  $FC Fun��o: ARV Ir para n� � esquerda
*
*  $EP Par�metros
*     $P pArvore - ponteiro para a estrutura �rvore
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetArvoreVazia
*     ARV_CondRetNaoPossuiFilho   - n� corrente n�o possui filho � esquerda
*
***********************************************************************/

   ARV_tpCondRet ARV_IrNoEsquerda( void * pArvore ) ;


/***********************************************************************
*
*  $FC Fun��o: ARV Ir para n� � direita
*
*  $EP Par�metros
*     $P pArvore - ponteiro para a estrutura �rvore
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetArvoreVazia
*     ARV_CondRetNaoPossuiFilho   - n� corrente n�o possui filho � direita
*
***********************************************************************/

   ARV_tpCondRet ARV_IrNoDireita( void * pArvore ) ;


/***********************************************************************
*
*  $FC Fun��o: ARV Obter valor corrente
*
*  $EP Par�metros
*     $P pArvore - ponteiro para a estrutura �rvore
*     $P ValorParm - � o par�metro que receber� o valor contido no n�.
*                    Este par�metro � passado por refer�ncia.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetArvoreVazia
*
***********************************************************************/

   ARV_tpCondRet ARV_ObterValorCorr( void * pArvore, char * ValorParm ) ;

/***********************************************************************
*
*  $FC Fun��o: ARV Costura os n�s folha da �rvore ordenados por sua Chave
*
*  $EP Par�metros
*     $P pArvore - ponteiro para a estrutura �rvore
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetArvoreVazia
*
***********************************************************************/

   ARV_tpCondRet ARV_Costura( void * pArvore) ;

/***********************************************************************
*
*  $FC Fun��o: ARV Imprime os n�s da costura na ordem em que foram costurados
*
*  $EP Par�metros
*     $P pArvore - ponteiro para a estrutura �rvore
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetArvoreVazia
*	  ARV_CondRetArvoreNaoCosturada
*
***********************************************************************/

   ARV_tpCondRet ARV_ImprimeCostura( void * pArvore) ;

#undef ARVORE_EXT

/********** Fim do m�dulo de defini��o: M�dulo �rvore **********/

#else
#endif
