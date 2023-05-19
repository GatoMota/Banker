#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Globales
const int n = 5, m = 3; // El profe nos pide n=6 hay que cambiarlo, esto es solo una base o 

// Calcula la matriz need (max - alloc)
void calcular_need(int need[n][m], int max[n][m], int alloc[n][m]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
}

// Aquí avaliable[j] es nuestro "work"
// si need <= work return true
bool comparar_need_work(int i, int need[n][m], int available[m]) {
    for (int j = 0; j < m; j++) {
        if (!(need[i][j] <= available[j])){ // need > work return false
            return false;
        }
    }
    return true;
}

int main(void) {
    // matriz nxm e.g: 5x3

    // 3 matrices y 1 array
    //int need[n][m], alloc[n][m], max[n][m], available[n];
    int alloc[n][m] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };
    int max[n][m] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };
    int available[m] = {3, 3, 2};
    int need[n][m];
    vector<int> secuencia;
    bool seguro = true;
    // Obtener matriz need
    calcular_need(need, max, alloc);

    int index = 0;
    int aux = -1;
    while (secuencia.size() < n) {
        if(index >= n) index = 0;
        // Si secuencia contiene index, entonces index++
        if(find(secuencia.begin(), secuencia.end(), index) != secuencia.end()) {
            aux = index;
            index++;
            continue;
        }
        // Si need <= available
        if(comparar_need_work(index, need, available)) {
            // work += alloc
            for (int j = 0; j < m; j++) {
                available[j] += alloc[index][j];
            }
            secuencia.push_back(index);
        } else if(index == aux){
            seguro = false;
            break;
        }
        aux = index;
        index++;
    }

    for (auto element : secuencia) {
        cout << element << " ";
    }
    exit(EXIT_SUCCESS);
}