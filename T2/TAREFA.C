/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo tarefa
*
*  Arquivo gerado:              TAREFA.C
*  Letras identificadoras:      TRF
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: T2 INF1301 2017.1
*  Autores: mv Maur�cio Vieira
*           sb Samuel Bastos
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>
#include   <string.h>

#define TAREFA_OWN
#include "TAREFA.H"
#include "LISTA.H"
#undef TAREFA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: TRF Descritor da estrutura de uma tarefa
*
*
*  $ED Descri��o do tipo
*     Descreve a estrutura de uma tarefa
*
***********************************************************************/

   typedef struct tgTarefa {

       char * nome;

       char * descricao;

       int idRecurso;
                
       LIS_tppLista tarefasPredecessoras ;
        
       LIS_tppLista tarefasSucessoras;

   } tpTarefa ;

/***********************************************************************
*
*  $TC Tipo de dados: TRF Descritor da cabe�a de uma tarefa
*
*
*  $ED Descri��o do tipo
*     A cabe�a da tarefa � o ponto de acesso para uma determinada tarefa.
*     Nela � guardada o ponteiro da tarefa em si e sua id.
*
***********************************************************************/

   typedef struct tcTarefa {

       int id;

       tpTarefa * tarefa;

   } tcTarefa;

/***** Vari�veis encapsuladas no m�dulo *****/

   static int  idAtual = 0;

/***** Prot�tipos das fun��es encapsuladas no m�dulo *****/

   static void DesconectarTarefas( tpTarefa ** ptTarefa ) ;

/***************************************************************************
*
*  Fun��o: TRF Criar tarefa
*  ****/

   TRF_tpCondRet TRF_CriarTarefa( tcTarefa ** ctTarefa, char * novoNome, char * novaDescricao )
   {

      tcTarefa * cTarefa = (*ctTarefa);
      tpTarefa * pTarefa;

      if ( cTarefa != NULL )
      {
         TRF_DestruirTarefa( ctTarefa ) ;
      } /* if */

      cTarefa = ( tcTarefa * ) malloc( sizeof( tcTarefa )) ;
      if ( cTarefa == NULL )
      {
         return TRF_CondRetFaltouMemoria ;
      } /* if */
      
      pTarefa = (tpTarefa * ) malloc( sizeof( tpTarefa )) ;

      pTarefa->tarefasPredecessoras = LIS_CriarLista(NULL);
      pTarefa->tarefasSucessoras = LIS_CriarLista(NULL);
      LIS_EsvaziarLista( pTarefa->tarefasPredecessoras );
      LIS_EsvaziarLista( pTarefa->tarefasSucessoras );
      cTarefa->id = idAtual;
      pTarefa->nome = (char*)malloc(strlen(novoNome)+1);
      pTarefa->descricao = (char*)malloc(strlen(novaDescricao)+1);
      pTarefa->idRecurso = -1;
      strcpy(pTarefa->nome, novoNome);
      strcpy(pTarefa->descricao, novaDescricao);

      idAtual += 1;

      cTarefa->tarefa = pTarefa;
      (*ctTarefa) = cTarefa;

      return TRF_CondRetOK ;

   } /* Fim fun��o: TRF Criar tarefa */

/***************************************************************************
*
*  Fun��o: TRF Destruir tarefa
*  ****/

   void TRF_DestruirTarefa( tcTarefa ** ctTarefa )
   {
     tcTarefa * cTarefa = (*ctTarefa);

     if ( ctTarefa != NULL)
     {
        if ( cTarefa != NULL )
        {
          DesconectarTarefas( ctTarefa );

          LIS_EsvaziarLista( cTarefa->tarefa->tarefasPredecessoras );
          LIS_DestruirLista( cTarefa->tarefa->tarefasPredecessoras );
          LIS_EsvaziarLista( cTarefa->tarefa->tarefasSucessoras );
          LIS_DestruirLista( cTarefa->tarefa->tarefasSucessoras );
          free(cTarefa->tarefa->nome);
          free(cTarefa->tarefa->descricao);
          free( cTarefa->tarefa );
          free( cTarefa );
          (*ctTarefa) = NULL;

        } /* if */
     }

   } /* Fim fun��o: TRF Destruir tarefa */

