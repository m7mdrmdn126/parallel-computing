#include "utils.cpp"
#include<iostream>
#include<vector>
#include<thread>

using namespace std; 


void vectorMatrixMultiply(const vector<double> vec, const vector<vector<double>> mat , vector<double>& result, int start , int end) {
    int vecSize = vec.size(); // vec size is how many columns(n) in the vector(1 * n)
    int matrixRows = mat.size(); // calculating how many rows in the matrix 

    // there will be an error if number of columns of the vector != the number of matrix rows 
    if (vecSize != matrixRows) {
        // cerr is an error message ostream method check it from here => https://www.programiz.com/cpp-programming/library-function/iostream/cerr
        cerr << "Math error ." << endl;
        return ;
    }


    // applying multiplication
    for (int i = start; i < end; ++i) {
        for (int j = 0; j < vecSize; ++j) {
            result[i] += vec[j] * mat[j][i];

        }
    }

    /* the main idea is multiplying number of columns with the vector in each thread generating the result compined in the result vector*/
}



int main(){

    vector<double> vec = generateRandomVector(10 , 0 , 100); // size , minimum value , maximum value 
    vector<vector<double>> mat = generateRandomMatrix(10 , 10 , 0 , 100); // rows , columns , minimum value , maximum value 

    int numThreads = 5;
    int chunkSize = mat[0].size() / numThreads; // dividing the number of columns on the therads 

    vector<thread> threads;
    vector<double> result(mat[0].size(), 0.0); // Initialize result vector with zeros 

    // Launchinf the threads by specifing each thread amount of work 
    for (int i = 0; i < numThreads; ++i) {
        int startCol = i * chunkSize; // start number in this case it start with 0 , 2 , 4 , etc...
        int endCol = (i == numThreads - 1) ? mat[0].size() : (i + 1) * chunkSize; 
        /* the one above is an expression has been mentioned in the lecture (ternary expression) spot this link to see an explainantion => https://www.w3schools.com/cpp/cpp_conditions_shorthand.asp*/
        /* this means that if the thread is the last one return the column size as all of the remaining columns otherwise return the next chunck */
        threads.emplace_back(vectorMatrixMultiply, ref(vec), ref(mat), ref(result), startCol, endCol);
        /* adding thread to the threads vector to control all the threads */
    }


    for (auto& thread : threads){
        thread.join();
    }


    print_vector(result);

}