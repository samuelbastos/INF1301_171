/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo de teste espec�fico
*
*  Arquivo gerado:              TESTREC.C
*  Letras identificadoras:      TREC
*
*  Projeto: Disciplinas INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: mp - Mauricio Pedro Silva Gon�alves Vieira
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*       1.00   mp    01/05/2017 In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�dulo cont�m as fun��es espec�ficas para o teste do
*     m�dulo Recurso. Ilustra como redigir um interpretador de comandos
*     de teste espec�ficos utilizando o arcabou�o de teste para C.
*
*  $EIU Interface com o usu�rio pessoa
*     Comandos de teste espec�ficos para testar o m�dulo recurso:
*
*     "=criar"  <i> <string> 
*				- chama a fun��o REC_CriarRecurso( <i>, <string> )

*     "=destroi" <i>	
*				- chama a fun��o REC_DestruirRecurso( <i> )

	  "=altnome" <i> <string>
				- chama a fun��o para alterar o nome REC_AlterarNome( <i>, <string> )
*
*	  Obs: nota��o: <i> � o valor do par�metro que se encontra no comando
*						de teste que � um inteiro e significa qual das ta-
*						refas criadas pelo m�dulo de testes o comando est�
*						se referindo
*					<string> � o valor do par�metro que se encontra no 
*							 comando de teste que � uma sequencia de 
*							 caracteres que simboliza o nome do recurso
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include	<stdlib.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"

#include    "recurso.h"

/* Tabela dos nomes dos comandos de teste espec�ficos */

#define     CRIAR_REC_CMD			"=criar"
#define     DESTROI_CMD				"=destruir"
#define		ALTERAR_NOME_CMD		"=altnome"
#define		MARCAR_OCUPADO_CMD		"=marcocup"
#define		MARCAR_DISPONIVEL_CMD	"=marcdisp"
#define		CONSULTA_ID_CMD			"=conid"
#define		CONSULTA_NOME_CMD		"=connome"
#define		CONSULTA_DISP_CMD		"=condisp"

#define		STRING_DIM 100

/* Vetor de recursos para serem usados nos testes */

tcRecurso * recursos[10];


