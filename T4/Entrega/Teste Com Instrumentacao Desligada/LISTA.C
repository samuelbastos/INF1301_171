/***************************************************************************
*  $MCI M�dulo de implementa��o: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: T2 INF1301 2017.1
*  Autores: avs Arndt Von Staa
*			      mv  Maur�cio Vieira
*           sb  Samuel Bastos
* 
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#define LISTA_OWN
#include "LISTA.h"
#undef LISTA_OWN

#undef _DEBUG

#ifdef _DEBUG
#include "CONTA.H"
#include "CESPDIN.H"
#endif

#define TRUE  1
#define FALSE 0

/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
*
***********************************************************************/

    typedef struct tagElemLista {

        void * pValor ;
            /* Ponteiro para o valor contido no elemento */

        struct tagElemLista * pAnt ;
            /* Ponteiro para o elemento predecessor */

        struct tagElemLista * pProx ;
            /* Ponteiro para o elemento sucessor */

        #ifdef _DEBUG
            int tipo;
                /* tipo do dado armazenado no elemento */

            int tamanho;
                /* tamanho de memoria utilizado pelo elemento */
            
            struct LIS_tagLista * pCabeca;
                /* Ponteiro para a cabe�a da lista */
        #endif

    } tpElemLista ;

    /***********************************************************************
    *
    *  $TC Tipo de dados: LIS Descritor da cabe�a de lista
    *
    *
    ***********************************************************************/

    typedef struct LIS_tagLista {

        tpElemLista * pOrigemLista ;
            /* Ponteiro para a origem da lista */

        tpElemLista * pFimLista ;
            /* Ponteiro para o final da lista */

        tpElemLista * pElemCorr ;
            /* Ponteiro para o elemento corrente da lista */

        int numElem ;
            /* N�mero de elementos da lista */

        void ( * ExcluirValor ) ( void * pValor ) ;
            /* Ponteiro para a fun��o de destrui��o do valor contido em um elemento */

        #ifdef _DEBUG
            int tipo;
                /* tipo do dado armazenado no elemento */

            int tamElementos;
                /* tamanho total de memoria utilizado pelos elementos da lista */
        #endif

    } LIS_tpLista ;

    /***** Prot�tipos das fun��es encapuladas no m�dulo *****/

    static void LiberarElemento( LIS_tppLista   pLista ,
                                 tpElemLista  * pElem   ) ;

    static tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                        void *       pValor  ) ;

    static void LimparCabeca( LIS_tppLista pLista ) ;

    /*****  C�digo das fun��es exportadas pelo m�dulo  *****/

    /***************************************************************************
    *
    *  Fun��o: LIS  &Criar lista
    *  ****/

    LIS_tppLista LIS_CriarLista(
                void   ( * ExcluirValor ) ( void * pDado ) )
    {

        LIS_tpLista * pLista = NULL ;

        pLista = ( LIS_tpLista * ) malloc( sizeof( LIS_tpLista )) ;
        if ( pLista == NULL )
        {
            return NULL ;
        } /* if */

        #ifdef _DEBUG
            CNT_CONTAR("LIS_CriarLista");
        #endif

        LimparCabeca( pLista ) ;

        pLista->ExcluirValor = ExcluirValor ;
        
        #ifdef _DEBUG
            CED_MarcarEspacoAtivo(pLista);
            CED_DefinirTipoEspaco(pLista, LIS_IdCabecaLista);
            pLista->tamElementos = 0;
            pLista->tipo = LIS_IdTipoNaoDefinido;
        #endif

        return pLista ;

    } /* Fim fun��o: LIS  &Criar lista */

    /***************************************************************************
    *
    *  Fun��o: LIS  &Destruir lista
    *  ****/

    void LIS_DestruirLista( LIS_tppLista pLista )
    {
        #ifdef _DEBUG
            assert( pLista != NULL ) ;
        #endif

        #ifdef _DEBUG
            CNT_CONTAR("LIS_DestruirLista");
            CED_MarcarTodosEspacosInativos();
        #endif

        LIS_EsvaziarLista( pLista ) ;

        free( pLista ) ;

    } /* Fim fun��o: LIS  &Destruir lista */

    /***************************************************************************
    *
    *  Fun��o: LIS  &Esvaziar lista
    *  ****/

    void LIS_EsvaziarLista( LIS_tppLista pLista )
    {

        tpElemLista * pElem ;
        tpElemLista * pProx ;

        #ifdef _DEBUG
            assert( pLista != NULL ) ;
        #endif

        pElem = pLista->pOrigemLista ;
        while ( pElem != NULL )
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_EsvaziarLista-while0");
            #endif

            pProx = pElem->pProx ;
            LiberarElemento( pLista , pElem ) ;
            pElem = pProx ;
        } /* while */

        LimparCabeca( pLista ) ;

    } /* Fim fun��o: LIS  &Esvaziar lista */

    /***************************************************************************
    *
    *  Fun��o: LIS  &Inserir elemento antes
    *  ****/

    LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                            void * pValor        )
    {

        tpElemLista * pElem ;

        #ifdef _DEBUG
            assert( pLista != NULL ) ;
        #endif

        /* Criar elemento a inerir antes */

        pElem = CriarElemento( pLista , pValor ) ;
        if ( pElem == NULL )
        {
            return LIS_CondRetFaltouMemoria ;
        } /* if */

        #ifdef _DEBUG
            CNT_CONTAR("LIS_InserirElementoAntes");
            pElem->pCabeca = pLista;
            pElem->tamanho = CED_ObterTamanhoValor(pValor);
            pElem->tipo = CED_ObterTipoEspaco(pValor);
            CED_MarcarEspacoAtivo(pElem);
            CED_MarcarEspacoAtivo(pValor);

            pLista->tamElementos += pElem->tamanho + CED_ObterTamanhoValor(pElem);
        #endif

        /* Encadear o elemento antes do elemento corrente */

        if ( pLista->pElemCorr == NULL )
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_InserirElementoAntes-if0");
            #endif

            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;

            #ifdef _DEBUG
                pLista->tipo = pElem->tipo;
            #endif
            
        } else
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_InserirElementoAntes-else0");
            #endif

            if ( pLista->pElemCorr->pAnt != NULL )
            {
                #ifdef _DEBUG
                    CNT_CONTAR("LIS_InserirElementoAntes-if1");
                #endif

                pElem->pAnt  = pLista->pElemCorr->pAnt ;
                pLista->pElemCorr->pAnt->pProx = pElem ;
            } else
            {
                #ifdef _DEBUG
                    CNT_CONTAR("LIS_InserirElementoAntes-else1");
                #endif

                pLista->pOrigemLista = pElem ;
            } /* if */

            pElem->pProx = pLista->pElemCorr ;
            pLista->pElemCorr->pAnt = pElem ;
        } /* if */

        pLista->pElemCorr = pElem ;

        return LIS_CondRetOK ;

    } /* Fim fun��o: LIS  &Inserir elemento antes */

    /***************************************************************************
    *
    *  Fun��o: LIS  &Inserir elemento ap�s
    *  ****/

    LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                           void * pValor        )
      
    {

        tpElemLista * pElem ;

        #ifdef _DEBUG
            assert( pLista != NULL ) ;
        #endif

        /* Criar elemento a inerir ap�s */

        pElem = CriarElemento( pLista , pValor ) ;
        if ( pElem == NULL )
        {
            return LIS_CondRetFaltouMemoria ;
        } /* if */

        #ifdef _DEBUG
            CNT_CONTAR("LIS_InserirElementoApos");
            pElem->pCabeca = pLista;
            pElem->tamanho = CED_ObterTamanhoValor(pElem);
            pElem->tipo = CED_ObterTipoEspaco(pValor);
            CED_MarcarEspacoAtivo(pElem);
            CED_MarcarEspacoAtivo(pValor);

            pLista->tamElementos += pElem->tamanho + CED_ObterTamanhoValor(pElem);
        #endif
        /* Encadear o elemento ap�s o elemento */

        if ( pLista->pElemCorr == NULL )
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_InserirElementoApos-if0");
            #endif

            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
            #ifdef _DEBUG
                pLista->tipo = pElem->tipo;
            #endif
        } else
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_InserirElementoApos-else0");
            #endif

            if ( pLista->pElemCorr->pProx != NULL )
            {
                #ifdef _DEBUG
                    CNT_CONTAR("LIS_InserirElementoApos-if1");
                #endif

                pElem->pProx  = pLista->pElemCorr->pProx ;
                pLista->pElemCorr->pProx->pAnt = pElem ;
            } else
            {
                #ifdef _DEBUG
                    CNT_CONTAR("LIS_InserirElementoApos-else1");
                #endif

                pLista->pFimLista = pElem ;
            } /* if */

            pElem->pAnt = pLista->pElemCorr ;
            pLista->pElemCorr->pProx = pElem ;

        } /* if */
                  
        pLista->pElemCorr = pElem ;
                  
        return LIS_CondRetOK ;

    } /* Fim fun��o: LIS  &Inserir elemento ap�s */

    /***************************************************************************
    *
    *  Fun��o: LIS  &Excluir elemento
    *  ****/

    LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista )
    {

        tpElemLista * pElem ;

        #ifdef _DEBUG
            assert( pLista  != NULL ) ;
        #endif

        if ( pLista->pElemCorr == NULL )
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_ExcluirElemento-if0");
            #endif

            return LIS_CondRetListaVazia ;
        } /* if */

        #ifdef _DEBUG
            CNT_CONTAR("LIS_ExcluirElemento-sq0");
        #endif

        pElem = pLista->pElemCorr ;

        /* Desencadeia � esquerda */

        if ( pElem->pAnt != NULL )
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_ExcluirElemento-if1");
            #endif
            pElem->pAnt->pProx   = pElem->pProx ;
            pLista->pElemCorr    = pElem->pAnt ;
        } else {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_ExcluirElemento-else1");
            #endif
            pLista->pElemCorr    = pElem->pProx ;
            pLista->pOrigemLista = pLista->pElemCorr ;

        } /* if */

        /* Desencadeia � direita */

        if ( pElem->pProx != NULL )
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_ExcluirElemento-if2");
            #endif
            pElem->pProx->pAnt = pElem->pAnt ;
        } else
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_ExcluirElemento-else2");
            #endif
            pLista->pFimLista = pElem->pAnt ;
        } /* if */

        LiberarElemento( pLista , pElem ) ;

        #ifdef _DEBUG
            if (LIS_VerificarVazia(pLista) == LIS_CondRetListaVazia)
                pLista->tipo = LIS_IdTipoNaoDefinido;
            else
                pLista->tipo = pLista->pOrigemLista->tipo;
        #endif


        return LIS_CondRetOK ;

    } /* Fim fun��o: LIS  &Excluir elemento */

    /***************************************************************************
    *
    *  Fun��o: LIS  &Obter refer�ncia para o valor contido no elemento
    *  ****/

    void * LIS_ObterValor( LIS_tppLista pLista )
    {

        #ifdef _DEBUG
            assert( pLista != NULL ) ;
        #endif

        if ( pLista->pElemCorr == NULL )
        {        
            #ifdef _DEBUG
                CNT_CONTAR("LIS_ObterValor-if0");
            #endif
            return NULL ;
        } /* if */

        #ifdef _DEBUG
            CNT_CONTAR("LIS_ObterValor-sq0");
        #endif

        return pLista->pElemCorr->pValor ;

    } /* Fim fun��o: LIS  &Obter refer�ncia para o valor contido no elemento */

    /***************************************************************************
    *
    *  Fun��o: LIS  &Ir para o elemento inicial
    *  ****/

    void IrInicioLista( LIS_tppLista pLista )
    {

        #ifdef _DEBUG
            assert( pLista != NULL ) ;
        #endif

        #ifdef _DEBUG
            CNT_CONTAR("LIS_IrInicioLista");
        #endif

        pLista->pElemCorr = pLista->pOrigemLista ;

    } /* Fim fun��o: LIS  &Ir para o elemento inicial */

    /***************************************************************************
    *
    *  Fun��o: LIS  &Ir para o elemento final
    *  ****/

    void IrFinalLista( LIS_tppLista pLista )
    {

        #ifdef _DEBUG
            assert( pLista != NULL ) ;
        #endif

        #ifdef _DEBUG
            CNT_CONTAR("LIS_IrFinalLista");
        #endif

        pLista->pElemCorr = pLista->pFimLista ;

    } /* Fim fun��o: LIS  &Ir para o elemento final */

    /***************************************************************************
    *
    *  Fun��o: LIS  &Avan�ar elemento
    *  ****/

    LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                               int numElem )
    {
        int i ;

        tpElemLista * pElem ;

        #ifdef _DEBUG
            assert( pLista != NULL ) ;
        #endif

        /* Tratar lista vazia */

        if ( pLista->pElemCorr == NULL )
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_AvancarElementoCorrente-if0");
            #endif
            return LIS_CondRetListaVazia ;

        } /* fim ativa: Tratar lista vazia */

        #ifdef _DEBUG
            CNT_CONTAR("LIS_AvancarElementoCorrente-sq0");
        #endif

        /* Tratar avan�ar para frente */

        if ( numElem > 0 )
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_AvancarElementoCorrente-if1");
            #endif
            pElem = pLista->pElemCorr ;
            for( i = numElem ; i > 0 ; i-- )
            {
                #ifdef _DEBUG
                    CNT_CONTAR("LIS_AvancarElementoCorrente-if1-for0");
                #endif
                if ( pElem == NULL )
                {
                    #ifdef _DEBUG
                        CNT_CONTAR("LIS_AvancarElementoCorrente-if1-for0-if0");
                    #endif
                    break ;
                } /* if */

                pElem    = pElem->pProx ;
            } /* for */

            if ( pElem != NULL )
            {
                #ifdef _DEBUG
                    CNT_CONTAR("LIS_AvancarElementoCorrente-if1-if0");
                #endif
                pLista->pElemCorr = pElem ;
                return LIS_CondRetOK ;
            } /* if */

            #ifdef _DEBUG
                CNT_CONTAR("LIS_AvancarElementoCorrente-if1-sq0");
            #endif

            pLista->pElemCorr = pLista->pFimLista ;
            return LIS_CondRetFimLista ;

        } /* fim ativa: Tratar avan�ar para frente */

        /* Tratar avan�ar para tr�s */

        else if ( numElem < 0 )
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_AvancarElementoCorrente-elseif1");
            #endif
            pElem = pLista->pElemCorr ;
            for( i = numElem ; i < 0 ; i++ )
            {
                #ifdef _DEBUG
                    CNT_CONTAR("LIS_AvancarElementoCorrente-elseif1-for0");
                #endif
                if ( pElem == NULL )
                {
                    #ifdef _DEBUG
                        CNT_CONTAR("LIS_AvancarElementoCorrente-elseif1-for0-if0");
                    #endif
                    break ;
                } /* if */

                pElem    = pElem->pAnt ;
            } /* for */

            if ( pElem != NULL )
            {
                #ifdef _DEBUG
                    CNT_CONTAR("LIS_AvancarElementoCorrente-elseif1-if0");
                #endif
                pLista->pElemCorr = pElem ;
                return LIS_CondRetOK ;
            } /* if */

            #ifdef _DEBUG
                CNT_CONTAR("LIS_AvancarElementoCorrente-elseif1-sq0");
            #endif

            pLista->pElemCorr = pLista->pOrigemLista ;
            return LIS_CondRetFimLista ;

        } /* fim ativa: Tratar avan�ar para tr�s */

        /* Tratar n�o avan�ar */

        #ifdef _DEBUG
            CNT_CONTAR("LIS_AvancarElementoCorrente-sq1");
        #endif

        return LIS_CondRetOK ;

    } /* Fim fun��o: LIS  &Avan�ar elemento */

    /***************************************************************************
    *
    *  Fun��o: LIS  &Procurar elemento contendo valor
    *  ****/

    LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                     void * pValor        )
    {

        tpElemLista * pElem ;

        #ifdef _DEBUG
            assert( pLista  != NULL ) ;
        #endif

        if ( pLista->pElemCorr == NULL )
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_ProcurarValor-if0");
            #endif
            return LIS_CondRetListaVazia ;
        } /* if */

        #ifdef _DEBUG
            CNT_CONTAR("LIS_ProcurarValor-sq0");
        #endif

        for ( pElem  = pLista->pElemCorr ;
              pElem != NULL ;
              pElem  = pElem->pProx )
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_ProcurarValor-for0");
            #endif

            if ( pElem->pValor == pValor )
            {
                #ifdef _DEBUG
                    CNT_CONTAR("LIS_ProcurarValor-for0-if0");
                #endif

                pLista->pElemCorr = pElem ;
                return LIS_CondRetOK ;
            } /* if */
        } /* for */

        #ifdef _DEBUG
            CNT_CONTAR("LIS_ProcurarValor-sq1");
        #endif

        return LIS_CondRetNaoAchou ;

    } /* Fim fun��o: LIS  &Procurar elemento contendo valor */

    /***************************************************************************
    *
    *  Fun��o: LIS  &Verificar Vazia
    *  ****/

    LIS_tpCondRet LIS_VerificarVazia( LIS_tppLista pLista ) 
    {
        if (pLista->numElem == 0)
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_VerificarVazia-if0");
            #endif
            return LIS_CondRetListaVazia;
        }
        else
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_VerificarVazia-else0");
            #endif
            return LIS_CondRetHaElemento;
        }
    } /* Fim fun��o: LIS  &Verificar Vazia */

    /***************************************************************************
    *
    *  Fun��o: LIS  &Adiciona ao Final
    *  ****/

    LIS_tpCondRet LIS_InserirElementoFinal( LIS_tppLista pLista,	void * pValor  )
    {
        #ifdef _DEBUG
            CNT_CONTAR("LIS_InserirElementoFinal");
        #endif
        IrFinalLista(pLista);
        return LIS_InserirElementoApos(pLista, pValor);

    } /* Fim fun��o: LIS  LIS  &Adiciona ao Final */

    #ifdef _DEBUG

    /***************************************************************************
    *
    *  Fun��o: LIS  &LIS Verificar estrutura
    *  ****/

    LIS_tpCondRet LIS_VerificarEstrutura( LIS_tppLista pLista, int * numErros )
    {
        int iteradorCED = TRUE;
        void * ponteiroCED;
        int numElementosRealLista = 0;
        int tamanhoRealLista = 0;
        LIS_tpCondRet fimLista = LIS_CondRetOK;


        // Garante que se o ponteiro para o corrente for null a lista tem que estar vazia
        if ( pLista->pElemCorr == NULL && pLista->numElem > 0)
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_VerificarEstrutura-if9");
            #endif
            (*numErros)++;
        }

        
        // Checa se o tamanho da lista esta correto
        IrInicioLista(pLista);
        if (pLista->pOrigemLista != NULL)
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_VerificarEstrutura-if0");
            #endif
            while ( fimLista != LIS_CondRetFimLista)
            {
                #ifdef _DEBUG
                    CNT_CONTAR("LIS_VerificarEstrutura-if0-while0");
                #endif
                numElementosRealLista++;
                fimLista = LIS_AvancarElementoCorrente(pLista, 1);
            }
        }
        if (numElementosRealLista != pLista->numElem)
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_VerificarEstrutura-if1");
            #endif
            (*numErros)++;
        }

        // Checa se o tamanho em memoria da lista esta correto
        IrInicioLista(pLista);
        fimLista = LIS_CondRetOK;
        if (pLista->pOrigemLista != NULL)
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_VerificarEstrutura-if2");
            #endif
            while ( fimLista != LIS_CondRetFimLista)
            {
                #ifdef _DEBUG
                    CNT_CONTAR("LIS_VerificarEstrutura-if2-while0");
                #endif
                tamanhoRealLista += pLista->pElemCorr->tamanho + CED_ObterTamanhoValor(pLista->pElemCorr);
                fimLista = LIS_AvancarElementoCorrente(pLista, 1);
            }
        }
        if (tamanhoRealLista != pLista->tamElementos)
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_VerificarEstrutura-if3");
            #endif
            (*numErros)++;
        }

        // Testa se a lista esta perfeitamente conexa
        IrInicioLista(pLista);
        fimLista = LIS_CondRetOK;
        if (pLista->pOrigemLista != NULL)
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_VerificarEstrutura-if4");
            #endif
            while ( fimLista != LIS_CondRetFimLista)
            {
                #ifdef _DEBUG
                    CNT_CONTAR("LIS_VerificarEstrutura-if4-while0");
                #endif
                if (pLista->pElemCorr->pAnt != NULL)
                {
                    #ifdef _DEBUG
                        CNT_CONTAR("LIS_VerificarEstrutura-if4-while0-if0");
                    #endif
                    if (pLista->pElemCorr->pAnt->pProx != pLista->pElemCorr)
                    {
                        #ifdef _DEBUG
                            CNT_CONTAR("LIS_VerificarEstrutura-if4-while0-if0-if0");
                        #endif
                        (*numErros)++;
                    }
                }
                if (pLista->pElemCorr->pProx != NULL)
                {
                    #ifdef _DEBUG
                        CNT_CONTAR("LIS_VerificarEstrutura-if4-while0-if1");
                    #endif
                    if (pLista->pElemCorr->pProx->pAnt != pLista->pElemCorr)
                    {
                        #ifdef _DEBUG
                            CNT_CONTAR("LIS_VerificarEstrutura-if4-while0-if1-if0");
                        #endif
                        (*numErros)++;
                    }
                }
                fimLista = LIS_AvancarElementoCorrente(pLista, 1);
            }
        }

        // Checa se todos os nos apontam para alguma coisa

        IrInicioLista(pLista);
        fimLista = LIS_CondRetOK;
        if (pLista->pOrigemLista != NULL)
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_VerificarEstrutura-if5");
            #endif
            while ( fimLista != LIS_CondRetFimLista)
            {
                #ifdef _DEBUG
                    CNT_CONTAR("LIS_VerificarEstrutura-if5-while0");
                #endif
                if ( pLista->pElemCorr->pValor == NULL )
                {
                    #ifdef _DEBUG
                        CNT_CONTAR("LIS_VerificarEstrutura-if5-while0-if0");
                    #endif
                    (*numErros)++;
                }
                fimLista = LIS_AvancarElementoCorrente(pLista, 1);
            }
        }

        // Testa se todos os nos dizem ser do mesmo tipo do cabeca
        if (pLista->pOrigemLista != NULL)
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_VerificarEstrutura-if6");
            #endif
            IrInicioLista(pLista);
            fimLista = LIS_CondRetOK;
            while ( fimLista != LIS_CondRetFimLista)
            {
                #ifdef _DEBUG
                    CNT_CONTAR("LIS_VerificarEstrutura-if6-while0");
                #endif
                if ( pLista->pElemCorr->tipo != pLista->tipo )
                {
                    #ifdef _DEBUG
                        CNT_CONTAR("LIS_VerificarEstrutura-if6-while0-if0");
                    #endif
                    (*numErros)++;
                }
                fimLista = LIS_AvancarElementoCorrente(pLista, 1);
            }
        }
        else
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_VerificarEstrutura-else6");
            #endif
            if (pLista->tipo != LIS_IdTipoNaoDefinido)
            {
                #ifdef _DEBUG
                    CNT_CONTAR("LIS_VerificarEstrutura-else6-if0");
                #endif
                (*numErros)++;
            }
        }

        // Testar se todos os nos possuem o mesmo tipo dos dados que armazenam
        if (pLista->pOrigemLista != NULL)
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_VerificarEstrutura-if7");
            #endif
            IrInicioLista(pLista);
            fimLista = LIS_CondRetOK;
            while ( fimLista != LIS_CondRetFimLista)
            {
                #ifdef _DEBUG
                    CNT_CONTAR("LIS_VerificarEstrutura-if7-while0");
                #endif
                if ( pLista->pElemCorr->tipo != CED_ObterTipoEspaco(pLista->pElemCorr->pValor))
                {
                    #ifdef _DEBUG
                        CNT_CONTAR("LIS_VerificarEstrutura-if7-while0-if0");
                    #endif
                    (*numErros)++;
                }
                fimLista = LIS_AvancarElementoCorrente(pLista, 1);
            }
        }

        // Garante que se o ponteiro para a origem for null a lista tem que estar vazia
        if ( pLista->pOrigemLista == NULL && pLista->numElem > 0 )
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_VerificarEstrutura-if8");
            #endif
            (*numErros)++;
        }

        // Checar Lista de Espa�os Alocados
        IrInicioLista(pLista);
        fimLista = LIS_CondRetOK;
        CED_MarcarEspacoNaoAtivo(pLista);
        if (pLista->pOrigemLista != NULL)
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_VerificarEstrutura-if10");
            #endif
            while ( fimLista != LIS_CondRetFimLista)
            {
                #ifdef _DEBUG
                    CNT_CONTAR("LIS_VerificarEstrutura-if10-while0");
                #endif
                CED_MarcarEspacoNaoAtivo(pLista->pElemCorr);
                CED_MarcarEspacoNaoAtivo(pLista->pElemCorr->pValor);
                fimLista = LIS_AvancarElementoCorrente(pLista, 1);
            }
        }

        CED_InicializarIteradorEspacos();
        while (iteradorCED)
        {
            #ifdef _DEBUG
                CNT_CONTAR("LIS_VerificarEstrutura-while0");
            #endif
            ponteiroCED = CED_ObterPonteiroEspacoCorrente();
            if (CED_EhEspacoAtivo(ponteiroCED))
            {
                #ifdef _DEBUG
                    CNT_CONTAR("LIS_VerificarEstrutura-while0-if0");
                #endif
                (*numErros)++;
            }
            iteradorCED = CED_AvancarProximoEspaco();
        }

    }

    /***************************************************************************
    *
    *  Fun��o: LIS  &LIS Deturpar estrutura
    *  ****/

    LIS_tpCondRet LIS_Deturpar( LIS_tppLista pLista, int flag )
    {
        tpElemLista * ponteiroNaoInicializado, * auxProx, * auxAnt;
        switch(flag)
        {
            case 1:
                pLista->pElemCorr->pAnt = NULL;
                break;

            case 2:
                pLista->pElemCorr->pProx = NULL;
                break;

            case 3:
                pLista->pElemCorr->pValor = NULL;
                break;

            case 4:
                CED_DefinirTipoEspaco(pLista->pElemCorr->pValor, LIS_IdCabecaLista);
                break;

            case 5:
                auxAnt = pLista->pElemCorr->pAnt;
                auxProx = pLista->pElemCorr->pProx;
                pLista->pElemCorr->pProx->pAnt = auxAnt;
                pLista->pElemCorr->pAnt->pProx = auxProx;
                break;

            case 6:
                pLista->pElemCorr = NULL;
                break;

            case 7:
                pLista->pOrigemLista = NULL;
                break;

            case 8:
                pLista->pElemCorr->pAnt = pLista->pElemCorr->pAnt->pAnt;
                break;

            case 9:
                pLista->pElemCorr->pProx = pLista->pElemCorr->pProx->pProx;
                break;

            case 10:
                pLista->pElemCorr->tipo = LIS_IdTipoNaoDefinido;
                break;
        }

        return LIS_CondRetOK;
    }

    #endif

    /*****  C�digo das fun��es encapsuladas no m�dulo  *****/


    /***********************************************************************
    *
    *  $FC Fun��o: LIS  -Liberar elemento da lista
    *
    *  $ED Descri��o da fun��o
    *     Elimina os espa�os apontados pelo valor do elemento e o
    *     pr�prio elemento.
    *
    ***********************************************************************/

    void LiberarElemento( LIS_tppLista   pLista ,
    tpElemLista  * pElem   )
    {
        #ifdef _DEBUG
            pLista->tamElementos -= pElem->tamanho;
            pLista->tamElementos -= CED_ObterTamanhoValor(pElem);
        #endif

        if ( ( pLista->ExcluirValor != NULL )
          && ( pElem->pValor != NULL        ))
        {
            #ifdef _DEBUG
                CNT_CONTAR("LiberarElemento-if0");
            #endif
            pLista->ExcluirValor( pElem->pValor ) ;
        } /* if */

        #ifdef _DEBUG
                CNT_CONTAR("LiberarElemento-pr0");
        #endif

        free( pElem ) ;

        pLista->numElem-- ;


    } /* Fim fun��o: LIS  -Liberar elemento da lista */


    /***********************************************************************
    *
    *  $FC Fun��o: LIS  -Criar o elemento
    *
    ***********************************************************************/

    tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                 void *       pValor  )
    {

        tpElemLista * pElem ;

        pElem = ( tpElemLista * ) malloc( sizeof( tpElemLista )) ;
        if ( pElem == NULL )
        {
            return NULL ;
        } /* if */

        #ifdef _DEBUG
            CNT_CONTAR("CriarElemento");
            CED_MarcarEspacoAtivo(pElem);
            CED_DefinirTipoEspaco(pElem, LIS_IdNoLista);
        #endif

        pElem->pValor = pValor ;
        pElem->pAnt   = NULL  ;
        pElem->pProx  = NULL  ;

        pLista->numElem ++ ;

        return pElem ;

    } /* Fim fun��o: LIS  -Criar o elemento */


    /***********************************************************************
    *
    *  $FC Fun��o: LIS  -Limpar a cabe�a da lista
    *
    ***********************************************************************/

    void LimparCabeca( LIS_tppLista pLista )
    {
        #ifdef _DEBUG
            CNT_CONTAR("LimparCabeca");
            pLista->tamElementos = 0;
            pLista->tipo = LIS_IdTipoNaoDefinido;
        #endif
        pLista->pOrigemLista = NULL ;
        pLista->pFimLista = NULL ;
        pLista->pElemCorr = NULL ;
        pLista->numElem   = 0 ;

    } /* Fim fun��o: LIS  -Limpar a cabe�a da lista */

    /********** Fim do m�dulo de implementa��o: LIS  Lista duplamente encadeada **********/

