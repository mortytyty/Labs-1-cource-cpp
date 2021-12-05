#include <iostream>
#include <queue> 
using namespace std;

const int n = 6;
int i, j;
int* DIST = new int[n];
int G[n][n];
/*= {
	{0,2,3,0,0,1},
	{2,0,0,5,0,0},
	{3,0,0,0,1,0},
	{0,5,0,0,0,0},
	{0,0,1,0,0,0},
	{1,0,0,0,0,0}
};*/

//поиск в ширину
void BFSD(int v)
{
	queue <int> Q;
	Q.push(v);
	DIST[v] = 0;
	while (!Q.empty())
	{
		v = Q.front();
		Q.pop();
		cout << v + 1 << " ";
		for (i = 0; i < n; i++)
			if (G[v][i] && DIST[i] > DIST[v] + G[v][i] && DIST[i]==1000)
			{
				Q.push(i);
				DIST[i] = DIST[v] + G[v][i];
			}
	}
}

//главная функция
void main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Rus");
	int start;
	cout << "Стартовая вершина >> "; cin >> start;
	for (i = 0; i < n; i++)
	{
		DIST[i] = 1000;
		G[i][i] = 0;
		
		for (j = 0; j < i; j++)
		{
			G[j][i] = G[i][j] = rand() % 5; //заполнение графа случайными числами
		}
	}
	cout << "Матрица смежности графа: " << endl;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++)
			cout << " " << G[i][j];
		cout << endl;
	}

	cout << "Порядок обхода: ";
	BFSD(start - 1);

	cout << endl << "Расстояния до вершин: ";
	for (i = 0; i < n; i++) {
		if (DIST[i] == 1000)
			DIST[i] = -1;
		cout << DIST[i] << " ";
	}

	delete[]DIST;
	system("pause>>void");
}