/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TREC Efetuar opera��es de teste espec�ficas para recurso
*
*  $ED Descri��o da fun��o
*     Efetua os diversos comandos de teste espec�ficos para o m�dulo
*     recurso sendo testado.
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

      REC_tpCondRet CondRetObtido   = REC_CondRetOK ;
      REC_tpCondRet CondRetEsperada = REC_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

      char ValorEsperado = '?'  ;
      char ValorObtido   = '!'  ;
      char ValorDado     = '\0' ;

	  int RecursoObtido = 11;
	  int idObtido;
	  int idConsultado;
	  int DisponibilidadeObtida;
	  int DisponibilidadeConsultada;
	  char NomeObtido[STRING_DIM];
	  char * NomeConsultado = (char*)malloc(sizeof(char) * 100);

      int  NumLidos = -1 ;

      TST_tpCondRet Ret ;

      /* Testar REC Criar Recurso */

         if ( strcmp( ComandoTeste , CRIAR_REC_CMD) == 0 )
         {

            NumLidos = LER_LerParametros( "isi" ,
                               &RecursoObtido, NomeObtido, &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

			if (RecursoObtido < 10 && RecursoObtido >= 0)
			{
				CondRetObtido = REC_CriarRecurso(&recursos[RecursoObtido], NomeObtido);
			}
			else
			{
				return TST_CompararInt(CondRetEsperada, TST_CondRetAcessoInvalidoVetor,
					"Acesso Invalido ao vetor de recursos.");
			}

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar recurso." );

         } /* fim ativa: Testar REC Criar recurso */

      /* Testar REC Destruir recurso */

         else if ( strcmp( ComandoTeste , DESTROI_CMD ) == 0 )
         {

			NumLidos = LER_LerParametros("i",
								&RecursoObtido);
			if (NumLidos != 1)
			{
				return TST_CondRetParm;
			} /* if */

			if (RecursoObtido < 10 && RecursoObtido >= 0)
			{
				REC_DestruirRecurso(&recursos[RecursoObtido]);
			}
			else
			{
				return TST_CompararInt(TST_CondRetOK, TST_CondRetAcessoInvalidoVetor,
					"Acesso Invalido ao vetor de recursos.");
			}

            return TST_CondRetOK ;

         } /* fim ativa: Testar REC Destruir recurso */

	/* Testar REC Alterar nome do recurso */

         else if ( strcmp( ComandoTeste , ALTERAR_NOME_CMD ) == 0 )
         {

			NumLidos = LER_LerParametros("isi",
								&RecursoObtido, NomeObtido, &CondRetEsperada);
			if (NumLidos != 3)
			{
				return TST_CondRetParm;
			} /* if */

			if (RecursoObtido < 10 && RecursoObtido >= 0)
			{
				CondRetObtido = REC_AlterarNome(recursos[RecursoObtido], NomeObtido);
			}
			else
			{
				return TST_CompararInt(TST_CondRetOK, TST_CondRetAcessoInvalidoVetor,
					"Acesso Invalido ao vetor de recursos.");
			}

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado alterar nome." );

         } /* fim ativa: REC Alterar nome do recurso */

	/* Testar REC Marca o recurso como ocupado */

         else if ( strcmp( ComandoTeste , MARCAR_OCUPADO_CMD ) == 0 )
         {

			NumLidos = LER_LerParametros("ii",
								&RecursoObtido, &CondRetEsperada);
			if (NumLidos != 2)
			{
				return TST_CondRetParm;
			} /* if */

			if (RecursoObtido < 10 && RecursoObtido >= 0)
			{
				CondRetObtido = REC_MarcarComoOcupada(recursos[RecursoObtido]);
			}
			else
			{
				return TST_CompararInt(TST_CondRetOK, TST_CondRetAcessoInvalidoVetor,
					"Acesso Invalido ao vetor de recursos.");
			}

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao marcar recurso como ocupado" );

         } /* fim ativa: REC Marca o recurso como ocupado */

	/* Testar REC Marca recurso como dispon�vel */

         else if ( strcmp( ComandoTeste , MARCAR_DISPONIVEL_CMD ) == 0 )
         {

			NumLidos = LER_LerParametros("ii",
								&RecursoObtido, &CondRetEsperada);
			if (NumLidos != 2)
			{
				return TST_CondRetParm;
			} /* if */

			if (RecursoObtido < 10 && RecursoObtido >= 0)
			{
				CondRetObtido = REC_MarcarComoDisponivel(recursos[RecursoObtido]);
			}
			else
			{
				return TST_CompararInt(TST_CondRetOK, TST_CondRetAcessoInvalidoVetor,
					"Acesso Invalido ao vetor de recursos.");
			}

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao marcar recurso como disponivel" );

         } /* fim ativa: REC Marca recurso como dispon�vel */

	/* Testar REC Consulta o Id do recurso */

         else if ( strcmp( ComandoTeste , CONSULTA_ID_CMD ) == 0 )
         {

			NumLidos = LER_LerParametros("iii",
								&RecursoObtido, &idObtido, &CondRetEsperada);
			if (NumLidos != 3)
			{
				return TST_CondRetParm;
			} /* if */

			if (RecursoObtido < 10 && RecursoObtido >= 0)
			{
				CondRetObtido = REC_ConsultarId(recursos[RecursoObtido], &idConsultado);
				if (CondRetEsperada == REC_CondRetOK && idObtido != idConsultado)
				{
					return TST_CompararInt(TST_CondRetOK, TST_CondRetErro,
						"Id encontrado n�o foi o esperado.");
				}
			}
			else
			{
				return TST_CompararInt(TST_CondRetOK, TST_CondRetAcessoInvalidoVetor,
					"Acesso Invalido ao vetor de recursos.");
			}

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao consultar o id." );

         } /* fim ativa: REC Consulta o Id do recurso */

	/* Testar REC Consulta o nome do recurso */

         else if ( strcmp( ComandoTeste , CONSULTA_NOME_CMD ) == 0 )
         {

			NumLidos = LER_LerParametros("isi",
								&RecursoObtido, NomeObtido, &CondRetEsperada);
			if (NumLidos != 3)
			{
				return TST_CondRetParm;
			} /* if */

			if (RecursoObtido < 10 && RecursoObtido >= 0)
			{
				CondRetObtido = REC_ConsultarNome(recursos[RecursoObtido], &NomeConsultado);
				if (CondRetEsperada == REC_CondRetOK && strcmp(NomeConsultado,NomeObtido) != 0)
				{
					return TST_CompararInt(TST_CondRetOK, TST_CondRetErro,
						"Nome obtido n�o � o mesmo do encontrado.");
				}
			}
			else
			{
				return TST_CompararInt(TST_CondRetOK, TST_CondRetAcessoInvalidoVetor,
					"Acesso Invalido ao vetor de recursos.");
			}

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao consultar nome." );

         } /* fim ativa: REC Consulta o nome do recurso */

	/* Testar REC Consulta a disponibilidade do Recurso */

         else if ( strcmp( ComandoTeste , CONSULTA_DISP_CMD ) == 0 )
         {

			NumLidos = LER_LerParametros("iii",
								&RecursoObtido, &DisponibilidadeObtida, &CondRetEsperada);
			if (NumLidos != 3)
			{
				return TST_CondRetParm;
			} /* if */

			if (RecursoObtido < 10 && RecursoObtido >= 0)
			{
				CondRetObtido = REC_ConsultarDisponibilidade(recursos[RecursoObtido], &DisponibilidadeConsultada);
				if (CondRetEsperada == REC_CondRetOK && DisponibilidadeObtida != DisponibilidadeConsultada)
				{
					return TST_CompararInt(TST_CondRetOK, TST_CondRetErro,
						"Disponibilidade encontrada n�o foi a esperada.");
				}
			}
			else
			{
				return TST_CompararInt(TST_CondRetOK, TST_CondRetAcessoInvalidoVetor,
					"Acesso Invalido ao vetor de recursos.");
			}

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao consultar a disponibilidade." );

         } /* fim ativa: REC Consulta a disponibilidade do Recurso */

      return TST_CondRetNaoConhec ;

   } /* Fim fun��o: TREC Efetuar opera��es de teste espec�ficas para recurso */

/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/

