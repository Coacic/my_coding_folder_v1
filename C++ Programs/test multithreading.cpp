#include <stdio.h>
#include <iostream>
#include <math.h>
#include <fstream>
#include <chrono>
#include <thread>

#define INT_MAX 2147483647

void calculate(int n, int m, std::istream &in)
{
    double i = 0.0, j = 0.0, k = 0.0, x = 0.0, y = 0.0, z = 0.0, rezultat = 0.0;
    int position = n;
    in.clear();
    in.seekg(n);
    for (int i = n; i < m; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        in >> i >> j >> k >> x >> y >> z;
        rezultat = pow(i * i * i * i * i * i + j * j * j * j * j * j + k * k * k * k * k * k + x * x * x * x * x * x + y * y * y * y * y * y + z * z * z * z * z * z, 6);
        if (rezultat - (int)rezultat == 0)
        {
            std::cout << i << "^6 + " << j << "^6 + " << k << "^6 + " << x << "^6 + " << y << "^6 + " << z << "^6 "
                      << " = " << rezultat << std::endl;
        }
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        //std::cout << "Odradjena je " << i << "-ta iteracija za " << duration.count() << " milisekundi" << std::endl;
    }
    std::cout << "Zavrsena iteracija od " << n << " do " << m << std::endl;
}

int main()
{
    double rezultat = 0.0;
    double i = 0, j = 0, k = 0, n = 0, pom = 1, a = 1, b = 1, c = 1, inc = 1, br = 0, o = 1, d = 1, f = 1, g = 1, h = 1;
    int i1 = 0, i2 = 0, i3 = 0, i4 = 0, div = 0;
    int m = 0;
    std::ofstream out;
    std::ifstream in;
    in.open("primeri.txt");
    //C Reading a File
    int num = 0;
    FILE *fp = fopen("primeri.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    char *line = NULL;
    size_t len = 0;
    while ((getline(&line, &len, fp)) != -1)
    {
        num++;
    }
    fclose(fp);
    if (line)
        free(line);
    //
    std::cout << "File ima " << num << " redova!" << std::endl;
    i1 = num / 4;
    i2 = i1 * 2;
    i3 = i1 * 3;
    i4 = i1 * 4;

    //Threading
    std::thread th1(calculate, 0, i1, in);
    // std::thread th2(calculate, i1, i2, in);
    // std::thread th3(calculate, i2, i3, in);
    // std::thread th4(calculate, i3, i4, in);

    th1.join();
    // th2.join();
    // th3.join();
    // th4.join();

    getchar();
    in.close();
    //out.close();
    return 0;
}