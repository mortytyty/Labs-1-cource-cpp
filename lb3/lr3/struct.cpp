#include <time.h>
#include <malloc.h>
#include <locale.h>
#include <iostream>
using namespace std;

struct Node {
	int items;
	Node* next;
};

typedef Node* PNode;

PNode CreateNode(int items) {
	PNode NewNode = new Node;
	NewNode->items = items;
	NewNode->next = NULL;
	return NewNode;
}

void AddFirst(PNode NewNode, int i, PNode* Head) {
	NewNode->next = Head[i];
	Head[i] = NewNode;
}

void InitializHead(int n, PNode* Head, PNode NewNode) {
	int i;
	for (i = 0; i < n; i++) {
		Head[i] = NULL;
	}

	for (i = 0; i < n; i++) {
		NewNode = CreateNode(i);
		AddFirst(NewNode, i, Head);
	}
}

void gener(PNode NewNode, int i) {}

void AddAfter(PNode p, PNode NewNode) {
	NewNode->next = p->next;
	p->next = NewNode;
}

void AddLast(PNode NewNode, int i, PNode* Head) {
	PNode q = Head[i];

	while (q->next) q = q->next;
	AddAfter(q, NewNode);
}

void InitStruct(int n, PNode NewNode, PNode* Head, int** matrix) {
	int i, j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (matrix[i][j] == 1) {
				NewNode = CreateNode(j);
				AddLast(NewNode, i, Head);
			}
		}
	}
}

void DeleteNode(PNode OldNode, PNode* Head, int i) {
	PNode q = Head[i];

	while (q && q->next != OldNode) q = q->next;
	if (q == NULL) return;
	q->next = OldNode->next;

	delete OldNode;
}

void PrintStruct(int n, PNode* Head) {
	for (int i = 0; i < n; i++) {
		PNode q = Head[i];
		while (q) {
			cout << q->items << " ";
			q = q->next;
		}
		cout << endl;
	}
}

void InitializMatrix(int** matrix, int n) {
	int i, j, ran;

	for (i = 0; i < n; i++) {
		matrix[i] = (int*)malloc(n * sizeof(int));
		for (j = 0; j < n; j++) {
			matrix[i][j] = 0;
		}
	}

	for (i = 0; i < n; i++) {
		for (j = i + 1; j < n; j++) {
			ran = rand() % 101;
			if (ran > 30) {
				matrix[i][j] = 1;
				matrix[j][i] = matrix[i][j];
			}
			else {
				matrix[i][j] = 0;
				matrix[j][i] = matrix[i][j];
			}
		}
	}
}

void PrintMatrix(int n, int** matrix) {
	int i, j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

void otogstruct(int n, int min, int max, PNode* Head1) {
	int i;
	PNode NewNode;

	for (i = 0; i < n; i++) {
		Head1[i] = Head1[i]->next;
		int flag = 0;
		while (Head1[i]) {

			if (Head1[i]->items == min) flag = 1;
			if (i == max) {
				NewNode = CreateNode(Head1[i]->items);
				AddLast(NewNode, min, Head1);
			}
			else {
				if (Head1[i]->items == max && flag == 1) {
					DeleteNode(Head1[i], Head1, i);
				}
				else {
					if (Head1[i]->items == max) {
						Head1[i]->items = min;
						/*NewNode = CreateNode(min);
						AddLast(NewNode, i, Head2);*/
					}
				}
			}
			Head1[i] = Head1[i]->next;
		}
	}
}

void otog(int** G, int** A, int n, int min, int max) {
	int i, j;
	int razn = max - min;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if ((i < max) && (j < max)) { A[i][j] = G[i][j]; } 
			if ((i <= min) && (j == max)) { A[i][min] += G[i][j]; } 
			if ((i == max) && (j < min)) { A[min][j] += G[i][j]; } 
			if ((i < max) && (j > max)) { A[i][j - 1] = G[i][j]; } 
			if ((j < max) && (i > max)) { A[i - 1][j] = G[i][j]; } 
			if ((i == min + 1) && (j == max)) { A[i - 1][j - razn + 1] += G[i][j]; } 
			if ((j == min + 1) && (i == max)) { A[i - razn + 1][j - 1] += G[i][j]; } 
		}
	}

	for (i = max + 1; i < n; i++) {
		for (j = max + 1; j < n; j++) {
			A[i - 1][j - 1] = G[i][j];
		}
	}

	for (i = 0; i < n - 1; i++) {
		for (j = 0; j < n - 1; j++) {
			if (A[i][j] > 1) { A[i][j] = 1; }
		}
	}
}

