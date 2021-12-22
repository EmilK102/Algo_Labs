#include <iostream>
#include <ctime>
#include <clocale>

#include "Header.h"

#define M 52

using namespace std;

float full,Num;

int ind = 0;
int all = 0;

int main() {
	setlocale(LC_ALL, "");
	srand(time(0));

	int Arr[M];
	int hTable[M / 2][10];
	int rArr[90];
	rndArray(Arr, rArr);
	priArray(Arr);
	creTable(hTable);
	for (int i = 0; i < M; i++) {
		hashTable(hTable, Arr[i]);
	}
	priTable(hTable);
	other(hTable);

	int count = -1;
	while (count != 0) {
		printf("\n1)Поиск элемента"
			"\n2)Добавить элемент"
			"\n3)Удалить элемент"
			"\n4)Замена элемента"
		"\n");
		cin >> count;
		switch (count)
		{
		case 1:
			sechElm(hTable);
			break;
		case 2:
			addElm(hTable, rArr);
			break;
		case 3:
			delElm(hTable);
			break;
		case 4:
			rplElm(hTable);
			break;
		default:
			break;
		}
		priTable(hTable);
		other(hTable);
	}

	return 0;
}


int rndNumber(int* A) {
	if (all >= 90) return -1;
	A[all] = rand() % 90 + 10;
	for (int j = 1; j <= all; j++) {
		while (A[all] == A[all - j]) {
			A[all] = rand() % 90 + 10;
		}
	}
	return A[all];
}
 

void rndArray(int* A, int* B) {
	for (int i = 0; i < M; i++) {
		rndNumber(A);
		all++;
	}
	for (int i = 0; i < M; i++) {
		B[i] = A[i];
	}
}

void priArray(int* A) {
	printf("Массив\n");
	for (int i = 0; i < M; i++) {
		if (i % 4 == 0 && i != 0) printf("\n");
		printf("\t[%i]%i", i + 1, A[i]);
	}
	printf("\n");
}

int hashFun(int a) {
	return ((a * a) % 100) % 26;
}

void hashTable(int(&A)[M / 2][10], int B) {
	if (B == -1) return;
	int tmp = hashFun(B);
	for (int j = 0; j < M / 2; j++) {
		if (j == tmp || tmp == -1) {
			ind = j;
			Num++;
			for (int k = 0; k < 10; k++) {
				Num+=k;
				if (A[j][k] == -1) {
					A[j][k] = B;
					return;
				}
			}
			tmp = -1;
		}
	}
}

void priTable(int(&A)[M / 2][10]) {
	printf("Хеш-таблица:\n");
	printf("\t ");
	for (int i = 0; i < 10; i++) {
		printf("\t[%i]", i);
	}
	printf("\n");

	for (int i = 0; i < M / 2; i++) {
		printf("\t[%i]", i);
		for (int j = 0; j < 10; j++) {
			if (A[i][j] == -1)
			{ 
				printf("\t   |");
				continue;
			}
			printf("\t%i |", A[i][j]);
		}
		printf("\n");
	}
}

void creTable(int(&A)[M / 2][10]) {
	for (int i = 0; i < M / 2; i++) {
		for (int j = 0; j < 10; j++)
			A[i][j] = -1;
	}
}

void countTable(int(&A)[M / 2][10]) {
	full = 0;
	for (int i = 0; i < M / 2; i++) {
		if (A[i][0] == -1) continue;
		full++;
	}
}

void addElm(int(&A)[M / 2][10], int* B) {
	printf("Как добавить элемент?:\n"
	"1)Вручную\n"
	"2)Сгенерировать\n");
	int num, cnt, tmp;
	cin >> num;
	if (num == 1) {
		printf("Введите число\n");
		cin >> tmp;
		if (tmp == 0) return;
		while (chkElm(A, tmp) != -1) {
			printf("Число уже находится по индексу %i\n", ind);
			if (all >= 90) return;
			printf("Введите число\n");
			cin >> tmp;
			if (tmp == 0) return;
		}
		hashTable(A, tmp);
		printf("Число %i записано в %i индекс\n", tmp, ind);
	}
	else {
		printf("Введите количество элементов:\n");
		cin >> cnt;
		for (int i = 0; i < cnt; i++) {
			tmp = rndNumber(B);
			if (tmp == -1) return;
			hashTable(A, tmp);
			printf("Число %i записано в %i индекс\n", tmp, ind);
		}
	}
}

void delElm(int(&A)[M / 2][10]) {
	printf("Введите число:\n");
	int num;
	cin >> num;
	int chNum = chkElm(A, num);
	if (chNum == -1) {
		printf("Число не найдено\n");
	}
	else {
		for (int j = 0; j < 10; j++) {
			if (A[chNum][j] == num) {
				A[chNum][j] = -1;
				for (int k = j; k < 9; k++) {
					A[chNum][k] = A[chNum][k+1];
					A[chNum][k+1] = -1;
				}
				break;
			}
		}
		printf("Число удалено из индекса %i\n", chNum);
	}
}

void sechElm(int(&A)[M / 2][10]) {
	printf("Введите число:\n");
	int num;
	cin >> num;
	int chNum = chkElm(A, num);
	if (chNum == -1) {
		printf("Число не найдено\n");
	}
	else {
		printf("Число находится по индексу %i\n", chNum);
	}
}

void rplElm(int(&A)[M / 2][10]) {
	int num, num2;
	printf("Введите число для замены:\n");
	cin >> num;
	if (num == 0) return;
	while (chkElm(A, num) == -1) {
		printf("Число не найдено\n");
		printf("\nВведите число для замены:\n");
		cin >> num;
		if (num == 0) return;
	}
	printf("Введите заменяющее число:\n");
	cin >> num2;
	if (num2 == 0) return;
	while (chkElm(A, num2) != -1) {
		printf("Число есть в таблице\n");
		printf("Введите заменяющее число:\n");
		cin >> num2;
		if (num2 == 0) return;
	}
	int chNum = chkElm(A, num);
	printf("Число удалено из индекса: %i\n",chNum);
	for (int j = 0; j < 10; j++) {
		if (A[chNum][j] == num) {
			A[chNum][j] = -1;
			for (int k = j; k < 9; k++) {
				A[chNum][k] = A[chNum][k + 1];
				A[chNum][k + 1] = -1;
			}
			break;
		}
	}
	hashTable(A, num2);
	printf("Число %i записано в %i индекс\n", num2, ind);
}

int chkElm(int(&A)[M / 2][10],int elm) {
	int tmp;
	tmp = hashFun(elm);
	ret:
	for (int j = 0; j < 10; j++) {
		if (A[tmp][j] == -1) break;
		if (A[tmp][j] == elm) return tmp;
		if (j == 9) { 
			++tmp;
			goto ret;
		}
	}
	return -1;
}

void other(int(&A)[M / 2][10]) {
	countTable(A);

	printf("Коэффицент: %f\n", full / 26);
	printf("Среднее количество шагов: %f", Num / M);
}