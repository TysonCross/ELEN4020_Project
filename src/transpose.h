#ifndef TRANSPOSE_H
#define TRANSPOSE_H
/// \file
/// \brief The in-place matrix transposition algorithms (Definitions)

#include <omp.h>
#include <pthread.h>
#include "utilities.h"

using namespace std;

/// \brief Transposes a matrix, using serial algorithm
/// \param The matrix to transpose
void transposeMatrixSerial(Matrix A);


// \brief Transposes a matrix, using OpenMP block-oriented algorithm
//  with a thread per "block"
/// \param The matrix to transpose
void transposeMatrixBlockOpenMP(Matrix A);

#endif