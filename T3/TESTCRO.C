/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo de teste espec�fico
*
*  Arquivo gerado:              TESTCRO.C
*  Letras identificadoras:      TCRO
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: T3 INF1301 2017.1
*  Autores: mv Maur�cio Vieira
*           sb Samuel Bastos
*
*  $ED Descri��o do m�dulo
*     Este m�dulo cont�m as fun��es espec�ficas para o teste do
*     m�dulo tarefa. Ilustra como redigir um interpretador de comandos
*     de teste espec�ficos utilizando o arcabou�o de teste para C.
*
*  $EIU Interface com o usu�rio pessoa
*     Comandos de teste espec�ficos para testar o m�dulo tarefa:
*
*     "=criar"          - chama a fun��o CRO_CriarCronograma( )
*     "=destruir"       - chama a fun��o CRO_DestruirCronograma( )
*     "=instrf"		       - chama a fun��o CRO_InserirTarefa( )
*     "=insrec"	        - chama a fun��o CRO_InserirRecurso( )
*					"=implisrec"						- chama a fun��o CRO_ImprimeListaRecurso( )
*					"=implistrf"						- chama a fun��o CRO_ImprimeListaTarefa( )
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <stdlib.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"

#include    "cronograma.h"
#include				"lista.h"

#define STRING_DIM 100

/* Tabela dos nomes dos comandos de teste espec�ficos */

#define     CRIAR_CRO_CMD               "=criar"
#define     DESTRUIR_CRO_CMD						"=destruir"
#define     INSERIR_TRF_CRO_CMD					"=instrf"
#define     INSERIR_REC_CRO_CMD         "=insrec"
#define     DELETAR_TRF_CRO_CMD					"=deltrf"
#define     DELETAR_REC_CRO_CMD         "=delrec"
#define			CONECTAR_TRF_CRO_CMD				"=conectartrf"
#define     IMPRIME_LIS_TRF_CRO_CMD			"=implistrf"
#define     IMPRIME_LIS_REC_CRO_CMD	    "=implisrec"
#define     CAMINHO_CRITICO_CRO_CMD     "=caminhocritico"
#define     ALTERAR_TAREFA_CRO_CMD      "=alteratarefa"
#define     ALTERAR_RECURSO_CRO_CMD     "=alterarecurso"
#define     GERAR_CRO_CMD               "=cronograma"

/* Vetor de tarefas para serem usados nos testes */

