#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// Vazio significa ter o valor zero, consequentemente uma celula vazia
#define VAZIO 0
#define TEMPO 250
 
int iter = 0; 

#define TAM 9
 
/*  Busca na matriz alguma célula que está vazia. 
 *  Se encontrar, retorna por referencia
 *  a posição da linha e da coluna e retorna true
 */
bool isEmpty(int  matriz[TAM][TAM], int &row, int &col);
 
// Essa função verifica se todas as restrições são aceitas 
bool isSafe(int  matriz[TAM][TAM], int row, int col, int num);

void imprimirTabuleiro(int matriz[TAM][TAM]);
 

/*
função que recebe com alguns valores prévios e executa o algoritmo backtraking
*/
bool SodokuBackTracking(int  matriz[TAM][TAM])
{
    int row, col;
 
    // Se não houver nenhum local com o valor zero, o problema foi resolvido
    // se houver, essa função retorna falso, mas retorna a posição linha e coluna (row&col)
    if (!isEmpty( matriz, row, col)) // utiliza valores referencia para trocar os valores
       return true; // success!
 
    // fazer a tentativa com numeros de 1 a 9
    for (int num = 1; num <= 9; num++)
    {
        // se tudo ocorrer bem e não der conflito
        if (isSafe( matriz, row, col, num)) // is safe testa todas as restrições
        {
            // coloar o numero na posição e chamar recursivamente a função
             matriz[row][col] = num;

             //sleep(1);
             usleep(TEMPO);
             system("clear");
             printf("%d\n", iter++);
             imprimirTabuleiro(matriz);

            // se retornar verdadeiro sair das chamadas 
            if (SodokuBackTracking( matriz))
                return true;
 
            // se der errado, colocar zero na posição e continar tentando
             matriz[row][col] = VAZIO;
        }
    }
    return false; // this triggers backtracking
}
 
/* Busca na matriz alguma célula que está vazia. Se encontrar, retorna por referencia
a posição da linha e da coluna e retorna true, se não estiver vazio, permanecer com a posição
da chamada da função e retornar falso.*/
bool isEmpty(int  matriz[TAM][TAM], int &row, int &col)
{
    for (row = 0; row < TAM; row++)
        for (col = 0; col < TAM; col++)
            if ( matriz[row][col] == VAZIO)
                return true;
    return false;
}
 
/* retorna true se houver um numero no local e falso se estiver vazio. */
bool testarLinha(int  matriz[TAM][TAM], int row, int num)
{
    for (int col = 0; col < TAM; col++)
        if ( matriz[row][col] == num)
            return true;
    return false;
}
 
/* retorna true se houver um numero no local e falso se estiver vazio. */
bool testarCol(int  matriz[TAM][TAM], int col, int num)
{
    for (int row = 0; row < TAM; row++)
        if ( matriz[row][col] == num)
            return true;
    return false;
}
 
/* retorna true se encontrar algum numero dentro da submatriz e retorna falso se
   não encontrar nada.
*/
bool testarSubMatriz(int  matriz[TAM][TAM], int rowOffset, int colOffset, int num)
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if ( matriz[row + rowOffset][col + colOffset] == num)
                return true;
    return false;
}
 
/* Função que usa as 3 funções de testa na linha, coluna e submatriz
caso essas 3 condições atendam, retornar verdadeiro, caso contrario, retornar falso.
*/
bool isSafe(int  matriz[TAM][TAM], int row, int col, int num)
{
    
    return !testarLinha( matriz, row, num) &&
           !testarCol( matriz, col, num) &&
           !testarSubMatriz( matriz, row - row%3 , col - col%3, num);
}
 
/* função para imprimir a matriz de forma bonitinha*/

void imprimirTabuleiro(int matriz[TAM][TAM])
{
    printf( ANSI_COLOR_GREEN "\n - SuDOKU & BACKTRACKING - \n\n" ANSI_COLOR_RESET );
    
    
    printf( ANSI_COLOR_CYAN "- - - - - - - - - - - - - \n" ANSI_COLOR_RESET );
    
    /* imprime linhas */
    for( int row = 0; row < 9; row++) {
         /* immprime colunas */
        printf(ANSI_COLOR_CYAN "| " ANSI_COLOR_RESET );
        for( int col=0; col<9; col++){
            
            if( matriz[row][col] == 0 ) printf("  ");
            else printf(ANSI_COLOR_MAGENTA "%d " ANSI_COLOR_RESET,  matriz[row][col]);
            
            if ((col+1)%3 == 0) printf( ANSI_COLOR_CYAN "| "  ANSI_COLOR_RESET );
        }
        if ((row+1)%3 == 0) printf( ANSI_COLOR_CYAN "\n- - - - - - - - - - - - - " ANSI_COLOR_RESET);
        
        printf("\n");
        
    }
}
 
int main()
{
    

    // 0 para células vazias
    int  matriz[TAM][TAM] = {
                              {5, 3, 0, 0, 7, 0, 0, 0, 0},
                              {6, 0, 0, 1, 9, 5, 0, 0, 0},
                              {0, 9, 8, 0, 0, 0, 0, 6, 0},
                              {8, 0, 0, 0, 6, 0, 0, 0, 3},
                              {4, 0, 0, 8, 0, 3, 0, 0, 1},
                              {7, 0, 0, 0, 2, 0, 0, 0, 6},
                              {0, 6, 0, 0, 0, 0, 2, 8, 0},
                              {0, 0, 0, 4, 1, 9, 0, 0, 5},
                              {0, 0, 0, 0, 8, 0, 0, 7, 9} };
    if (SodokuBackTracking( matriz) == true)
    {
        system("clear");
        printf("%d\n", iter++);
        imprimirTabuleiro( matriz);
    }

          
    else
         printf("Não existe solução");
 
    return 0;
}