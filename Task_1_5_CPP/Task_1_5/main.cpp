#include <iostream>

struct Matrix {
    int** data;
    int rows;
    int cols;
};

void allocateMatrix(Matrix& mat, int rows, int cols) {
    mat.rows = rows;
    mat.cols = cols;

    mat.data = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        mat.data[i] = new int[cols];
    }
}

void deallocateMatrix(Matrix& mat) {
    for (int i = 0; i < mat.rows; ++i) {
        delete[] mat.data[i];
    }
    delete[] mat.data;
}

void fillMatrix(Matrix& mat) {
    for (int i = 0; i < mat.rows; ++i) {
        for (int j = 0; j < mat.cols; ++j) {
            std::cin >> mat.data[i][j];
        }
    }
}

void changeMatrix(const Matrix& mat) {
    int min = mat.data[0][0], max = mat.data[0][0], mini=0, maxi=0;
    for (int i = 0; i < mat.rows; ++i) {
        for (int j = 0; j < mat.cols; ++j) {
            if (mat.data[i][j] <= min){
                min = mat.data[i][j];
                mini = i;
            }
            if (mat.data[i][j] >= max){
                max = mat.data[i][j];
                maxi = i;
            }
        }
    }
    int* temp = mat.data[maxi];
    mat.data[maxi] = mat.data[mini];
    mat.data[mini] = temp;
}

void printMatrix(const Matrix& mat) {
    std::cout << "Matrix:\n";
    for (int i = 0; i < mat.rows; ++i) {
        for (int j = 0; j < mat.cols; ++j) {
            std::cout << mat.data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


int main() {
    int rows, cols;
    std::cout << "Enter number of rows:";
    std::cin >> rows;
    std::cout << "Enter number of cols:";
    std::cin >> cols;

    Matrix mat;
    allocateMatrix(mat, rows, cols);

    fillMatrix(mat);
    changeMatrix(mat);
    printMatrix(mat);

    deallocateMatrix(mat);

    return 0;
}

