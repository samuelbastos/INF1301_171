/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo Recurso
*
*  Arquivo gerado:              RECURSO.C
*  Letras identificadoras:      REC
*
*  Projeto: Disciplinas INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: mv - Mauricio Pedro Silva Gon�alves Vieira
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*       1.00   mp   01/05/2017 In�cio do desenvolvimento
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>
#include   <string.h>

#define RECURSO_OWN
#include "RECURSO.H"
#undef RECURSO_OWN

#define TRUE 1
#define FALSE 0

/***********************************************************************
*
*  $TC Tipo de dados: REC Variavel que controla o id de cada tarefa
*
***********************************************************************/

static int idAtual = 0;

/***********************************************************************
*
*  $TC Tipo de dados: REC Descritor do Recurso
*
*
*  $ED Descri��o do tipo
*     Descreve a organiza��o de um Recurso
*
***********************************************************************/

				typedef struct tgRecurso {

								char * nome;
												/*	Nome do Recurso */

								int estaDisponivel;
											/*
												*	Vari�vel que indica se o Recurso est� atualmente ligado a
												*	alguma tarefa, seu valor ser� 1 quando ela estiver dispon�vel
												*	e 0 quando n�o estiver
												*/

				} tpRecurso ;


/***********************************************************************
*
*  $TC Tipo de dados: REC Descritor da cabe�a de um recurso
*
*
*  $ED Descri��o do tipo
*     A cabe�a de um recurso � o ponto de acesso para um determinado recurso.
*
***********************************************************************/

				typedef struct tcRecurso {

								int id;
												/* Sequencial que identifica unicamente um Recurso */

								tpRecurso * recurso ;
												/* Ponteiro para a estrutura recurso */

				} tcRecurso ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: REC Criar Recurso
*  ****/

				REC_tpCondRet REC_CriarRecurso (tcRecurso ** ptRecurso, char * novoNome)
				{

								tcRecurso * cabecaRecurso = (*ptRecurso);
								tpRecurso * pRecurso;
								if (novoNome == NULL || strcmp(novoNome, "") == 0 || strcmp(novoNome, " ") == 0)
								{
												return REC_CondRetNomeInvalido;
								} /* if */

								if (cabecaRecurso != NULL && cabecaRecurso->recurso != NULL)
								{
												REC_DestruirRecurso(ptRecurso);
								} /* if */

								cabecaRecurso = (tcRecurso *) malloc (sizeof(tcRecurso));
								if (cabecaRecurso == NULL)
								{
												return REC_CondRetFaltouMemoria;
								} /* if */

								pRecurso = (tpRecurso *)malloc(sizeof(tpRecurso));
								if (pRecurso == NULL)
								{
												return REC_CondRetFaltouMemoria;
								} /* if */
								pRecurso->nome = (char*) malloc (strlen(novoNome)*sizeof(char) + 1);
								if (pRecurso->nome == NULL)
								{
												return REC_CondRetFaltouMemoria;
								} /* if */
								strcpy(pRecurso->nome, novoNome);

								pRecurso->estaDisponivel = FALSE;

								cabecaRecurso->id = idAtual;
								idAtual++;
								cabecaRecurso->recurso = pRecurso;

								(*ptRecurso) = cabecaRecurso;

								return REC_CondRetOK;

				} /* Fim fun��o: REC Criar Recurso */

/***************************************************************************
*
*  Fun��o: REC Destruir Recurso
*  ****/

				void REC_DestruirRecurso (tcRecurso ** ptRecurso)
				{
								tcRecurso * cabecaRecurso = (*ptRecurso);
	  
								if (ptRecurso != NULL)
								{
												if (cabecaRecurso != NULL)
												{
																if (cabecaRecurso->recurso != NULL)
																{
																				free(cabecaRecurso->recurso->nome);
																				free(cabecaRecurso->recurso);
																} /* if */
																free(cabecaRecurso);
																(*ptRecurso) = NULL;
												} /* if */
								} /* if */

				} /* Fim fun��o: REC Destruir Recurso */

