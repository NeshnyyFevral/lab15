/*27(7) ������� 
7.����� ������ N ���������������, ������ �� ��� �����
� ������� ��������� ��� ������ �������� ���� � ������� �������
����.���������� ������������� ���������� �������, ������� ���
����� � �������.*/
#include <iostream>      
#include <ctime>
#define M 1000
#define MY_ERROR_FILE 1

struct coord
{
	int x1, y1, x2, y2;
};

void fillArray(coord* mas, int &N, FILE* input);
void printArray(coord* mas, int N);
void fillArrayCoordByHand(coord* mas, int &N);
void fillArrayCoordByRandom(coord* mas, int &N);
int calculatingMostArea(coord* mas, int N);
float getArea(coord A);
int fillArrayByFile(coord* mas, int &N, FILE* input);
int saveArray(coord* mas, int N, FILE* input);

int main()
{
	system("chcp 1251");
	srand(time(0));

	coord mas[M];
	int N, index;
	float S;
	FILE* input = NULL;

	fillArray(mas, N, input);
	saveArray(mas, N, input);
	printArray(mas, N);

	index = calculatingMostArea(mas, N);
	S = getArea(mas[index]);
	printf("%i-� ������������� ����� ���������� ������� = %lf\n", index, S);

	system("pause");
	return 0;
}

//����� �������
void printArray(coord* mas, int N)
{
	for (int i = 0; i < N; i++)
	{
		printf("���������� ����� ������ �������� � ������� ������� ���� %i-�� ��������������:\n", i + 1);
		printf("x1 = %i ", mas[i].x1);
		printf("x2 = %i\n", mas[i].x2);
		printf("y1 = %i ", mas[i].y1);
		printf("y2 = %i ", mas[i].y2);
		printf("\n");
	}
	printf("\n");
}
//����� ������� ���������� ������� � ��� ���������������� ����������.
void fillArray(coord* mas, int &N, FILE* input)
{
	int choice;
	printf("�������� ������ ���������� �������:\n1)���������� �������.\n2)���� � ����������.\n3)�� �����.\n");
	do
	{
		scanf_s("%i", &choice);
		if (choice != 1 && choice != 2 && choice !=3)
			printf("�������� �����. ������� \"1\", \"2\" ��� \"3\": ");	
	}
	while (choice != 1 && choice != 2 && choice !=3);
	switch (choice)
	{
	case 1: fillArrayCoordByRandom(mas, N); break;
	case 2: fillArrayCoordByHand(mas, N); break;
	case 3: fillArrayByFile(mas, N, input); break;
	}
}
//���� ������� ��������.
void fillArrayCoordByRandom(coord* mas, int &N)
{
	printf("������� ���������� ��������������� N: ");
	do
	{
		scanf_s("%i", &N);
		if (N <= 0)
			printf("������� ����������� ����� �����: ");
	} while (N <= 0);
	int A, B;
	printf("������� ������� ������������ ����� A � �:\n");
	printf("A = "); scanf_s("%i", &A);
	printf("B = "); scanf_s("%i", &B);
	for (int i = 0; i < N; i++)
	{
		mas[i].x1 = rand() % (B - A + 1) + A;
		mas[i].y1 = rand() % (B - A + 1) + A;
		do
		mas[i].x2 = rand() % (B - A + 1) + A;
		while (mas[i].x2 < mas[i].x1);
		do
		mas[i].y2 = rand() % (B - A + 1) + A;
		while (mas[i].y2 > mas[i].y1);
	}
}
//���� ������� � ����������.
void fillArrayCoordByHand(coord* mas, int &N)
{
	printf("������� ���������� ��������������� N: ");
	do
	{
		scanf_s("%i", &N);
		if (N <= 0)
			printf("������� ����������� ����� �����: ");
	} while (N <= 0);
	for (int i = 0; i < N; i++)
	{
		printf("������� ���������� ����� ������ �������� � ������� ������� ���� %i-�� ��������������: \n", i + 1);
		printf("x1: "); scanf_s("%i", &mas[i].x1);
		printf("y1: "); scanf_s("%i", &mas[i].y1);
		do
		{
			printf("x2: ");
			scanf_s("%i", &mas[i].x2);
		} while (mas[i].x2 <= mas[i].x1);
		do
		{
			printf("y2: ");
			scanf_s("%i", &mas[i].y2);
		} while (mas[i].y2 >= mas[i].y1);
	}
}
//���������� ���������� �������.
int calculatingMostArea(coord* mas, int N)
{
	int index=0;
	float S;
	double t = 0;
	for (int i = 0; i < N; i++)
	{
		S = getArea(mas[i]);
		if (S > t)
		{
			t = S;
			index = i+1;
		}
	}
	return index;
}
//���������� �������.
float getArea(coord A)
{
	int S;
	S = (A.x2 - A.x1) * (A.y1 - A.y2);
	return S;
}
//���� ������� � ����.
int fillArrayByFile(coord* mas, int &N, FILE* input)
{
	if (fopen_s(&input, "input.txt", "r") != 0)
	{
		printf("File error!\n");
		return MY_ERROR_FILE;
	}

	fscanf_s(input, "%i", &N);

	for (int i = 0; i < N; i++)
	{
		fscanf_s(input, "%i", &mas[i].x1);
		fscanf_s(input, "%i", &mas[i].y1);
		fscanf_s(input, "%i", &mas[i].x2);
		fscanf_s(input, "%i", &mas[i].y2);
	}
	fclose(input);
}
//���������� ��������� �������.
int saveArray(coord* mas, int N, FILE* input)
{
	if (fopen_s(&input, "input.txt", "w") != 0)
	{
		printf("File error!");
		return MY_ERROR_FILE;
	}
	fprintf(input, "%i\n", N);
	for (int i = 0; i < N; i++)
	{
		fprintf(input, "%i ", mas[i].x1);
		fprintf(input, "%i ", mas[i].y1);
		fprintf(input, "%i ", mas[i].x2);
		fprintf(input, "%i\n", mas[i].y2);
	}
	fclose(input);
	return 0;
}
