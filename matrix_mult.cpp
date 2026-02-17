#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <iomanip>

using namespace std;
using namespace chrono;

vector<vector<int>> readMatrix(const string& filename, int size) {
    vector<vector<int>> matrix(size, vector<int>(size));
    ifstream file(filename);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            file >> matrix[i][j];
        }
    }
    file.close();
    return matrix;
}

void writeResult(const vector<vector<int>>& matrix, long long time, long long operations, const string& filename) {
    ofstream file(filename);
    file << "Результирующая матрица:\n";
    for (const auto& row : matrix) {
        for (int val : row) {
            file << setw(5) << val << " ";
        }
        file << "\n";
    }
    file << "\n";
    file << "Время выполнения: " << time << " мкс (" << time / 1000.0 << " мс)\n";
    file << "Объем задачи: " << operations << " операций\n";
    file << "Размер матрицы: " << matrix.size() << "x" << matrix.size() << "\n";
}

int main() {
    system("chcp 65001 > nul");
    int size;
    cout << "Введите размер матрицы: ";
    cin >> size;
    string base = "C:/Users/gayvo/OneDrive/Desktop/parallel/lab_1/";
    auto A = readMatrix(base + "matrix_a.txt", size);
    auto B = readMatrix(base + "matrix_b.txt", size);

    vector<vector<int>> C(size, vector<int>(size, 0));
    auto start = high_resolution_clock::now();

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();

    long long operations = 2LL * size * size * size;

    writeResult(C, duration, operations, base + "result.txt");

    cout << "Результат сохранен в " << base << "result.txt\n";
    cout << "Время выполнения: " << duration << " мкс\n";
    cout << "Объем задачи: " << operations << " операций\n";

    return 0;
}