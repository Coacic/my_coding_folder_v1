#include<stdio.h> 
#include<math.h> 


int main() {
	int gen[][4] = { {1,1,1,0},{0,1,1,1},{1,1,0,1} }; 
	//Iz zadate matrice se vidi da je broj kolona 4 i broj vrsta 3
	int row = 3;
	int col = 4; 
	int k = row,n = col;
	int m = pow(2, k);
	printf("(%d,%d)\n", n, k);
	//Realizujem operaciju mnozenja matrica
	int finamat[8][4], pommat[][3] = { {0,0,0},{0,0,1},{0,1,0},{0,1,1},{1,0,0},{1,0,1},{1,1,0},{1,1,1} };
	int ma[1][3],x=0;
	while ( x < 8)
	{
		for (int h = 0; h < 3; h++){
			ma[1][h] = pommat[x][h];
		}
		for (int j = 0; j < 4; j++)	{
				int temp = 0;
				for (int k = 0; k < 3; k++)
				{
					temp += ma[1][k] * gen[k][j];
				}
				finamat[x][j] = temp;
			}
		x++;
	}
	//Prebrojava i ispisuje tezine kodnih reci
	int tez[8];
	for (int j = 0; j < 8; j++)
	{
		int y = 0;
		for (int k = 0; k < 4; k++)
		{
			printf("%d", finamat[j][k]);
			if (finamat[j][k] == 1) { y++; }
		}
		printf("  Tezina reci je d=%d\n",y);
		tez[j] = y;
	}
	printf("\n");
	//Ispisuje koliko ima kojih tezina
	for (int j = 0; j < 5; j++)
	{
		int y = 0;
		for (int k = 0; k < 8; k++)
		{
			if (tez[k] == j)y++;
		}
		printf("Broj reci tezine %d je %d\n", j,y);
	}
	printf("\n");
	//Broj gresaka koji kod moze da ispravi
	int c = n - k;
	int ec = (c - 1) / 2;
	printf("Broj gresaka koje moze da ispravi ovakav kod je %d", ec);
	return 0;
}
