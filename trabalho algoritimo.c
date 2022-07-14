#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int
tamanho ()
{
  int tam, erro;
  int certo = 1;
  printf ("\ninforme um numero maior ou igual a  16 e que tenha raiz:\n");	//informa o tamnho do dna a ser analisado 
  scanf ("%i", &tam);
  do
    {
      if (tam != 0 && tam >= 16)	// confere o tamnho do dna se e maior que 16 
	{
	  for (int r = 0; r < tam; r++)
	    {
	      if (r * r == tam)
		{
		  certo = 0;
		}
	    }
	}
    }
  while (certo == 1 && tam > 0);
  return tam;
}

int
Raiz (int tam)
{
  int raiz = sqrt (tam);	//faz a raiz do tamnho do dna 
  return raiz;
}


void
armazena (int tam, char seq[tam])	// armazena os dados do dna A T C G 
{
  if (tam > 0)
    {
      printf ("digite somente  A,G,T,C");
      printf ("\nA sequencia de dna para ser analisada:\n");
      scanf ("%s", seq);
    }
}



void
verificaTamLet (int tam, char seq[tam])	// verificaC'C#o do tamnho da letra 
{
  int tamanho, erro;
  if (tam > 0)
    {
      do
	{
	  tamanho = strlen (seq);	// utiliza a funC'C#o strlen para percorrer toda a matriz 
	  erro = 0;
	  if (tamanho != tam)	// verifica se o numero de letras digitados pelo usuario esta igual ao tamnho escolhido 
	    {
	      printf ("\n a sequencia deve possuir somente  %i letras", tam);
	      printf ("\ndigite novamente\n\n");
	      scanf ("%s", seq);
	    }
	  for (int i = 0; i < tam && tamanho == tam; i++)	// percorre a matriz verificando se possui alguma letra diferente ou minuscula 
	    {
	      if (seq[i] != 'a' && seq[i] != 't' && seq[i] != 'c'
		  && seq[i] != 'g' && seq[i] != 'A' && seq[i] != 'T'
		  && seq[i] != 'C' && seq[i] != 'G')
		{
		  erro = erro + 1;
		  printf ("\n contem um erro na %iB* letra, (%c),\n",	// informa onde possui o erro e onde esta 
			  i + 1, seq[i]);
		}
	    }
	  if (erro > 0)
	    {
	      printf ("\n deve possuir somente as letras A, T, C e G!"); //pede para que o usuario digite novamente; 
	      printf ("\ndigite de novo \n\n");
	      scanf ("%s", seq);
	    }
	}
      while (tamanho > tam || erro > 0);
    }
}


void
mostraSeqemMaius (int tam, int raiz, char seq[tam], char dna[][raiz])	// trasformar letras minusculas em maiusculas 
{

  if (tam > 0)
    {
      printf ("\n\n a sequencia do dna foi:\n");
      int d = 0;
      for (int i = 0; i < raiz; i++)
	{
	  for (int j = 0; j < raiz; j++, d++)
	    {
	      dna[i][j] = seq[d];
	      if (dna[i][j] == 'a' || dna[i][j] == 't' || dna[i][j] == 'c'
		  || dna[i][j] == 'g')
		{
		  dna[i][j] = toupper (dna[i][j]);
		}
	      printf ("%c\t", dna[i][j]);
	    }
	  printf ("\n");
	}
    }
}

int
analiseLin (int raiz, char dna[][raiz])
{
  int simios = 0;
  for (int i = 0; i < raiz && raiz > 0 && simios < 3; i++)
    {
      for (int j = 0; j < raiz && simios < 3; j++)
	{
	  if (dna[i][j] == dna[i][j + 1])
	    {
	      simios = simios + 1;
	      
	    }
	  else if (j + 1 != raiz && simios < 3)
	    {
	      simios = 0;
	    }
	}
    }
  return simios;
}

int
analiseCol (int raiz, char dna[][raiz], int simios)
{
  for (int i = 0; i < raiz && raiz > 0; i++)
    {
      for (int j = 0; j < raiz && simios < 3; j++)
	{
	  if (dna[j][i] == dna[j + 1][i])
	    {
	      simios = simios + 1;
	      
	    }
	  else if (j + 1 != raiz && simios < 3)
	    {
	      simios = 0;
	    }
	}
    }
  return simios;
}

int
analiseDP (int raiz, char dna[][raiz], int simios)	//analisa as diagonais maiores ou iguais a 4 no mesmo sentido da principal
{
  int diagonais = ((raiz - 4) * 2) + 1; 
  int lin, col, cont, x;
  lin = raiz - 4;		
  col = x = 0;
  if (simios < 3 && raiz > 0)
    {
      simios = 0;
      do
	{
	  cont = 0;
	  for (int i = lin, j = col; (i + 1) != raiz && (j + 1) != raiz;
	       i++, j++)
	    {
	      if (dna[i][j] == dna[i + 1][j + 1])
		{
		  cont = cont + 1;
		}
	      else if (i + 1 != raiz && j + 1 != raiz && cont < 3)
		{
		  cont = 0;
		}
	    }

	  if (simios < cont)
	    {
	      simios = cont;
	    }
	  if (lin > col)
	    {
	      lin--;
	    }
	  else
	    {
	      col++;
	    }
	  x = x + 1;
	}
      while (x < diagonais);
    }
  return simios;
}

int
analiseDS (int raiz, char dna[][raiz], int simios)	//analisa as diagonais maiores ou iguais a 4 no mesmo sentido da secundaria
{
  int diagonais = ((raiz - 4) * 2) + 1;
  int cont, lin, col;
  int x = 0;
  lin = cont = 0;
  col = 3;
  if (simios < 3 && raiz > 0)
    {
      simios = 0;
      do
	{
	  cont = 0;
	  for (int i = lin, j = col; (i + 1) != raiz && (j - 1) != -1;
	       i++, j--)
	    {
	      if (dna[i][j] == dna[i + 1][j - 1])
		{
		  cont = cont + 1;
		}
	      else if (i + 1 != raiz && j - 1 != 0 && cont < 3)
		{
		  cont = 0;
		}
	    }
	  if (simios < cont)
	    {
	      simios = cont;
	    }
	  if (col + 1 != raiz)
	    {
	      col++;
	    }
	  else
	    {
	      lin++;
	    }
	  x = x + 1;
	}
      while (x < diagonais);
    }
  return simios;
}

void
isSimian (int simios, int tam)	// faz a verificaC'C#o se C) um simion ou humano 
{
  if (tam > 0)
    {
      if (simios >= 3)
	{
	  printf (" e um simion");
	}
      else
	{
	  printf (" e um humano");
	}
    }
}




int
main (void)
{
  int tam, raiz, simio, escrever, testes = 0;
  do
    {
      tam = tamanho ();
      raiz = Raiz (tam);
      char seq[tam], dna[raiz][raiz];
      armazena (tam, seq);
      verificaTamLet (tam, seq);
      mostraSeqemMaius (tam, raiz, seq, dna);
      simio = analiseLin (raiz, dna);
      simio = analiseCol (raiz, dna, simio);
      simio = analiseDP (raiz, dna, simio);
      simio = analiseDS (raiz, dna, simio);
      isSimian (simio, tam);


    }
  while (tam != 0);

  printf ("encerrando programa");

  return 0;
}




