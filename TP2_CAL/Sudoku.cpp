/*
 * Sudoku.cpp
 *
 */

#include "Sudoku.h"

/** Inicia um Sudoku vazio.
 */
Sudoku::Sudoku()
{
	this->initialize();
}

/**
 * Inicia um Sudoku com um conteúdo inicial.
 * Lança excepção IllegalArgumentException se os valores
 * estiverem fora da gama de 1 a 9 ou se existirem números repetidos
 * por linha, coluna ou bloc 3x3.
 *
 * @param nums matriz com os valores iniciais (0 significa por preencher)
 */
Sudoku::Sudoku(int nums[9][9])
{
	this->initialize();

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (nums[i][j] != 0)
			{
				int n = nums[i][j];
				numbers[i][j] = n;
				lineHasNumber[i][n] = true;
				columnHasNumber[j][n] = true;
				block3x3HasNumber[i / 3][j / 3][n] = true;
				countFilled++;
			}
		}
	}
}

void Sudoku::initialize()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			for (int n = 0; n < 10; n++)
			{
				numbers[i][j] = 0;
				lineHasNumber[i][n] = false;
				columnHasNumber[j][n] = false;
				block3x3HasNumber[i / 3][j / 3][n] = false;
			}
		}
	}

	this->countFilled = 0;
}

/**
 * Obtem o conteúdo actual (só para leitura!).
 */
int** Sudoku::getNumbers()
{
	int** ret = new int*[9];

	for (int i = 0; i < 9; i++)
	{
		ret[i] = new int[9];

		for (int a = 0; a < 9; a++)
			ret[i][a] = numbers[i][a];
	}

	return ret;
}

/**
 * Verifica se o Sudoku já está completamente resolvido
 */
bool Sudoku::isComplete()
{
	return countFilled == 9 * 9;
}


//2.a)
/**
 * Resolve o Sudoku.
 * Retorna indicação de sucesso ou insucesso (sudoku impossível).
 */
bool Sudoku::solve()
{
	//check if it is completed.
	if(isComplete()) return true;

	//Search for the optimal cell
	int i, j;
	if(! bestCell(i,j)) return false;

	for(int n = 1; n <= 9; i++){
		if(possible(i,j,n)){
			fill(i,j,n);
			if(solve()) return true;
			clear(i,j,n);
		}
	}
	return false;
}

bool Sudoku::bestCell(int i, int j){
	i = -1, j = -1;
	int best_choices = 10;

	for(int x = 0; x < 9; x++){
		for(int y = 0; y < 9; y++){
			int choices = 0;
			//this cycle checks if the numbers 1..9 can fill the empty space, incrementing the choices we have
			for(int n = 1; n <= 9; n++){
				if(possible(x,y,n));
				choices++;
			}
			if(choices == 0) return false;//Impossible to solve;
			//if the choices argument is actually lower than the best_choices, then we update the arguments to find the best one
			if(choices < best_choices){
				best_choices = choices;
				i = x;
				j = y;
			}
			if(choices == 1) return true; // this means it can't get better so we will just return true;
		}
	}
	return (i >= 0);
}

bool Sudoku::possible(int i, int j, int n){
	return !lineHasNumber[i][n] && !columnHasNumber[j][n] && !block3x3HasNumber[i/3][j/3][n];
}

void Sudoku::fill(int i, int j, int n){
	numbers[i][j] = n;
	lineHasNumber[i][j] = true;
	columnHasNumber[i][j] = true;
	block3x3HasNumber[i/3][j/3][n] = true;
	countFilled++;
}

void Sudoku::clear(int i, int j, int n){
	numbers[i][j] = 0;
	lineHasNumber[i][j] = false;
	columnHasNumber[i][j] = false;
	block3x3HasNumber[i/3][j/3][n] = false;
	countFilled--;
}



/**
 * Imprime o Sudoku.
 */
void Sudoku::print()
{
	for (int i = 0; i < 9; i++)
	{
		for (int a = 0; a < 9; a++)
			cout << this->numbers[i][a] << " ";

		cout << endl;
	}
}