/***************************************************************************
*
*  Fun��o: TRF Conectar tarefas
*  ****/

   TRF_tpCondRet TRF_ConectarTarefas( tcTarefa ** ctTarefaSucessora, tcTarefa ** ctTarefaPredecessora )
   {
       LIS_tpCondRet retornoSucessor;
       LIS_tpCondRet retornoPredecessor;
       LIS_tpCondRet procuraListaDoSucessor;
       LIS_tpCondRet procuraListaDoPredecessor;
       LIS_tpCondRet procuraListaDoSucessorInverso;
       LIS_tpCondRet procuraListaDoPredecessorInverso;

       tcTarefa * cTarefaSucessora = (*ctTarefaSucessora);
       tcTarefa * cTarefaPredecessora = (*ctTarefaPredecessora);

       if(cTarefaSucessora == NULL || cTarefaPredecessora == NULL)
       {
           return TRF_CondRetTarefaInexistente;
       }

       IrInicioLista( cTarefaSucessora->tarefa->tarefasPredecessoras ) ;
       IrInicioLista( cTarefaPredecessora->tarefa->tarefasSucessoras ) ;

       procuraListaDoSucessor = LIS_ProcurarValor( cTarefaSucessora->tarefa->tarefasPredecessoras ,(void *) cTarefaPredecessora);
       procuraListaDoPredecessor = LIS_ProcurarValor( cTarefaPredecessora->tarefa->tarefasSucessoras, (void*) cTarefaSucessora );

       if(procuraListaDoSucessor == LIS_CondRetOK && procuraListaDoPredecessor == LIS_CondRetOK)
       {
           return TRF_CondRetConexaoJaExistente;
       }

       IrInicioLista( cTarefaPredecessora->tarefa->tarefasPredecessoras ) ;
       IrInicioLista( cTarefaSucessora->tarefa->tarefasSucessoras ) ;

       procuraListaDoSucessorInverso = LIS_ProcurarValor( cTarefaPredecessora->tarefa->tarefasPredecessoras ,(void *) cTarefaSucessora);
       procuraListaDoPredecessorInverso = LIS_ProcurarValor( cTarefaSucessora->tarefa->tarefasSucessoras ,(void *) cTarefaPredecessora);

       if(procuraListaDoSucessorInverso == LIS_CondRetOK &&  procuraListaDoPredecessorInverso == LIS_CondRetOK)
       {
           return TRF_CondRetConexaoInvalida;
       }

       IrFinalLista( cTarefaSucessora->tarefa->tarefasPredecessoras ) ;
       IrFinalLista( cTarefaPredecessora->tarefa->tarefasSucessoras ) ;
       retornoSucessor = LIS_InserirElementoApos( cTarefaSucessora->tarefa->tarefasPredecessoras , (void *) cTarefaPredecessora);
       retornoPredecessor = LIS_InserirElementoApos( cTarefaPredecessora->tarefa->tarefasSucessoras , (void *) cTarefaSucessora);
        
       return TRF_CondRetOK;

   } /* Fim fun��o: TRF Conectar tarefas */


/***************************************************************************
*
*  Fun��o: TRF Alterar Tarefa
*  ****/

   TRF_tpCondRet  TRF_AlterarTarefa( tcTarefa ** ctTarefa, char * novoNome, char * novaDescricao  )
   {
       tcTarefa * cTarefa = (*ctTarefa);

       if (cTarefa == NULL)
       {
           return TRF_CondRetTarefaInexistente;
       }

       cTarefa->tarefa->nome = NULL;
       cTarefa->tarefa->descricao = NULL;
       cTarefa->tarefa->nome = (char*)malloc(strlen(novoNome)+1);
       cTarefa->tarefa->descricao = (char*)malloc(strlen(novaDescricao)+1);
       strcpy(cTarefa->tarefa->nome, novoNome);
       strcpy(cTarefa->tarefa->descricao, novaDescricao);

       return TRF_CondRetOK ;

   } /* Fim fun��o: TRF Alterar tarefa */

/***************************************************************************
*
*  Fun��o: TRF Consultar Nome da Tarefa
*  ****/

   TRF_tpCondRet  TRF_ConsultarNomeTarefa( tcTarefa ** ctTarefa, char ** nomeConsultado ) 
   {
       tcTarefa * cTarefa = (*ctTarefa);

       if (cTarefa == NULL)
       {
           return TRF_CondRetTarefaInexistente;
       }

       *nomeConsultado = (char*)malloc(strlen(cTarefa->tarefa->nome));
       strcpy(*nomeConsultado, cTarefa->tarefa->nome);

       return TRF_CondRetOK ;

   } /* Fim fun��o: TRF Consultar nome da tarefa */

/***************************************************************************
*
*  Fun��o: TRF Consultar Descricao da Tarefa
*  ****/

   TRF_tpCondRet  TRF_ConsultarDescricaoTarefa( tcTarefa ** ctTarefa, char ** descricaoConsultada ) 
   {
       tcTarefa * cTarefa = (*ctTarefa);

       if (cTarefa == NULL)
       {
           return TRF_CondRetTarefaInexistente;
       }

       *descricaoConsultada = (char*)malloc(strlen(cTarefa->tarefa->descricao));
       strcpy(*descricaoConsultada, cTarefa->tarefa->descricao);

       return TRF_CondRetOK ;

   } /* Fim fun��o: TRF Consultar descricao da tarefa */
   
/***************************************************************************
*
*  Fun��o: TRF Cadastrar id do recurso da tarefa
*  ****/

   TRF_tpCondRet TRF_CadastrarIdRecurso( tcTarefa ** ctTarefa, int idRecurso )
   {
       tcTarefa * cTarefa = (*ctTarefa);

       if (cTarefa == NULL)
       {
           return TRF_CondRetTarefaInexistente;
       }

       cTarefa->tarefa->idRecurso = idRecurso;

       return TRF_CondRetOK ;

   } /* Fim fun��o: TRF Cadastrar id do recurso da tarefa */