void stiag(int** G, int** A, int n, int min, int max) {
	int i, j, razn;

	razn = max - min;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if ((i < max) && (j < max)) A[i][j] = G[i][j]; 
			if ((i < min) && (j == max)) A[i][min] += G[i][j]; 
			if ((i == max) && (j < min)) A[min][j] += G[i][j];
			if ((i < max) && (j > max)) A[i][j - 1] = G[i][j];
			if ((j < max) && (i > max)) A[i - 1][j] = G[i][j];
			if ((i == min + 1) && (j == max)) A[i - 1][j - razn + 1] += G[i][j];
			if ((j == min + 1) && (i == max)) A[i - razn + 1][j - 1] += G[i][j];
		}
	}

	for (i = max + 1; i < n; i++) {
		for (j = max + 1; j < n; j++) {
			A[i - 1][j - 1] = G[i][j];
		}
	}

	for (i = 0; i < n - 1; i++) {
		for (j = 0; j < n - 1; j++) {
			if (A[i][j] > 1) { A[i][j] = 1; }
		}
	}
}

void raschepstruct(int n, int v, PNode* Head1, PNode* Head2) {
	int i;
	PNode NewNode;

	for (i = 0; i < n; i++) {
		Head1[i] = Head1[i]->next;
		while (Head1[i]) {
			if (Head1[i]->items == v) {
				NewNode = CreateNode(n);
				AddLast(NewNode, i, Head2);
				NewNode = CreateNode(i);
				AddLast(NewNode, n, Head2);
			}
			NewNode = CreateNode(Head1[i]->items);
			AddLast(NewNode, i, Head2);
			Head1[i] = Head1[i]->next;
		}
	}
	NewNode = CreateNode(v);
	AddLast(NewNode, n, Head2);
	NewNode = CreateNode(n);
	AddLast(NewNode, v, Head2);
}

void raschep(int** G, int** A, int n, int v) {
	int i, j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			A[i][j] = G[i][j];
			if (j == v) {
				if (i == v) { A[i][n] = 1; A[n][i] = A[i][n]; }
				else { A[i][n] = G[i][v]; A[n][i] = G[i][v]; }
			}
		}
	}
}

void fill() {
	int** G, ** A;
	int n, i, j, min, max, flag, v;
	PNode NewNode = NULL, * Head1, * Head2;

	srand(time(NULL));
	setlocale(LC_ALL, "RUS");

	cout << "Введите размер матрицы" << endl;
	cin >> n;

	G = (int**)malloc(n * sizeof(int));
	InitializMatrix(G, n);
	PrintMatrix(n, G);
	cout << endl;

	Head1 = (PNode*)malloc(n * sizeof(PNode));
	InitializHead(n, Head1, NewNode);
	InitStruct(n, NewNode, Head1, G);
	PrintStruct(n, Head1);
	cout << endl;

	cout << "Введите тип операции:\n1-отождествление\n2-стягивание\n3-расщепление" << endl;
	cin >> flag;

	switch (flag)
	{
	case 1:
		cout << "Введите отождествляемые вершины" << endl;
		cin >> min >> max;

		A = (int**)malloc((n - 1) * sizeof(int));
		InitializMatrix(A, n - 1);

		otog(G, A, n, min, max);
		PrintMatrix(n - 1, A);

		Head2 = (PNode*)malloc((n + 1) * sizeof(PNode));
		//InitializHead(n - 1, Head2, NewNode);
		otogstruct(n, min, max, Head1);
		PrintStruct(n - 1, Head1);
		break;
	case 2:
		cout << "Введите стягиваемые вершины" << endl;
		cin >> min >> max;

		A = (int**)malloc((n - 1) * sizeof(int));
		InitializMatrix(A, n - 1);

		if (G[min][max] == 1) {
			stiag(G, A, n, min, max);
			PrintMatrix(n - 1, A);
		}
		else { cout << "Невозможно стянуть данные вершины"; }

		break;
	case 3:
		cout << "Введите расщепляемую вершину" << endl;
		cin >> v;

		A = (int**)malloc((n + 1) * sizeof(int));
		InitializMatrix(A, n + 1);

		raschep(G, A, n, v);
		PrintMatrix(n + 1, A);
		cout << endl;

		Head2 = (PNode*)malloc((n + 1) * sizeof(PNode));
		InitializHead(n + 1, Head2, NewNode);
		raschepstruct(n, v, Head1, Head2);
		PrintStruct(n + 1, Head2);
		break;
	}
}