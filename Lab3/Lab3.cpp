#include <iostream>
using namespace std;

#define N 25

struct Branch
{
	int Data; //���� ������
	Branch* LeftBranch; //��������� �� �������� �������
	Branch* RightBranch;
};


//������� �������� ������
void Add(int aData, Branch*& aBranch)
{
	//���� ����� �� ����������
	if (!aBranch)
	{ //�������� �� � ������� � ��� ������
		aBranch = new Branch;
		aBranch->Data = aData;
		aBranch->LeftBranch = 0;
		aBranch->RightBranch = 0;
		return;
	}
	else //����� ������ ��������
	{
		if (aBranch->Data > aData)
		{ //���� ��� ������ ����, ��� � ���� ����� - ������� �����
			Add(aData, aBranch->LeftBranch);
		}
		else
		{ //����� � ����� ������
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

	printf("��������������� ��������:\n");
	for (int i = 0; i < N; i++) {
		if (i % 4 == 0 && i != 0) printf("\n");
		printf("\t[%i]%i", i + 1, Arr[i]);
	}

	printf("\n����� ������:\n");
	print(Root, 0);
	printf("\n�������� �����:\n");
	postorder(Root);
	DeleteTree(Root);
	return 0;
}