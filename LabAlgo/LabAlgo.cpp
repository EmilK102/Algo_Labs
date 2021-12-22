#include <iostream>
#include <ctime>
#include <clocale>

#include "Header.h"
#define M 52

using namespace std;

float full,num;

int all = 0;

int main() {
	setlocale(LC_ALL, "");
	srand(time(0));

	int Arr[M];
	int hTable[M/2][10];
	int rArr[90];
	for (int i = 10; i < 100; i++) {
		rArr[i - 10] = i;
	}
	rndArray(Arr, rArr);
	priArray(Arr);
	creTable(hTable);
	for (int i = 0; i < M; i++) {
		hashTable(hTable, Arr[i]);
	}
	priTable(hTable);
	countTable(hTable);

	printf("Коэффицент: %f\n", full / 26);
	printf("Среднее количество шагов: %f", num/full);

	return 0;
}

int rndNumber(int* A) {
	int tmp, ind;
	ind = rand() % 90;
	all++;
	while (A[ind] == -1) {
		if (all >= 90) return -1;
		ind = rand() % 90;
	}
	tmp = A[ind];
	A[ind] = -1;
	return tmp;
}

void rndArray(int* A, int* B) {
	for (int i = 0; i < M; i++) {
		A[i] = rndNumber(B);
	}
}

void priArray(int* A) {
	printf("Массив\n");
	for (int i = 0; i < M; i++) {
		if (i % 4 == 0 && i != 0) printf("\n");
		printf("\t[%i]%i",i+1,A[i]);
	}
	printf("\n");
}

int hashFun(int a) {
	return ((a * a)%100)%26;
}

void hashTable(int (&A)[M/2][10], int B) {
	int tmp = hashFun(B);
	for (int j = 0; j < M / 2; j++) {
		if (j == tmp || tmp == -1) {
			num++;
			for (int k = 0; k < 10; k++) {
				num++;
				if (A[j][k] == -1) {
					A[j][k] = B;
					return;
				}
			}
			tmp = -1;
		}
	}
}

void priTable(int (&A)[M/2][10]) {
	printf("Хеш-таблица:\n");
	printf("\t ");
	for (int i = 0; i < 10; i++) {
		printf("\t[%i]",i);
	}
	printf("\n");

	for (int i = 0; i < M/2; i++) {
		printf("\t[%i]", i);
		for (int j = 0; j < 10; j++) {
			printf("\t%i |",A[i][j]);
		}
		printf("\n");
	}
}

void creTable(int (&A)[M/2][10]) {
	for (int i = 0; i < M / 2; i++) {
		for (int j = 0; j < 10; j++)
			A[i][j] = -1;
	}
}

void countTable(int (&A)[M/2][10]) {
	full = 0;
	for (int i = 0; i < M / 2; i++) {
		if (A[i][0] == -1) continue;
		full++;
	}
}