tcCronograma * cronogramas[10];

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TTRF Efetuar opera��es de teste espec�ficas para tarefa
*
*  $ED Descri��o da fun��o
*     Efetua os diversos comandos de teste espec�ficos para o m�dulo
*     tarefa sendo testado.
*
*  $EP Par�metros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

    TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
    {

        CRO_tpCondRet CondRetObtido   = CRO_CondRetOK ;
        CRO_tpCondRet CondRetEsperada = CRO_CondRetFaltouMemoria ;
        /* inicializa para qualquer coisa */

        char ValorEsperado   = '?'  ;
        char ValorObtido     = '!'  ;
        char ValorDado       = '\0' ;
        int  CronogramaObtido  = 11  ;
        int  duracaoObtida = -1;
        int  TarefaObtidaAux = 12;
        int  idTarefaObtido = -1;
        int  idTarefaSucessora = -1;
        int  idTarefaPredecessora = -1;
        int  idRecursoObtido = -1;
        char NomeObtido[STRING_DIM];
        char DescricaoObtida[STRING_DIM];
        char * NomeConsultado = (char*)malloc(sizeof(char)*STRING_DIM);
        char * DescricaoConsultada = (char*)malloc(sizeof(char)*STRING_DIM);
        int  NumLidos = -1 ;

        TST_tpCondRet Ret ;

        /* Testar CRO Criar Cronograma */

        if ( strcmp( ComandoTeste , CRIAR_CRO_CMD ) == 0 )
        {

            NumLidos = LER_LerParametros( "ii" , &CronogramaObtido, &CondRetEsperada ) ;

            if ( NumLidos != 2 )
            {
                return TST_CondRetParm ;
            } /* if */

            if ( CronogramaObtido < 10 && CronogramaObtido >= 0 )
            {
                CondRetObtido = CRO_CriarCronograma(&cronogramas[CronogramaObtido]);
            }
            else
            {
                return TST_CompararInt(CondRetEsperada, TST_CondRetAcessoInvalidoVetor, "Acesso Invalido ao vetor de cronogramas.");
            }

            return TST_CompararInt( CondRetEsperada , CondRetObtido , "Retorno errado ao criar cronograma." );

        } /* fim ativa: Testar CRO Criar Cronograma */

        /* Testar CRO Destruir cronograma */

        else if ( strcmp( ComandoTeste , DESTRUIR_CRO_CMD ) == 0 )
        {
            NumLidos = LER_LerParametros( "i", &CronogramaObtido ) ;

            if ( NumLidos != 1 )
            {
                return TST_CondRetParm ;
            } /* if */

            if ( CronogramaObtido < 10 && CronogramaObtido >= 0 )
            {
                CRO_DestruirCronograma( &cronogramas[CronogramaObtido] ) ;
            }
            else
            {
                return TST_CompararInt(CondRetEsperada, TST_CondRetAcessoInvalidoVetor, "Acesso Invalido ao vetor de cronogramas.");
            }

            return TST_CondRetOK ;

        } /* fim ativa: Testar CRO Destruir cronograma */

        /* Testar CRO Insere Tarefa */

        else if ( strcmp( ComandoTeste , INSERIR_TRF_CRO_CMD ) == 0 )
        {
            NumLidos = LER_LerParametros( "issii" , &CronogramaObtido, NomeObtido, DescricaoObtida, &duracaoObtida, &CondRetEsperada ) ;
            if ( NumLidos != 5 )
            {
                return TST_CondRetParm ;
            } /* if */

            if ( CronogramaObtido < 10 && CronogramaObtido >= 0 )
            {
                CondRetObtido = CRO_InserirTarefa(cronogramas[CronogramaObtido], NomeObtido, DescricaoObtida, duracaoObtida);
            }
            else
            {
                return TST_CompararInt(CondRetEsperada, TST_CondRetAcessoInvalidoVetor, "Acesso Invalido ao vetor de tarefas.");
            }

            return TST_CompararInt( CondRetEsperada , CondRetObtido , "Retorno errado ao inserir tarefa na lista de tarefas do cronograma." );

        } /* fim ativa: Testar CRO Insere Tarefa */

        /* Testar CRO Insere Recurso */

        else if ( strcmp( ComandoTeste , INSERIR_REC_CRO_CMD) == 0 )
        {

            NumLidos = LER_LerParametros( "isi" , &CronogramaObtido, NomeObtido, &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
                return TST_CondRetParm ;
            } /* if */

            if (CronogramaObtido < 10 && CronogramaObtido >= 0)
            {
                CondRetObtido = CRO_InserirRecurso(cronogramas[CronogramaObtido], NomeObtido);
            }
            else
            {
                return TST_CompararInt(CondRetEsperada, TST_CondRetAcessoInvalidoVetor, "Acesso Invalido ao vetor de cronogramas.");
            }

            return TST_CompararInt( CondRetEsperada , CondRetObtido , "Retorno errado ao inserir recurso na lista de recursos do cronograma." );

        } /* fim ativa: Testar CRO Insere Recurso */

        /* Testar CRO Remover Tarefa */

        else if ( strcmp( ComandoTeste , DELETAR_TRF_CRO_CMD ) == 0 )
        {
            NumLidos = LER_LerParametros( "iii" , &CronogramaObtido, &idTarefaObtido, &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
                return TST_CondRetParm ;
            } /* if */

            if ( CronogramaObtido < 10 && CronogramaObtido >= 0 )
            {
                CondRetObtido = CRO_RemoveTarefa(cronogramas[CronogramaObtido], idTarefaObtido);
            }
            else
            {
                return TST_CompararInt(CondRetEsperada, TST_CondRetAcessoInvalidoVetor, "Acesso Invalido ao vetor de cronogramas.");
            }

            return TST_CompararInt( CondRetEsperada , CondRetObtido , "Retorno errado ao remover tarefa na lista de tarefas do cronograma." );

        } /* fim ativa: Testar CRO Remover Tarefa */

        /* Testar CRO Remover Recurso */

        else if ( strcmp( ComandoTeste , DELETAR_REC_CRO_CMD) == 0 )
        {

            NumLidos = LER_LerParametros( "iii" , &CronogramaObtido, &idRecursoObtido, &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
                return TST_CondRetParm ;
            } /* if */

            if (CronogramaObtido < 10 && CronogramaObtido >= 0)
            {
                CondRetObtido = CRO_RemoveRecurso(cronogramas[CronogramaObtido], idRecursoObtido);
            }
            else
            {
                return TST_CompararInt(CondRetEsperada, TST_CondRetAcessoInvalidoVetor, "Acesso Invalido ao vetor de cronogramas.");
            }

            return TST_CompararInt( CondRetEsperada , CondRetObtido , "Retorno errado ao remover recurso na lista de recursos do cronograma." );

        } /* fim ativa: Testar CRO Remover Recurso */

        /* Testar CRO Conectar Tarefas */

        else if ( strcmp( ComandoTeste , CONECTAR_TRF_CRO_CMD) == 0 )
        {

            NumLidos = LER_LerParametros( "iiii" , &CronogramaObtido, &idTarefaSucessora, &idTarefaPredecessora, &CondRetEsperada ) ;
            if ( NumLidos != 4 )
            {
                return TST_CondRetParm ;
            } /* if */

            if (CronogramaObtido < 10 && CronogramaObtido >= 0)
            {
                CondRetObtido = CRO_ConectarTarefas(cronogramas[CronogramaObtido], idTarefaSucessora, idTarefaPredecessora);
            }
            else
            {
                return TST_CompararInt(CondRetEsperada, TST_CondRetAcessoInvalidoVetor, "Acesso Invalido ao vetor de cronogramas.");
            }

            return TST_CompararInt( CondRetEsperada , CondRetObtido , "Retorno errado ao inserir recurso na lista de recursos do cronograma." );

        } /* fim ativa: Testar CRO Insere Recurso */

        /* Testar CRO Imprime Lista Tarefa */

        else if ( strcmp( ComandoTeste , IMPRIME_LIS_TRF_CRO_CMD) == 0 )
        {

            NumLidos = LER_LerParametros( "ii" , &CronogramaObtido, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
                return TST_CondRetParm ;
            } /* if */

            if (CronogramaObtido < 10 && CronogramaObtido >= 0)
            {
                CondRetObtido = CRO_ImprimeListaTarefa(cronogramas[CronogramaObtido]);
            }
            else
            {
                return TST_CompararInt(CondRetEsperada, TST_CondRetAcessoInvalidoVetor, "Acesso Invalido ao vetor de cronogramas.");
            }

            return TST_CompararInt( CondRetEsperada , CondRetObtido , "Retorno errado ao imprimir lista de tarefas do cronograma." );

        } /* fim ativa: Testar CRO Imprime Lista Tarefa */

        /* Testar CRO Imprime Lista Recurso */

        else if ( strcmp( ComandoTeste , IMPRIME_LIS_REC_CRO_CMD) == 0 )
        {

            NumLidos = LER_LerParametros( "ii" , &CronogramaObtido, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
                return TST_CondRetParm ;
            } /* if */

            if (CronogramaObtido < 10 && CronogramaObtido >= 0)
            {
                CondRetObtido = CRO_ImprimeListaRecurso(cronogramas[CronogramaObtido]);
            }
            else
            {
                return TST_CompararInt(CondRetEsperada, TST_CondRetAcessoInvalidoVetor, "Acesso Invalido ao vetor de cronogramas.");
            }

            return TST_CompararInt( CondRetEsperada , CondRetObtido , "Retorno errado ao imprimir lista de recursos do cronograma." );

        } /* fim ativa: Testar CRO Imprime Lista Recurso */

        /* Testar CRO Calcula Caminho Critico */

        else if ( strcmp( ComandoTeste , CAMINHO_CRITICO_CRO_CMD) == 0 )
        {

            NumLidos = LER_LerParametros( "ii" , &CronogramaObtido, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
                return TST_CondRetParm ;
            } /* if */

            if (CronogramaObtido < 10 && CronogramaObtido >= 0)
            {
                CondRetObtido = CRO_CaminhoCritico(cronogramas[CronogramaObtido]);
            }
            else
            {
                return TST_CompararInt(CondRetEsperada, TST_CondRetAcessoInvalidoVetor, "Acesso Invalido ao vetor de cronogramas.");
            }

            return TST_CompararInt( CondRetEsperada , CondRetObtido, "Retorno errado ao imprimir lista de recursos do cronograma." );

        } /* fim ativa: Testar CRO Calcula Caminho Critico */

        /* Testar CRO Altera tarefa */

        else if ( strcmp(ComandoTeste , ALTERAR_TAREFA_CRO_CMD) == 0 )
        {
            NumLidos = LER_LerParametros( "iissii", &CronogramaObtido, &idTarefaObtido, NomeObtido, DescricaoObtida, &duracaoObtida, &CondRetEsperada );
            if( NumLidos != 6 )
            {
                return TST_CondRetParm;
            } /* if */

            if (CronogramaObtido < 10 && CronogramaObtido >= 0)
            {
                CondRetObtido = CRO_AlterarTarefa(cronogramas[CronogramaObtido], idTarefaObtido, NomeObtido, DescricaoObtida, duracaoObtida);
            }
            else
            {
                return TST_CompararInt(CondRetEsperada, TST_CondRetAcessoInvalidoVetor, "Acesso Invalido ao vetor de cronogramas.");
            }

            return TST_CompararInt( CondRetEsperada , CondRetObtido, "Retorno errado ao alterar tarefa do cronograma" ); 

        } /* fim ativa: Testar CRO Altera Tarefa */

        /* Testar CRO Altera Recurso */

        else if ( strcmp(ComandoTeste , ALTERAR_RECURSO_CRO_CMD) == 0 )
        {
            NumLidos = LER_LerParametros( "iisi", &CronogramaObtido, &idRecursoObtido, NomeObtido, &CondRetEsperada );
            if( NumLidos != 4 )
            {
                return TST_CondRetParm;
            } /* if */

            if (CronogramaObtido < 10 && CronogramaObtido >= 0)
            {
                CondRetObtido = CRO_AlterarRecurso(cronogramas[CronogramaObtido], idRecursoObtido, NomeObtido);
            }
            else
            {
                return TST_CompararInt(CondRetEsperada, TST_CondRetAcessoInvalidoVetor, "Acesso Invalido ao vetor de cronogramas.");
            }

            return TST_CompararInt( CondRetEsperada , CondRetObtido, "Retorno errado ao alterar recurso do cronograma" ); 

        } /* fim ativa: Testar CRO Altera Tarefa */

        /* Testar CRO Gerar Cronograma */

        else if ( strcmp(ComandoTeste , GERAR_CRO_CMD) == 0 )
        {
            NumLidos = LER_LerParametros( "ii", &CronogramaObtido, &CondRetEsperada );
            if( NumLidos != 2 )
            {
                return TST_CondRetParm;
            } /* if */

            if (CronogramaObtido < 10 && CronogramaObtido >= 0)
            {
                CondRetObtido = CRO_ImprimeCronograma(cronogramas[CronogramaObtido]);
            }
            else
            {
                return TST_CompararInt(CondRetEsperada, TST_CondRetAcessoInvalidoVetor, "Acesso Invalido ao vetor de cronogramas.");
            }

            return TST_CompararInt( CondRetEsperada , CondRetObtido, "Retorno errado ao gerar o cronograma" ); 

        } /* fim ativa: Testar CRO Gerar Cronograma */

        return TST_CondRetNaoConhec ;	

    } /* Fim fun��o: TCRO Efetuar opera��es de teste espec�ficas para cronograma */

/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/

