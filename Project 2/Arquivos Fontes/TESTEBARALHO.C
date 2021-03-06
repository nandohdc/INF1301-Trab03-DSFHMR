/***************************************************************************
*   $MCI M�dulo de implementa��o: TESTEBARALHO Teste Baralho
*
*  Arquivo gerado:              TESTEBARALHO.c
*  Letras identificadoras:      TSTBARALHO
*
*
*  Projeto: Disciplinas INF 1301
*  Professor: Flavio
*  Autores: ds  - Daniel Siles
*			fh  - Fernando Homem
*			mr  - Mateus Ribeiro
*
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor     Data     Observa��es
*	4.00 ds/fh/mr 27/04/2015 criar linguagem script simb�lica
*       3.00 ds/fh/mr 26/04/2015 uniformiza��o dos exemplos
*       2.00 ds/fh/mr 22/04/2015 unifica��o de todos os m�dulos em um s� projeto
*       1.00 ds/fh/mr 17/04/2015 In�cio do desenvolvimento
*
***************************************************************************/


#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "BaralhoInicial.h"
#include    "Carta.h"
#include    "PilhadeCartas.h"


#define CRIAR_BARALHO_CMD  "=criarbaralho"
#define LIBERAR_BARALHO_CMD  "=liberarbaralho"
#define INICIALIZAR_BARALHO_CMD  "=inicializarbaralho"
#define EMBARALHAR_BARALHO_CMD  "=embaralharbaralho"
#define IMPRIMIR_BARALHO_CMD  "=imprimirbaralho"


BAR_tpBaralho Baralho = NULL;

TST_tpCondRet TST_EfetuarComando(char * ComandoTeste)
{
	BAR_tpCondRet CondRetRecebida;
	BAR_tpCondRet CondRetEsperada;

	int numLidos = -1;
	int numNaipes = 0;


	/* Testar criarBaralho */

	if (strcmp(ComandoTeste, CRIAR_BARALHO_CMD) == 0)
	{

		numLidos = LER_LerParametros("i", &CondRetEsperada);

		if (numLidos != 1){
			return TST_CondRetParm;
		} /* if */

		CondRetRecebida = BAR_criarBaralho(&Baralho);

		return TST_CompararInt(CondRetEsperada, CondRetRecebida, "Erro ao criar a baralho.");

	} /* fim ativa: Testar criarBaralho */

	/* Testar liberarBaralho  */

	else if (strcmp(ComandoTeste, LIBERAR_BARALHO_CMD) == 0)
	{

		numLidos = LER_LerParametros("i", &CondRetEsperada);

		if ((numLidos != 1))
		{
			return TST_CondRetParm;
		} /* if */

		CondRetRecebida = BAR_liberarBaralho(Baralho);

		return TST_CompararInt(CondRetEsperada, CondRetRecebida, "Erro ao destruir a Baralho");

	} /* fim ativa: Testar liberarBaralho */

	/* Testar inicializarBaralho */

	else if (strcmp(ComandoTeste, INICIALIZAR_BARALHO_CMD) == 0)
	{

		numLidos = LER_LerParametros("ii", &numNaipes, &CondRetEsperada);

		if ((numLidos != 2))
		{
			return TST_CondRetParm;
		} /* if */

		CondRetRecebida = BAR_inicializarBaralho(Baralho, numNaipes);

		return TST_CompararInt(CondRetEsperada, CondRetRecebida, "Erro ao inicializar baralho");

	} /* fim ativa: Testar inicializarBaralho */

	/* Testar embaralharBaralho */

	else if (strcmp(ComandoTeste, EMBARALHAR_BARALHO_CMD) == 0)
	{

		numLidos = LER_LerParametros("i", &CondRetEsperada);

		if ((numLidos != 1))
		{
			return TST_CondRetParm;
		} /* if */

		CondRetRecebida = BAR_embaralharBaralho(Baralho);

		return TST_CompararInt(CondRetEsperada, CondRetRecebida, "Erro ao embaralhar o baralho");

	} /* fim ativa: Testar embaralharBaralho */

	/* Testar imprimeBaralho */

	else if (strcmp(ComandoTeste, IMPRIMIR_BARALHO_CMD) == 0)
	{

		numLidos = LER_LerParametros("i", &CondRetEsperada);

		if ((numLidos != 1))
		{
			return TST_CondRetParm;
		} /* if */

		CondRetRecebida = BAR_imprimeBaralho(Baralho);

		return TST_CompararInt(CondRetEsperada, CondRetRecebida, "Erro ao retornar Naipe da Carta.");

	} /* fim ativa: Testar imprimeBaralho */

		

	return TST_CondRetNaoConhec;

} /* Fim fun��o: TESTEBARALHO Efetuar opera��es de teste espec�ficas para Baralho */

/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/