/***************************************************************************
*
*  Fun��o: TRF Consultar id do recurso da tarefa
*  ****/

   TRF_tpCondRet TRF_ConsultarIdRecurso( tcTarefa ** ctTarefa, int* idRecurso )
   {
       tcTarefa * cTarefa = (*ctTarefa);

       if (cTarefa == NULL)
       {
           return TRF_CondRetTarefaInexistente;
       }

       if(cTarefa->tarefa->idRecurso == -1)
       {
           return TRF_CondRetIdRecursoNaoCadastrado;
       }

       *idRecurso = cTarefa->tarefa->idRecurso; 

       return TRF_CondRetOK ;

   } /* Fim fun��o: TRF Consultar id do recurso da tarefa */

/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: TRF Desconectar Tarefas
*
*  $EP Par�metros
*     $P ctTarefa - ponteiro passado por refer�ncia que aponta para a 
*                   cabe�a tarefa que ser� desconectada de todas as outras
*                   as quais a mesma est� conectada
*
***********************************************************************/

   static void DesconectarTarefas( tcTarefa ** ctTarefa )
   {
       LIS_tpCondRet retPred = LIS_CondRetOK;
       LIS_tpCondRet retSuc = LIS_CondRetOK;
       LIS_tpCondRet retSucPre = LIS_CondRetOK;
       LIS_tpCondRet retPreSuc = LIS_CondRetOK;

       tcTarefa * cTarefaCorrentePred;
       tcTarefa * cTarefaCorrentePredSuc;
       tcTarefa * cTarefaCorrenteSuc;
       tcTarefa * cTarefaCorrenteSucPred;
       

       int numPassos = 1;
       tcTarefa * cTarefa = (*ctTarefa);

       int flag = 0;

       if(LIS_VerificarVazia(cTarefa->tarefa->tarefasPredecessoras) != LIS_CondRetListaVazia)
       {
           IrInicioLista(cTarefa->tarefa->tarefasPredecessoras);
           cTarefaCorrentePred = (tcTarefa *)LIS_ObterValor( cTarefa->tarefa->tarefasPredecessoras );
           IrInicioLista(cTarefaCorrentePred->tarefa->tarefasSucessoras);

           while(retPred != LIS_CondRetFimLista)
           {
               cTarefaCorrentePred = (tcTarefa *)LIS_ObterValor( cTarefa->tarefa->tarefasPredecessoras );

               while(retPreSuc != LIS_CondRetFimLista)
               {
                   if(flag == 1)
                   {
                       IrInicioLista(cTarefaCorrentePred->tarefa->tarefasSucessoras);
                       flag = 0;
                   }

                   cTarefaCorrentePredSuc = (tcTarefa *)LIS_ObterValor( cTarefaCorrentePred->tarefa->tarefasSucessoras );

                   if(cTarefaCorrentePredSuc->id == cTarefa->id)
                   {
                       LIS_ExcluirElemento( cTarefaCorrentePred->tarefa->tarefasSucessoras );
                       flag = 1;
                       break;
                   }

                   retPreSuc = LIS_AvancarElementoCorrente( cTarefaCorrentePred->tarefa->tarefasSucessoras , numPassos );
               }
           
               retPred = LIS_AvancarElementoCorrente( cTarefa->tarefa->tarefasPredecessoras , numPassos );
           }
       }

       if(LIS_VerificarVazia(cTarefa->tarefa->tarefasSucessoras) != LIS_CondRetListaVazia)
       {
           IrInicioLista(cTarefa->tarefa->tarefasSucessoras);
           cTarefaCorrenteSuc = (tcTarefa *)LIS_ObterValor( cTarefa->tarefa->tarefasSucessoras );
           IrInicioLista(cTarefaCorrenteSuc->tarefa->tarefasPredecessoras);

           while(retSuc != LIS_CondRetFimLista)
           {
               cTarefaCorrenteSuc = (tcTarefa *)LIS_ObterValor( cTarefa->tarefa->tarefasSucessoras );

               while(retSucPre != LIS_CondRetFimLista)
               {
                   if(flag == 1)
                   {
                       IrInicioLista(cTarefaCorrenteSuc->tarefa->tarefasPredecessoras);
                       flag = 0;
                   }

                   cTarefaCorrenteSucPred = (tcTarefa *)LIS_ObterValor( cTarefaCorrenteSuc->tarefa->tarefasPredecessoras );

                   if(cTarefaCorrenteSucPred->id == cTarefa->id)
                   {
                       LIS_ExcluirElemento(cTarefaCorrenteSuc->tarefa->tarefasPredecessoras);
                       flag = 1;
                       break;
                   }

                   retSucPre = LIS_AvancarElementoCorrente( cTarefaCorrenteSuc->tarefa->tarefasPredecessoras , numPassos );
               }

               retSuc = LIS_AvancarElementoCorrente( cTarefa->tarefa->tarefasSucessoras , numPassos );
           }
       }
   }

/********** Fim do m�dulo de implementa��o: M�dulo tarefa **********/
