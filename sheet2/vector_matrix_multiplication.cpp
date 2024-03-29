#include "utils.cpp"
#include<iostream>
#include<vector>

using namespace std; 


vector<double> vectorMatrixMultiply(const vector<double> vec, const vector<vector<double>> mat) {
    int vecSize = vec.size(); // vec size is how many columns(n) in the vector(1 * n)
    int matrixRows = matrix.size(); // calculating how many rows in the matrix 
    int matrixCols = matrix[0].size(); // caluclting how many columns in the martix by getting the size one row vectors 

    // there will be an error if number of columns of the vector != the number of matrix rows 
    if (vecSize != matrixRows) {
        // cerr is an error message ostream method check it from here => https://www.programiz.com/cpp-programming/library-function/iostream/cerr
        cerr << "Math error ." << endl;
        return vector<double>();
    }


    /* the result from a vector matrix multiplication is a vector of the size of the matrix columns 
    here we are intiating this vector      */
    vector<double> result(matrixCols, 0.0);


    // applying multiplication
    for (int i = 0; i < matrixCols; ++i) {
        for (int j = 0; j < vecSize; ++j) {
            result[i] += vec[j] * matrix[j][i];
        }
    }

    return result;
}



int main(){

    vector<double> vec = generateRandomVector(10 , 0 , 100);
    print_vector(vec);
}