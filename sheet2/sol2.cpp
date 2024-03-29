#include "utils.cpp"
#include<iostream>
#include<vector>
#include<thread>

using namespace std; 

void matrixMultiply(const vector<vector<double>>& mat1, const vector<vector<double>>& mat2, vector<vector<double>>& result, int startRow, int endRow) {
    int n = mat1.size(); // rows in mat1
    int m = mat1[0].size(); //  columns in mat1
    int x = mat2.size(); // rows in mat2
    int y = mat2[0].size(); // columns in mat2

    if (m != x){ // checking if it is mathematically works .
        cerr << "Math error ." << endl;
        return ;
    }

    /* the main idea is taking a few numbers of rows from matrix 1 and multiply them by matrix 2 columns and son on ..*/

    // multiplication 
    for (int i = startRow; i < endRow; ++i) { // mat1 rows 
        for (int j = 0; j < y; ++j) {  // looping on mat2 columns 
            for (int k = 0; k < n; ++k) { // looping on each element in the row and column 
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }


    /* as in matrix multiplication we take row and column then multiply the row by column the 1st element by the 1st element the 2nd by the 2nd and so on ..*/
}


int main(){
    vector<vector<double>> mat1 = generateRandomMatrix(5 , 8 , 0 , 100); // rows , columns , minimum value , maximum value 
    vector<vector<double>> mat2 = generateRandomMatrix(8 , 7 , 0 , 100); // rows , columns , minimum value , maximum value 
    

    // getting matrecies dimensions 
    int numRows1 = mat1.size();
    int numCols1 = mat1[0].size();
    int numRows2 = mat2.size();
    int numCols2 = mat2[0].size();



/* then the next the same procedures as the previous question .*/

    vector<vector<double>> result(numRows1, vector<double>(numCols2, 0));
    int numThreads = 4;
    int chunkSize = numRows1 / numThreads;
    vector<thread> threads;

    for (int i = 0; i < numThreads; ++i) {
        int startRow = i * chunkSize;
        int endRow = (i == numThreads - 1) ? numRows1 : (i + 1) * chunkSize;
        threads.emplace_back(matrixMultiply, ref(mat1), ref(mat2), ref(result), startRow, endRow);
    }


    for (auto& t : threads) {
        t.join();
    }


    print_matrix(result);

}