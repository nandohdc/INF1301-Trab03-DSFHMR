/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo �rvore
*
*  Arquivo gerado:              ARVORE.C
*  Letras identificadoras:      ARV
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: avs - Arndt von Staa
*			ds  - Daniel Siles
*			fh  - Fernando Homem
*			mr - Mateus Ribeiro
*
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor     Data     Observa��es
*		4.00 ds/fh/mr 25/03/2015 Cria��o da fun��o Costureira	
*       3.00   avs    28/02/2003 Uniformiza��o da interface das fun��es e
*                                de todas as condi��es de retorno.
*       2.00   avs    03/08/2002 Elimina��o de c�digo duplicado, reestrutura��o
*       1.00   avs    15/08/2001 In�cio do desenvolvimento
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>

#define ARVORE_OWN
#include "ARVORE.H"
#undef ARVORE_OWN

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor do n� da �rvore
*
*
*  $ED Descri��o do tipo
*     Descreve a organiza��o do n�
*
***********************************************************************/

   typedef struct tgNoArvore {

         struct tgNoArvore * pNoPai ;
               /* Ponteiro para pai
               *
               *$EED Assertivas estruturais
               *   � NULL sse o n� � raiz
               *   Se n�o for raiz, um de pNoEsq ou pNoDir de pNoPai do n�
               *   corrente apontam para o n� corrente */

         struct tgNoArvore * pNoEsq ;
               /* Ponteiro para filho � esquerda
               *
               *$EED Assertivas estruturais
               *   se pNoEsq do n� X != NULL ent�o pNoPai de pNoEsq aponta para o n� X */

         struct tgNoArvore * pNoDir ;
               /* Ponteiro para filho � direita
               *
               *$EED Assertivas estruturais
               *   se pNoDir do n� X != NULL ent�o pNoPai de pNoDir aponta para o n� X */
		 
		 struct tgNoArvore * pNoCostura;
				/* Ponteiro para costurar as folhas*/

		 char pNoChave;
				/*Ponteiro auxiliar para armazenar as folhas anteriores*/

         char Valor ;
               /* Valor do n� */

   } tpNoArvore ;

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor da cabe�a de uma �rvore
*
*
*  $ED Descri��o do tipo
*     A cabe�a da �rvore � o ponto de acesso para uma determinada �rvore.
*     Por interm�dio da refer�ncia para o n� corrente e do ponteiro
*     pai pode-se navegar a �rvore sem necessitar de uma pilha.
*     Pode-se, inclusive, operar com a �rvore em forma de co-rotina.
*
***********************************************************************/

   typedef struct tgArvore {

         tpNoArvore * pNoRaiz ;
               /* Ponteiro para a raiz da �rvore */

         tpNoArvore * pNoCorr ;
               /* Ponteiro para o n� corrente da �rvore */

   } tpArvore ;

/*****  Dados encapsulados no m�dulo  *****/

      static tpArvore * pArvore = NULL ;
            /* Ponteiro para a cabe�a da �rvore */

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static tpNoArvore * CriarNo( char ValorParm ) ;

   static ARV_tpCondRet CriarNoRaiz( char ValorParm ) ;

   static void DestroiArvore( tpNoArvore * pNo ) ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: ARV Criar �rvore
*  ****/

   ARV_tpCondRet ARV_CriarArvore( void )
   {

      if ( pArvore != NULL )
      {
         ARV_DestruirArvore( ) ;
      } /* if */

      pArvore = ( tpArvore * ) malloc( sizeof( tpArvore )) ;
      if ( pArvore == NULL )
      {
         return ARV_CondRetFaltouMemoria ;
      } /* if */

      pArvore->pNoRaiz = NULL ;
      pArvore->pNoCorr = NULL ;

      return ARV_CondRetOK ;

   } /* Fim fun��o: ARV Criar �rvore */

/***************************************************************************
*
*  Fun��o: ARV Destruir �rvore
*  ****/

   void ARV_DestruirArvore( void )
   {

      if ( pArvore != NULL )
      {
         if ( pArvore->pNoRaiz != NULL )
         {
            DestroiArvore( pArvore->pNoRaiz ) ;
         } /* if */
         free( pArvore ) ;
         pArvore = NULL ;
      } /* if */

   } /* Fim fun��o: ARV Destruir �rvore */

