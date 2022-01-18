#include <iostream>
#include <windows.h>
using namespace std;
int** M1, ** M2, **M3;
void fill();
void create(int size)
{
	int i, j;
	M1 = (int**)malloc(size * (sizeof(int)));
	M2 = (int**)malloc(size * (sizeof(int)));
	srand(time(NULL));
	for (i = 0; i < size; i++)
	{
		M1[i] = (int*)malloc(size * (sizeof(int)));
		M2[i] = (int*)malloc(size * (sizeof(int)));
		for (j = 0 + i; j < size; j++)
		{
			M1[i][j] = 0;
			M2[i][j] = rand() % 2;
		}
	}

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			M1[j][i] = M1[i][j];
			if (i == j)
				M1[i][j] = 0;
			M2[j][i] = M2[i][j];
			if (i == j)
				M2[i][j] = 0;
		}
	}
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			cout << M2[i][j] << ' ';
		}
		cout << endl;
	}
}
void InitM3(int size) 
{
	int i, j;
	M3 = (int**)malloc(size * sizeof(int));
	for (i = 0; i < size; i++) 
	{
		M3[i] = (int*)malloc(size * sizeof(int));
		for (j = 0; j < size; j++) 
		{
			M3[i][j] = 0;
		}
	}
}
void identify(int size, int first, int second) 
{
	int i, j;
	int razn = second - first;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if ((i < second) && (j < second)) { M1[i][j] = M2[i][j]; } 
			if ((i <= first) && (j == second)) { M1[i][first] += M2[i][j]; } 
			if ((i == second) && (j < first)) { M1[first][j] += M2[i][j]; } 
			if ((i < second) && (j > second)) { M1[i][j - 1] = M2[i][j]; } 
			if ((j < second) && (i > second)) { M1[i - 1][j] = M2[i][j]; } 
			if ((i == first + 1) && (j == second)) { M1[i - 1][j - razn + 1] += M2[i][j]; } 
			if ((j == first + 1) && (i == second)) { M1[i - razn + 1][j - 1] += M2[i][j]; } 
		}
	}

	for (i = second + 1; i < size; i++) {
		for (j = second + 1; j < size; j++) {
			M1[i - 1][j - 1] = M2[i][j];
		}
	}

	for (i = 0; i < size - 1; i++) {
		for (j = 0; j < size - 1; j++) {
			if (M1[i][j] > 1) { M1[i][j] = 1; }
		}
	}
}
void constrict(int size, int first, int second) 
{
	int i, j, razn;

	razn = second - first;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if ((i < second) && (j < second)) M1[i][j] = M2[i][j]; 
			if ((i < first) && (j == second)) M1[i][first] += M2[i][j]; 
			if ((i == second) && (j < first)) M1[first][j] += M2[i][j];
			if ((i < second) && (j > second)) M1[i][j - 1] = M2[i][j];
			if ((j < second) && (i > second)) M1[i - 1][j] = M2[i][j];
			if ((i == first + 1) && (j == second)) M1[i - 1][j - razn + 1] += M2[i][j];
			if ((j == first + 1) && (i == second)) M1[i - razn + 1][j - 1] += M2[i][j];
		}
	}

	for (i = second + 1; i < size; i++) {
		for (j = second + 1; j < size; j++) {
			M1[i - 1][j - 1] = M2[i][j];
		}
	}

	for (i = 0; i < size - 1; i++) {
		for (j = 0; j < size - 1; j++) {
			if (M1[i][j] > 1) { M1[i][j] = 1; }
		}
	}
}
void split(int size, int pos) 
{
	int i, j;

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			M3[i][j] = M2[i][j];
			if (j == pos) {
				if (i == pos) { M3[i][size] = 1; M3[size][i] = M3[i][size]; }
				else { M3[i][size] = M2[i][pos]; M3[size][i] = M2[i][pos]; }
			}
		}
	}
}
void InitM1(int size)
{
	int i, j;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			M1[i][j] = rand() % 2;
		}
	}
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			printf("%d ", M1[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void SumMatrix(int size) 
{
	int i, j;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			M1[i][j] += M2[i][j];
			if (M1[i][j] == 2) { M1[i][j] = 1; }
			cout << M1[i][j] << " ";
		}
		cout << endl;
	}
}
void CrossMatrix(int size) 
{
	int i, j;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (M1[i][j] != M2[i][j]) { M1[i][j] = 0; }
			cout << M1[i][j] << " ";
		}
		cout << endl;
	}
}
void RingSum(int size) 
{
	int i, j;

	for (i = 0; i < size; i++) 
	{
		for (j = 0; j < size; j++) 
		{
			if (M1[i][j] == M2[i][j]) { M1[i][j] = 0; }
			else { M1[i][j] = 1; }
			cout << M1[i][j] << " ";
		}
		cout << endl;
	}
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int i, j, Number, pos, size, first, second, type;
	cout << "Введите тип задания:\n1-Матрица\n2-Список\n" << endl;
	cin >> type;

	switch (type) {
	case 1:
		cout << "Введите размер графа:" << endl;
		cin >> size;
		create(size);
		cout << "Введите тип операции:\n1-отождествление\n2-стягивание\n3-расщепление\n4-объединение\n5-пересечение\n6-кольц. сумма\n";
		cin >> Number;
		switch (Number)
		{
		case 1:
			cout << "Введите отождествляемые вершины" << endl;
			cin >> first >> second;
			identify(size, first - 1, second - 1);
			for (i = 0; i < size - 1; i++)
			{
				for (j = 0; j < size - 1; j++)
				{
					cout << M1[i][j] << ' ';
				}
				cout << endl;
			}
			break;
		case 2:
			cout << "Введите стягивающиеся вершины" << endl;
			cin >> first >> second;
			if (M2[first][second] == 1)
			{
				constrict(size, first - 1, second - 1);
				for (i = 0; i < size - 1; i++)
				{
					for (j = 0; j < size - 1; j++)
					{
						cout << M1[i][j] << ' ';
					}
					cout << endl;
				}
			}
			else cout << "Невозможно стянуть данные вершины";
			break;
		case 3:
			cout << "Введите вершину для расщепления" << endl;
			cin >> pos;
			InitM3(size + 1);
			split(size, pos - 1);

			for (i = 0; i < size + 1; i++)
			{
				for (j = 0; j < size + 1; j++)
				{
					cout << M3[i][j] << ' ';
				}
				cout << endl;
			}
			break;
		case 4:
			printf("Вторая матрица\n");
			InitM1(size);
			printf("Итоговая матрица\n");
			SumMatrix(size);
			break;
		case 5:
			printf("Вторая матриц\n");
			InitM1(size);
			printf("Итоговая матриц\n");
			CrossMatrix(size);
			break;
		case 6:
			printf("Вторая матрица\n");
			InitM1(size);
			printf("Итоговая матрица\n");
			RingSum(size);
			break;
		}
		break;
	case 2:
		fill();
		break;
	}
}

