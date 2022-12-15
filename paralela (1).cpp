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

    static double x[N][M], y[M][O], z[M][O];

    auto t3 = std::chrono::high_resolution_clock::now();
    //Iniciando bloco paralelo, definindo as variaveis N, x, y, z como compartilhadas e 
    //i, j, jj, kk como variaveis privadas
    #pragma omp parallel default(none) shared (N, x, y, z) private (i, j, jj, kk)
    {
        //Preenchimento da matriz utilizando paralelismo
        #pragma omp for
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
    }
    //Fim do bloco paralelo
    auto t4 = std::chrono::high_resolution_clock::now();
    
    auto duration2 = (std::chrono::duration_cast<std::chrono::microseconds>(t4-t3).count());

    float time2 = (float)duration2/1000000;

    std::cout << "Tempo de processamento com otimizacao da memoria =" << time2 << "segundos." <<std::endl;





}