/***************************************************************************
*
*  Fun��o: ARV Adicionar filho � esquerda
*  ****/

   ARV_tpCondRet ARV_InserirEsquerda( char ValorParm )
   {

      ARV_tpCondRet CondRet ;

      tpNoArvore * pCorr ;
      tpNoArvore * pNo ;

      /* Tratar vazio, esquerda */

         CondRet = CriarNoRaiz( ValorParm ) ;
         if ( CondRet != ARV_CondRetNaoCriouRaiz )
         {
            return CondRet ;
         } /* if */

      /* Criar n� � esquerda de folha */

         pCorr = pArvore->pNoCorr ;
         if ( pCorr == NULL )
         {
            return ARV_CondRetErroEstrutura ;
         } /* if */
               
         if ( pCorr->pNoEsq == NULL )
         {
            pNo = CriarNo( ValorParm ) ;
            if ( pNo == NULL )
            {
               return ARV_CondRetFaltouMemoria ;
            } /* if */
            pNo->pNoPai      = pCorr ;
            pCorr->pNoEsq    = pNo ;
            pArvore->pNoCorr = pNo ;

            return ARV_CondRetOK ;
         } /* if */

      /* Tratar n�o folha � esquerda */

         return ARV_CondRetNaoEhFolha ;

   } /* Fim fun��o: ARV Adicionar filho � esquerda */

/***************************************************************************
*
*  Fun��o: ARV Adicionar filho � direita
*  ****/

   ARV_tpCondRet ARV_InserirDireita( char ValorParm )
   {

      ARV_tpCondRet CondRet ;

      tpNoArvore * pCorr ;
      tpNoArvore * pNo ;

      /* Tratar vazio, direita */

         CondRet = CriarNoRaiz( ValorParm ) ;
         if ( CondRet != ARV_CondRetNaoCriouRaiz )
         {
            return CondRet ;
         } /* if */

      /* Criar n� � direita de folha */

         pCorr = pArvore->pNoCorr ;
         if ( pCorr == NULL )
         {
            return ARV_CondRetErroEstrutura ;
         } /* if */

         if ( pCorr->pNoDir == NULL )
         {
            pNo = CriarNo( ValorParm ) ;
            if ( pNo == NULL )
            {
               return ARV_CondRetFaltouMemoria ;
            } /* if */
            pNo->pNoPai      = pCorr ;
            pCorr->pNoDir    = pNo ;
            pArvore->pNoCorr = pNo ;

            return ARV_CondRetOK ;
         } /* if */

      /* Tratar n�o folha � direita */

         return ARV_CondRetNaoEhFolha ;

   } /* Fim fun��o: ARV Adicionar filho � direita */

