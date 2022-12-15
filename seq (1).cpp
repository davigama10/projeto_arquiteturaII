#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <ctime>

#include <chrono>
#include <iostream>

const long N = 600;
const long M = 600;
const long O = 600;
double step;

int main(){
    //Criando matrizes 600x600
    static double x[N][M], y[M][O], z[M][O];

    //Etapa com acesso à memória de maneira não otimizada//
    //Preenchendo essas matrizes
    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            x[i][j] = rand() % 10;
            for (int k = 0; k < O; k++) {
                y[j][k] = rand() % 10;
                z[j][k] = rand() % 10;
            }
        }
    }
    

    auto t2 = std::chrono::high_resolution_clock::now();

    //Otimização da memória utilizando blocagem//
    auto t3 = std::chrono::high_resolution_clock::now();


    //Preenchendo as matrizes//
    for (int jj = 0; jj < M; jj = jj + 2) {
        for (int kk = 0; kk < O; kk = kk + 2) {
            for (int i = 0; i < N; i = i + 1) {
                for (int j = jj; j < jj + 2 - 1; j = j + 1) {
                    x[i][j] = rand() % 10;
                    for (int k = kk; k < kk + 2 - 1; k = k + 1) {
                        y[j][k] = rand() % 10;
                        z[j][k] = rand() % 10;
                     }
                }
            }
        }
    }

    auto t4 = std::chrono::high_resolution_clock::now();

    auto duration = (std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count());
    auto duration2 = (std::chrono::duration_cast<std::chrono::microseconds>(t4-t3).count());


    float time = (float)duration/1000000;
    float time2 = (float)duration2/1000000;


    std::cout << "Tempo de processamento =" << time << "segundos." <<std::endl;
    std::cout << "Tempo de processamento com otimizacao da memoria =" << time2 << "segundos." <<std::endl;





}