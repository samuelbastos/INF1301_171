#if ! defined( TAREFA_ )
#define TAREFA_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: M�dulo tarefa
*
*  Arquivo gerado:              TAREFA.H
*  Letras identificadoras:      TRF
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: T2 INF1301 2017.1
*  Autores: mv Maur�cio Vieira
*           sb Samuel Bastos
*
*  $ED Descri��o do m�dulo
*     Este m�dulo implementa um conjunto simples de fun��es para criar e
*     explorar tarefas.
*     A cada momento o m�dulo admite no m�ximo duas tarefas (no caso de conectar
*     tarefas).
*     Tarefas possuem um listas de suas sucessoras e predecessoras
*     Ao iniciar a execu��o do programa n�o existe tarefa.
*
***************************************************************************/
 
#if defined( TAREFA_OWN )
   #define TAREFA_EXT
#else
   #define TAREFA_EXT extern
#endif


/***********************************************************************
*
*  $TC Tipo de dados: TRF Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

       TRF_CondRetOK = 0,
            /* Executou correto */

       TRF_CondRetFaltouMemoria = 1,
            /* Faltou mem�ria ao alocar os dados */

       TRF_CondRetAcessoInvalidoVetor = 2,
            /* Acesso invalido ao vetor de tarefas */

       TRF_CondRetConexaoJaExistente = 3,
            /* Tarefas j� conectadas */

       TRF_CondRetConexaoInvalida = 4,
            /* Conex�o inv�lida de tarefas  */

       TRF_CondRetTarefaInexistente = 5
            /* Tarefas n�o alocada */

   } TRF_tpCondRet ;

/***********************************************************************
*
*  $FC Fun��o: TRF Criar tarefa
*
*  $ED Descri��o da fun��o
*     Cria uma nova tarefa preenchida com nome e descri��o.
*     Caso j� exista uma tarefa, esta ser� destru�da.
*
*  $EP Par�metros
*     $P ptTarefa      - ponteiro passado por refer�ncia para apontar para a 
*				         tarefa criada
*     $P novoNome      - nome da tarefa a ser criada 
*     $P novaDescricao - descricao da tarefa a ser criada
*
*  $FV Valor retornado
*     TRF_CondRetOK
*     TRF_CondRetFaltouMemoria
*
***********************************************************************/

   TRF_tpCondRet TRF_CriarTarefa( void ** ptTarefa, char * novoNome, char * novaDescricao ) ;

/***********************************************************************
*
*  $FC Fun��o: TRF Destruir tarefa
*
*  $EP Par�metros
*     $P ptTarefa - ponteiro passado por refer�ncia que aponta para a 
*                   tarefa que ser� destruida
*
*  $ED Descri��o da fun��o
*    Destroi a tarefa passada por por refer�ncia. 
*
***********************************************************************/

   void TRF_DestruirTarefa( void ** ptTarefa ) ;

/***********************************************************************
*
*  $FC Fun��o: TRF Conectar tarefas
*
*  $EP Par�metros
*     $P ptTarefaSucessora    - ponteiro passado por refer�ncia que aponta para a 
*				                tarefa que ser� conectada como sucessora
*     $P ptTarefaPredecessora - ponteiro passado por refer�ncia que aponta para a 
*				                tarefa que ser� conectada como predecessora
* 
*  $FV Valor retornado
*     TRF_CondRetOK
*     TRF_CondRetConexaoJaExistente
*     TRF_CondRetConexaoInvalida
*
***********************************************************************/

   TRF_tpCondRet TRF_ConectarTarefas( void ** ptTarefaSucessora, void ** ptTarefaPredecessora ) ;

/***********************************************************************
*
*  $FC Fun��o: TRF Alterar tarefa
*
*  $EP Par�metros
*     $P pTarefa        - ponteiro passado por refer�ncia que aponta 
*                         a tarefa a ser alterada
*     $P novoNome       - novo nome da tarefa 
*     $P novaDescricao  - nova descricao da tarefa
*
*  $FV Valor retornado
*     TRF_CondRetOK
*     TRF_CondRetTarefaInexistente;
*
***********************************************************************/

   TRF_tpCondRet  TRF_AlterarTarefa( void ** ptTarefa, char * novoNome, char * novaDescricao  ) ;

/***********************************************************************
*
*  $FC Fun��o: TRF Consultar nome da tarefa
*
*  $EP Par�metros
*     $P pTarefa              - ponteiro passado por refer�ncia que aponta 
*                               a tarefa a ser alterada
*     $P nomeConsultado       - nome da tarefa passado por referencia
*
*  $FV Valor retornado
*     TRF_CondRetOK
*     TRF_CondRetTarefaInexistente;
*
***********************************************************************/

   TRF_tpCondRet  TRF_ConsultarNomeTarefa( void ** ptTarefa, char ** nomeConsultado ) ;

/***********************************************************************
*
*  $FC Fun��o: TRF Consultar descricao da tarefa
*
*  $EP Par�metros
*     $P pTarefa              - ponteiro passado por refer�ncia que aponta 
*                               a tarefa a ser alterada
*     $P nomeConsultado       - descricao da tarefa passada por referencia
*
*  $FV Valor retornado
*     TRF_CondRetOK
*     TRF_CondRetTarefaInexistente;
*
***********************************************************************/

   TRF_tpCondRet  TRF_ConsultarDescricaoTarefa( void ** ptTarefa, char ** descricaoConsultada ) ;

#undef TAREFA_EXT

/********** Fim do m�dulo de defini��o: M�dulo tarefa **********/

#else
#endif