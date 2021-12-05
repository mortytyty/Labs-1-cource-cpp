#include <iostream>
using namespace std;
const int n = 6;
int i, j;
bool* NUM = new bool[n]; //массив посещенных вершин
int G[n][n]; //граф
/* = {
	{0,1,1,0,0,1},
	{1,0,0,1,0,0},
	{1,0,0,0,1,0},
	{0,1,0,0,0,0},
	{0,0,1,0,0,0},
	{1,0,0,0,0,0}
};*/
void DFS(int st) //функция обхода в глубину
{
	int r;
	cout << st + 1 << " ";
	NUM[st] = true;
	for (r = 0; r < n; r++)
		if ((G[st][r] != 0) && (!NUM[r]))
			DFS(r);
}

void main() //главная функция
{
	srand(time(NULL));
	setlocale(LC_ALL, "Rus");
	int start;

	for (i = 0; i < n; i++) 
	{
		NUM[i] = false;
		G[i][i] = 0;
		for (j = 0; j < i; j++) 
		{
			G[j][i] = G[i][j] = rand() % 2; //заполнение графа случайными числами
		}
	}

	cout << "Матрица смежности графа: " << endl;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			cout << " " << G[i][j]; //вывод таблицы смежности графа
		cout << endl;
	}
	cout << "Стартовая вершина >> "; 
	cin >> start;
	cout << "Порядок обхода: ";
	DFS(start - 1);//обход в грубину
	delete[]NUM;
	system("pause>>void");
}