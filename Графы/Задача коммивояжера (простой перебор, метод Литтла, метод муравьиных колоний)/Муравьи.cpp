#define _CRT_SECURE_NO_WARNINGS
#define ll long long

#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <limits.h>
#include <malloc.h>

#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <locale>
#include <string>
#include <vector>
#include <cstdio>
#include <random>
#include <deque>
#include <queue>
#include <stack>
#include <ctime>
#include <cmath>
#include <regex>
#include <tuple>
#include <map>
#include <set>

#define ALPHA 1
#define BETA 3
#define T_MAX 100
#define M 20
#define p 0.5
#define SIZE 1000000

struct ANT_TYPE
{
    int number;
    double length;
    int *array;
};

int ReadSize(double **, char[SIZE], int *);
int ReadMatrix(double **, char[SIZE], int *);
double Probability(int, ANT_TYPE, double **, double **, int);
void InitializationAnts(ANT_TYPE[M], int, int);
void InitializationLength(double **, double **, int);
void GenerationPheromon(double **, int);
void Pheromon(ANT_TYPE[M], double, double **, int);
ANT_TYPE AntColony(double **, int, int, int);
void PrintResult(ANT_TYPE);
using namespace std;

int ReadSize(double **D, char name[SIZE], int *n)
{
    FILE *input = NULL;
    int size = 0, j = 0;
    char ch = 0;

    if (fopen_s(&input, name, "rb") == NULL)
    {
        while (!feof(input))
        {
            ch = fgetc(input);
            if (ch == '\n')
            {
                size++;
                j = 0;
            }
            else if (ch == '\xff' || ch == '\r')
            {}
            else if (ch == ' ') j++;
            else if (ch == '-')
            {
                cout << "Граф содержит отрицательный вес ребра.\nНевозможно применение муравьиного алгоритма.\nДля продолжения нажмите любую клавишу...\n";
                _getch();
                return 0;
            }
        }
        fclose(input);
        *n = size;
    }
    else
    {
        cout << "Ошибка: невозможно открыть файл.\nДля продолжения нажмите любую клавишу...\n";
        _getch();
        return 0;
    }
    return size;
}
int ReadMatrix(double **D, char name[SIZE], int *n)
{
    FILE *input = NULL;
    int size = ReadSize(D, name, n);
    if (fopen_s(&input, name, "rb") == NULL)
    {
        for (int t = 0; t < size; ++t)
            for (int k = 0; k < size; ++k)
            {
                int num;
                fscanf_s(input, "%d", &num);
                D[t][k] = num;
                if (t != k && D[t][k] == 0)
                    D[t][k] = INFINITY;
            }
        fclose(input);
    }
    return size;
}
double Probability(int to, ANT_TYPE ant, double **tao, double **epsilon, int size)
{
    double res = 0.0, sum = 0.0;
    int from = ant.array[ant.number - 1];
    for (int i = 0; i < ant.number; ++i)
        if (to == ant.array[i])
            return 0.0;
    for (int j = 0; j < size; ++j)
    {
        int flag = 1;
        for (int i = 0; i < ant.number; ++i)
            if (j == ant.array[i]) flag = 0;
        if (flag && from >= 0)
            sum += pow(tao[from][j], ALPHA) * pow(epsilon[from][j], BETA);
    }
    if (from >= 0) res = pow(tao[from][to], ALPHA) * pow(epsilon[from][to], BETA) / sum;
    return res;
}
void InitializationLength(double **epsilon, double **D, int size)
{
    for (int i = 0; i < size; ++i)
    {
        epsilon[i] = (double *)malloc(sizeof(double) * size);
        for (int j = 0; j < size; ++j)
            if (i != j) epsilon[i][j] = 1.0 / D[i][j];
    }
}
void GenerationPheromon(double **tao, int size)
{
    srand((unsigned)time(NULL));
    for (int i = 0; i < size; ++i)
    {
        tao[i] = (double *)malloc(sizeof(double) * size);
        for (int j = 0; j < size; ++j)
            tao[i][j] = 1 + (size * rand() / RAND_MAX);
    }
}

