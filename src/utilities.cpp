#include "utilities.h"
#include "Matrix.h"
/// \file
/// \brief Various output/validation methods for confirming transposition (Implementation)

bool isPowerOfTwo(uint32_t x)
{
    return x!=0 && (x & (x - 1)) == 0;
}

void print2d(Matrix A){
    const auto N = A.size();
    cout << N << "x" << N << endl;
    for (auto i = 0; i < N; i++){
        for (auto j = 0; j < N; j++){
            cout << A.at(i, j) << "\t";
        }
        cout << endl;
    }
}

void writeMatrixToFile(string fileName, Matrix A)
{
    ofstream outputFile(fileName, ios::out | ios::trunc);
    if (!outputFile.is_open()){
        cout << "Unable to open file:" << fileName << endl;
    }
    const auto N = A.size();
    outputFile << N << endl;
    for (auto i = 0; i < N; i++){
        for (auto j = 0; j < N; j++){
            outputFile << A.at(i, j) << "\t";
        }
        outputFile << endl;
        }
    outputFile.close();
}

Matrix readMatrixfromFile(string fileName)
{
    ifstream inputFile(fileName, ios::in);
    if (!inputFile.is_open()){
        cout << "Unable to open file:" << fileName << endl;
    }
    inputFile.seekg(0, ios::beg);

    int N;
    uint32_t val;
    inputFile >> N;
    Matrix A(N);

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            inputFile >> val;
            A.set(i, j, val);
        }
    }
    return A;
}

bool matricesAreEqual(Matrix A, Matrix B)
{    
    const auto N = A.size();
    const auto M = B.size();
    if (N!=M) {
        cout << "Error: Matrix sizes do not match" << endl;
        return -1;
    }
    for (auto i = 0; i < N; i++){
        for (auto j = 0; j < N; j++){
            if (A.at(i, j) != B.at(i, j)){
                cout << "Error: Matrix sizes do not match at (" << i << "," << j << ")" << endl;
                return 0;
            }
        }
    }
    return 1;
}

string getEnvironmentVar( string const& env_val )
{
    char* val = getenv( env_val.c_str() );
    return val == NULL ? string("") : string(val);
}

int getNumThreadsEnvVar()
{
    int num_threads_default = 8;
    string const val = "OMP_NUM_THREADS";
    return getEnvironmentVar(val) == "" ? num_threads_default : stoi(getEnvironmentVar(val));
}