#ifndef UTILITIES_H
#define UTILITIES_H
/// \file
/// \brief Various output/validation methods for confirming transposition (Definitions)

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <fstream>
#include <vector>
#include "Matrix.h"

using namespace std;


/// \brief Checks if a value is a power of two
/// \param Value to check (unsigned 32-bit integer)
bool isPowerOfTwo(uint32_t x);

/// \brief Prints an NxM matrix
/// \param The matrix to print
void print2d(Matrix A);

/// \brief Caches a matrix to disk
/// \param Path to the cache file to write (replaces contents)
/// \param The matrix to cache to disk
void writeMatrixToFile(string fileName, Matrix A);

/// \brief Reads a matrix into memory from disk
/// \param Path to the cache file to read
Matrix readMatrixfromFile(string fileName);

/// \brief Compares two matrices to check if all elements are the same
/// \param The first matrix to compare to
/// \param The second matrix to compare with
bool matricesAreEqual(Matrix A, Matrix B);

/// \brief Returns an Environmental Variable from
string getEnvironmentVar(string const& env_val);

/// \brief Returns the number of threads from OP_NUM_THREADS (if empty, returns 8)
int getNumThreadsEnvVar();

#endif