/***************************************************************************
*
*  Fun��o: ARV Ir para n� pai
*  ****/

   ARV_tpCondRet ARV_IrPai( void )
   {

      if ( pArvore == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */
      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      if ( pArvore->pNoCorr->pNoPai != NULL )
      {
         pArvore->pNoCorr = pArvore->pNoCorr->pNoPai ;
         return ARV_CondRetOK ;
      } else {
         return ARV_CondRetNohEhRaiz ;
      } /* if */

   } /* Fim fun��o: ARV Ir para n� pai */

/***************************************************************************
*
*  Fun��o: ARV Ir para n� � esquerda
*  ****/

   ARV_tpCondRet ARV_IrNoEsquerda( void )
   {

      if ( pArvore == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */

      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      if ( pArvore->pNoCorr->pNoEsq == NULL )
      {
         return ARV_CondRetNaoPossuiFilho ;
      } /* if */

      pArvore->pNoCorr = pArvore->pNoCorr->pNoEsq ;
      return ARV_CondRetOK ;

   } /* Fim fun��o: ARV Ir para n� � esquerda */

/***************************************************************************
*
*  Fun��o: ARV Ir para n� � direita
*  ****/

   ARV_tpCondRet ARV_IrNoDireita( void )
   {

      if ( pArvore == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */

      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      if ( pArvore->pNoCorr->pNoDir == NULL )
      {
         return ARV_CondRetNaoPossuiFilho ;
      } /* if */

      pArvore->pNoCorr = pArvore->pNoCorr->pNoDir ;
      return ARV_CondRetOK ;

   } /* Fim fun��o: ARV Ir para n� � direita */

/***************************************************************************
*
*  Fun��o: ARV Obter valor corrente
*  ****/

   ARV_tpCondRet ARV_ObterValorCorr( char * ValorParm )
   {

      if ( pArvore == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */
      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */
      * ValorParm = pArvore->pNoCorr->Valor ;

      return ARV_CondRetOK ;

   } /* Fim fun��o: ARV Obter valor corrente */


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: ARV Criar n� da �rvore
*
*  $FV Valor retornado
*     Ponteiro para o n� criado.
*     Ser� NULL caso a mem�ria tenha se esgotado.
*     Os ponteiros do n� criado estar�o nulos e o valor � igual ao do
*     par�metro.
*
***********************************************************************/

   tpNoArvore * CriarNo( char ValorParm )
   {

      tpNoArvore * pNo ;

      pNo = ( tpNoArvore * ) malloc( sizeof( tpNoArvore )) ;
      if ( pNo == NULL )
      {
         return NULL ;
      } /* if */

      pNo->pNoPai = NULL ;
      pNo->pNoEsq = NULL ;
      pNo->pNoDir = NULL ;
	  pNo->Valor  = ValorParm ;
      pNo->pNoChave  = ValorParm ;
      return pNo ;

   } /* Fim fun��o: ARV Criar n� da �rvore */


/***********************************************************************
*
*  $FC Fun��o: ARV Criar n� raiz da �rvore
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetFaltouMemoria
*     ARV_CondRetNaoCriouRaiz
*
***********************************************************************/

   ARV_tpCondRet CriarNoRaiz( char ValorParm )
   {

      ARV_tpCondRet CondRet ;
      tpNoArvore * pNo ;

      if ( pArvore == NULL )
      {
         CondRet = ARV_CriarArvore( ) ;

         if ( CondRet != ARV_CondRetOK )
         {
            return CondRet ;
         } /* if */
      } /* if */

      if ( pArvore->pNoRaiz == NULL )
      {
         pNo = CriarNo( ValorParm ) ;
         if ( pNo == NULL )
         {
            return ARV_CondRetFaltouMemoria ;
         } /* if */
         pArvore->pNoRaiz = pNo ;
         pArvore->pNoCorr = pNo ;

         return ARV_CondRetOK ;
      } /* if */

      return ARV_CondRetNaoCriouRaiz ;

   } /* Fim fun��o: ARV Criar n� raiz da �rvore */


/***********************************************************************
*
*  $FC Fun��o: ARV Destruir a estrutura da �rvore
*
*  $EAE Assertivas de entradas esperadas
*     pNoArvore != NULL
*
***********************************************************************/

   void DestroiArvore( tpNoArvore * pNo )
   {

      if ( pNo->pNoEsq != NULL )
      {
         DestroiArvore( pNo->pNoEsq ) ;
      } /* if */

      if ( pNo->pNoDir != NULL )
      {
         DestroiArvore( pNo->pNoDir ) ;
      } /* if */

      free( pNo ) ;

   } /* Fim fun��o: ARV Destruir a estrutura da �rvore */

/***********************************************************************
*
*  $FC Fun��o: ARV Conta Folhas
*
*  $EAE Assertivas de entradas esperadas
*     pNoArvore != NULL
*
***********************************************************************/
   int ARV_ContaFolhas(tpNoArvore * arvore){
	   //Verifica se a arvore n�o est� vazia
	   if(arvore == NULL){
		   return 0;
	   }
	   //Varifica se o n� da �rvore � uma folha
	   else if((arvore->pNoEsq == NULL) && (arvore->pNoDir == NULL)){
		   return 1;
	   }
	   
	   else{
		   return ((ARV_ContaFolhas(arvore->pNoEsq)) + (ARV_ContaFolhas(arvore->pNoDir)));
	   }
   } /* Fim fun��o: ARV Conta Folhas */
   
/***********************************************************************
*
*  $FC Fun��o: ARV Pega Chave
*
*  $EAE Assertivas de entradas esperadas
*     pNoArvore != NULL
*
***********************************************************************/
   char* ARV_PegaChave(tpNoArvore *arvore, char *vetorA, char *indice){
	   if(arvore->pNoEsq != NULL){
		   ARV_PegaChave(arvore->pNoEsq, vetorA, indice);
	   }
	   if(arvore->pNoDir != NULL){
		   ARV_PegaChave(arvore->pNoDir, vetorA, indice);
	   }
	   //Acha folha, retorna a chave e armazena no vetor
	   if(arvore->pNoDir == NULL && arvore->pNoEsq == NULL){
		   vetorA[*indice] = arvore->pNoChave;
		   *indice = *indice + 1;

	   }
	   return vetorA;
   } /* Fim fun��o: ARV Pega Chave */

  /***********************************************************************
*
*  $FC Fun��o: ARV Ordena Vetor
*
***********************************************************************/
 
   void ARV_OrdenaVetor(char* VetorA, int nfolhas){
	   int fim, i;
	   for( fim = nfolhas-1 ; fim > 0 ; fim--){
		   for(i = 0 ; i < fim ; i++){
			   if(VetorA[i] > VetorA[i+1]){
			   int temp = VetorA[i];
			   VetorA[i] = VetorA[i+1];
			   VetorA[i+1] = temp;
			   }
		   }
	   }
   } /* Fim fun��o: ARV Ordena Vetor */
   
   /***********************************************************************
*
*  $FC Fun��o: ARV Busca e Costura
*
*  $EAE Assertivas de entradas esperadas
*     pNoArvore != NULL
*
***********************************************************************/


   void ARV_BuscaECostura(tpNoArvore * arvore, char elemento){
	   
	   if (arvore->pNoEsq != NULL){
		   ARV_BuscaECostura(arvore->pNoEsq, elemento);
	   }

	   if (arvore->pNoDir != NULL){
		   ARV_BuscaECostura(arvore->pNoDir, elemento);
	   }
	   //Encontra uma folha com o elemento procurado e realiza a costura
	   if ((arvore->pNoDir == NULL) && (arvore->pNoEsq == NULL) && (arvore->pNoChave == elemento)){
		   arvore->pNoCostura = pArvore->pNoCorr;
		   pArvore->pNoCorr = arvore;
	   }
   } /* Fim fun��o: ARV Busca e Costura */

   /***********************************************************************
*
*  $FC Fun��o: ARV Imprime
*
*  $EAE Assertivas de entradas esperadas
*     pNoArvore != NULL
*
***********************************************************************/
   void ARV_Imprime(tpNoArvore * arvore, char elemento, int nfolhas){
	   
	   int i;

	   if (arvore->pNoEsq != NULL){
		   ARV_Imprime(arvore->pNoEsq, elemento, nfolhas);
	   }
	   if (arvore->pNoDir != NULL){
		   ARV_Imprime(arvore->pNoDir, elemento, nfolhas);
	   }
	   if ((arvore->pNoDir == NULL) && (arvore->pNoEsq == NULL) && (arvore->pNoChave == elemento)){
		   //Encontra a folha que cont�m o primeiro elemento a ser costura e segue a costura pelo ponteiro pNoCostura
		   for (i = 0; i < nfolhas; i++)
		   {
			   printf("%c ", arvore->pNoChave);
			   arvore = arvore->pNoCostura;
		   }
	   }
	   
   } /* Fim fun��o: ARV Imprime */

/***********************************************************************
*
*  $FC Fun��o: ARV Costureira
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetFaltouMemoria
*     ARV_CondRetNaoCriouRaiz
*
***********************************************************************/
   ARV_tpCondRet ARV_Costureira(void){
	   int nfolhas = 0, i = 0;
	   char indice = 0;
	   char *VetorA;

	    if (pArvore == NULL){
		   return ARV_CondRetArvoreNaoExiste;
	   }

	   if (pArvore->pNoRaiz == NULL){
		   return ARV_CondRetArvoreVazia;
	   }   

	   //Recebe o numero de folhas da �rvore
	   nfolhas = ARV_ContaFolhas(pArvore->pNoRaiz);

	   VetorA = (char*) malloc (nfolhas * sizeof(char));

	   if(VetorA == NULL){
		   return ARV_CondRetFaltouMemoria;
	   }
		
	   //Preenche o vetor com as chaves das folhas
	   VetorA = ARV_PegaChave(pArvore->pNoRaiz, VetorA, &indice);
	   
	   //Ordena o vetor em ordem alfanum�rica
	   ARV_OrdenaVetor(VetorA, nfolhas);

	   pArvore->pNoCorr = NULL;

	   //Costura as folhas da �rvore partindo do �ltimo elemento a ser costurado
	   //O �ltimo aponta para NULL
	   //Os demais apontam para o que foi costurado anteriormente
	   for (i = nfolhas - 1; i >= 0; i--){
		   ARV_BuscaECostura(pArvore->pNoRaiz, VetorA[i]);
	   }

	   printf("\n");

	   //Imprime a chave das folhas seguindo a costura (em �rdem alfanum�rica)
	   ARV_Imprime(pArvore->pNoRaiz, VetorA[0], nfolhas);

	   free(VetorA);

	   return ARV_CondRetOK;
   } /* Fim fun��o: ARV Costureira */

      
/********** Fim do m�dulo de implementa��o: M�dulo �rvore **********/