void InitializationAnts(ANT_TYPE ants[M], int size, int city_1)
{
    for (int k = 0; k < M; ++k)
    {
        ants[k].number = 0;
        ants[k].length = 0.0;
        ants[k].array = (int *)malloc(sizeof(int) * size);
        ants[k].array[ants[k].number++] = city_1;
    }
}
void Pheromon(ANT_TYPE ants[M], double Q, double **tao, int k)
{
    for (int i = 0; i < ants[k].number - 1; ++i)
    {
        int from = ants[k].array[i % ants[k].number];
        int to = ants[k].array[(i + 1) % ants[k].number];
        tao[from][to] += Q / ants[k].length;
        tao[to][from] = tao[from][to];
    }
}
ANT_TYPE AntColony(double **D, int size, int city_1, int city_2)
{
    ANT_TYPE way;
    way.number = 0;
    way.length = -1;
    way.array = (int *)malloc(sizeof(int) * size);
    double Q = 1.0;
    ANT_TYPE ants[M];
    double **epsilon = NULL, **tao = NULL;
    epsilon = (double **)malloc(sizeof(double *) * size);
    tao = (double **)malloc(sizeof(double *) * size);
    InitializationLength(epsilon, D, size);
    GenerationPheromon(tao, size);
    InitializationAnts(ants, size, city_1);

    for (int t = 0; t < T_MAX; ++t)
    {
        for (int k = 0; k < M; ++k)
        {
            do
            {
                int J_max = -1;
                double P_max = 0.0;
                for (int j = 0; j < size; ++j)
                    if (ants[k].array[ants[k].number - 1] != j)
                    {
                        double P = Probability(j, ants[k], tao, epsilon, size);
                        if (P != 0 && P >= P_max)
                        {
                            P_max = P;
                            J_max = j;
                        }
                    }
                if (J_max >= 0)
                {
                    ants[k].length += D[ants[k].array[ants[k].number - 1]][J_max];
                    ants[k].array[ants[k].number++] = J_max;
                }
            } while (ants[k].array[ants[k].number - 1] != city_2);

            Pheromon(ants, Q, tao, k);

            if (ants[k].length < way.length || way.length < 0)
            {
                way.number = ants[k].number;
                way.length = ants[k].length;
                for (int i = 0; i < way.number; ++i)
                {
                    way.array[i] = ants[k].array[i];
                }
            }
            ants[k].number = 1;
            ants[k].length = 0.0;
        }
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                if (i != j)
                {
                    tao[i][j] *= (1 - p);
                }
            }
        }
    }
    free(epsilon);
    free(tao);
    return way;
}
void PrintResult(ANT_TYPE way)
{
    system("cls");
    cout << "Путь: " << ++way.array[0];
    for (int i = 1; i < way.number; ++i) 
        cout << " -> " << ++way.array[i]; 
    cout << "\nДлинна пути: " << way.length << endl;
    cout << "Для продолжения нажмите любую клавишу..." << endl;
}

void main()
{
    setlocale(LC_ALL, "Russian");
    double **D = NULL;
    int size = 0, city_1 = 0, city_2 = 0;
    char name[SIZE];
    cout << "Введите путь файла: ";
    scanf_s("%s", name, SIZE);
    size = ReadSize(D, name, &size);
    D = new double *[size];
    for (int t = 0; t < size; t++) 
        D[t] = new double[size]; 
    for (int k = 0; k < size; k++)
        for (int r = 0; r < size; r++) D[k][r] = 0.0;
    ReadMatrix(D, name, &size);

    while (city_1 < 1 || city_1 > size)
    {
        cout << "Введите начальную вершину от 1 до " << size << ": ";
        cin >> city_1;
    }
    while (city_2 < 1 || city_2 > size || city_2 == city_1)
    {
        cout << "Введите конечную вершину от 1 до " << size << ", исключая " << city_1 << ": ";
        cin >> city_2;
    }
    ANT_TYPE way = AntColony(D, size, --city_1, --city_2);
    PrintResult(way);
    _getch();
    delete[] D;

    return;
}