/***************************************************************************
*
*  Fun��o: REC Alterar nome do Recurso
*  ****/

	REC_tpCondRet REC_AlterarNome(tcRecurso * ptRecurso, char * novoNome)
	{
		tpRecurso * pRecurso;
		if (ptRecurso == NULL || ptRecurso->recurso == NULL)
		{
			return REC_CondRetRecursoNaoExiste;
		} /* if */

		pRecurso = ptRecurso->recurso;

		if (novoNome == NULL || strcmp(novoNome, "") == 0 || strcmp(novoNome, " ") == 0)
		{
			return REC_CondRetNomeInvalido;
		} /* if */

		free(pRecurso->nome);
		pRecurso->nome = (char*)malloc(strlen(novoNome) * sizeof(char) + 1);
		if (pRecurso->nome == NULL)
		{
			return REC_CondRetFaltouMemoria;
		} /* if */
		strcpy(pRecurso->nome, novoNome);

		return REC_CondRetOK;

	} /* Fim fun��o: REC Alterar nome do Recurso */

/***************************************************************************
*
*  Fun��o: REC Marca o recurso como ocupado
*  ****/

	REC_tpCondRet REC_MarcarComoOcupada(tcRecurso * ptRecurso)
	{
		tpRecurso * pRecurso;
		if (ptRecurso == NULL)
		{
			return REC_CondRetRecursoNaoExiste;
		} /* if */

		pRecurso = ptRecurso->recurso;
	   
		ptRecurso->recurso->estaDisponivel = FALSE;

		return REC_CondRetOK;

	} /* Fim fun��o: REC Marca o recurso como ocupado */

/***************************************************************************
*
*  Fun��o: REC Marca recurso como dispon�vel
*  ****/

   REC_tpCondRet REC_MarcarComoDisponivel(tcRecurso * ptRecurso)
   {
	   if (ptRecurso == NULL || ptRecurso->recurso == NULL)
	   {
		   return REC_CondRetRecursoNaoExiste;
	   } /* if */

	   ptRecurso->recurso->estaDisponivel = TRUE;

	   return REC_CondRetOK;

   } /* Fim fun��o: REC Marca recurso como dispon�vel */

/***************************************************************************
*
*  Fun��o: REC Consulta o Id do recurso
*  ****/

   REC_tpCondRet REC_ConsultarId(tcRecurso * ptRecurso, int * id)
   {
	   if (ptRecurso == NULL || ptRecurso->recurso == NULL)
	   {
		   return REC_CondRetRecursoNaoExiste;
	   } /* if */

	   (*id) = ptRecurso->id;

	   return REC_CondRetOK;

   } /* Fim fun��o: REC Consulta o Id do recurso */

/***************************************************************************
*
*  Fun��o: REC Consulta o nome do recurso
*  ****/

   REC_tpCondRet REC_ConsultarNome(tcRecurso * ptRecurso, char ** pNome)
   {
	   char * nome = (*pNome);
	   if (ptRecurso == NULL || ptRecurso->recurso == NULL)
	   {
		   return REC_CondRetRecursoNaoExiste;
	   } /* if */

	   free(nome);
	   nome = (char*)malloc(strlen(ptRecurso->recurso->nome) * sizeof(char) + 1);
	   if (nome == NULL)
	   {
		   return REC_CondRetFaltouMemoria;
	   } /* if */
	   strcpy(nome, ptRecurso->recurso->nome);

	   (*pNome) = nome;

	   return REC_CondRetOK;

   } /* Fim fun��o: REC Consulta o nome do recurso */

/***************************************************************************
*
*  Fun��o: REC Consulta a disponibilidade do Recurso
*  ****/

   REC_tpCondRet REC_ConsultarDisponibilidade(tcRecurso * ptRecurso, int * estaDisponivel)
   {
	   if (ptRecurso == NULL || ptRecurso->recurso == NULL)
	   {
		   return REC_CondRetRecursoNaoExiste;
	   } /* if */

	   (*estaDisponivel) = ptRecurso->recurso->estaDisponivel;

	   return REC_CondRetOK;

   } /* Fim fun��o: REC Consulta a disponibilidade do Recurso */

/***************************************************************************
*
*  Fun��o: REC Imprime informa��es do Recurso
*  ****/

   REC_tpCondRet REC_ImprimeRecurso(tcRecurso * ptRecurso)
   {
	   if (ptRecurso == NULL || ptRecurso->recurso == NULL)
	   {
		   return REC_CondRetRecursoNaoExiste;
	   } /* if */

	   printf("Recurso: %s\nId: %d\n", ptRecurso->recurso->nome, ptRecurso->id);

	   return REC_CondRetOK;

   } /* Fim fun��o: REC Imprime informa��es do Recurso */


#undef TRUE
#undef FALSE

/********** Fim do m�dulo de implementa��o: M�dulo Recurso **********/

