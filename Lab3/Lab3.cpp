#include <iostream>
using namespace std;

#define N 25

struct Branch
{
	int Data; //Поле данных
	Branch* LeftBranch; //УКАЗАТЕЛИ на соседние веточки
	Branch* RightBranch;
};


//Функция внесения данных
void Add(int aData, Branch*& aBranch)
{
	//Если ветки не существует
	if (!aBranch)
	{ //создадим ее и зададим в нее данные
		aBranch = new Branch;
		aBranch->Data = aData;
		aBranch->LeftBranch = 0;
		aBranch->RightBranch = 0;
		return;
	}
	else //Иначе сверим вносимое
	{
		if (aBranch->Data > aData)
		{ //Если оно меньше того, что в этой ветке - добавим влево
			Add(aData, aBranch->LeftBranch);
		}
		else
		{ //Иначе в ветку справа
			Add(aData, aBranch->RightBranch);
		}
	}
}

void print(Branch* aBranch, int level)
{
	if (!aBranch) return;
	print(aBranch->RightBranch, level + 1);
	for (int i = 0; i < level; i++) {
		printf("    ");
	}
	printf("%i\n", aBranch->Data);
	print(aBranch->LeftBranch, level + 1);
}

void DeleteTree(Branch* aBranch)
{
	if (!aBranch) return;
	DeleteTree(aBranch->LeftBranch);
	DeleteTree(aBranch->RightBranch);
	delete aBranch;
	return;
}

void postorder(Branch* aBranch) {
	if (!aBranch) return;
	postorder(aBranch->LeftBranch);
	postorder(aBranch->RightBranch);
	printf("%i ", aBranch->Data);
}

int main()
{
	setlocale(LC_ALL, "");
	srand(time(NULL));
	Branch* Root = 0;

	int Arr[N];
	for (int i = 0; i < N; i++) {
		Arr[i] = rand() % 90 + 10;
		for (int j = 1; j <= N; j++) {
			while (Arr[i] == Arr[i - j]) {
				Arr[i] = rand() % 90 + 10;
			}
		}
		Add(Arr[i], Root);
	}

	printf("Неповторяющиеся элементы:\n");
	for (int i = 0; i < N; i++) {
		if (i % 4 == 0 && i != 0) printf("\n");
		printf("\t[%i]%i", i + 1, Arr[i]);
	}

	printf("\nВывод дерева:\n");
	print(Root, 0);
	printf("\nОбратный обход:\n");
	postorder(Root);
	DeleteTree(Root);
	return 0;
}