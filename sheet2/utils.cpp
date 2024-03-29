/* this is utils file it just including some helper functions to help generating metrices and vectors for testing purposes*/

#include <iostream>
#include <vector>
#include <random>

using namespace std ;

vector<vector<double>> generateRandomMatrix(int rows, int cols, double minVal, double maxVal) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(minVal, maxVal);

    /* in the previous lines we are intianting a random generator from a distribution to get random values*/

    // intaiting a matrix
    vector<vector<double>> matrix(rows, vector<double>(cols));

    /* looping on our matrix and putting random values*/
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = dis(gen);
        }
    }

    return matrix;
}



/* printing matrix */
void print_matrix(vector<vector<double>> matrix) {
    for (const auto& row : matrix) {
        for (double value : row) {
            cout << value << " ";
        }
        cout << endl;
    }
}


/* --------------------------------- generating random vector -----------------------------------------------*/

vector<double> generateRandomVector(int size, double minVal, double maxVal) {

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(minVal, maxVal);

    vector<double> vec(size);
    for (int i = 0; i < size; ++i) {
        vec[i] = dis(gen);
    }

    return vec;
}

// printing vector 
void print_vector(vector<double> vec){

    for (double value : vec) {
        cout << value << " ";
    }
    cout << endl;
} 

