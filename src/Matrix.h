#ifndef MATRIX_H
#define MATRIX_H
// Code adapted from suggestions at goo.gl/sF1SK4
/// \file
/// \brief Matrix class for 1D aray representation as a 2D array

#include <array>

/// \brief   Matrix class for a contiguous memory block
///
/// The 2d square matrix is stored as a single contigous array,
/// with getter and setter methods provided to allow 2d indexing
class Matrix
{
    int* array;
    int width;

public:
    /// \brief Constructor for a Matrix object
    /// \param The size of a single dimension
    /// \param The size of a single dimension
    /// \param The array will be [width x width]*32-bits size,
    /// in a contiguous block of memory
    Matrix(int N) : width(N),
                    array(new int[N * N]) {}

    /// \brief Returns the memory address of the array
    int* begin()
    {
        return &array[0];
    }

    /// \brief The getter method, with 2d indexing of elements
    /// \param The row index
    /// \param The column index
    int at(int x, int y)
    {
        return array[_index(x, y)];
    }

    /// \brief Returns a single dimension of the square matrix
    int size()
    {
        return width;
    }

    /// \brief The setter method, with 2d indexing of elements
    /// \param The row index
    /// \param The column index
    /// \param An unsigned 32-bit integer value inserted into the element
    void set(int x, int y, int val)
    {
        array[_index(x, y)] = val;
    }

    /// \brief Sets each element in the matrix to 0
    void zeroValues()
    {
        for(size_t i = 0; i < width*width; i++){
            this->array[i] = 0;
        }
    }

    /// \brief Sets each element in the matrix to
    /// a random 32-bit integer between 0 and 99
    void randomizeValues(int seed = static_cast<unsigned int>(time(NULL)))
    {
        const int max = 100;
        srand(seed+static_cast<unsigned int>(time(NULL)));
        for(size_t i = 0; i < width*width; i++){
            this->array[i] = rand() % max;
        }
    }

    /// \brief Sets each element in the matrix to
    /// its index (as a 32-bit integer)
    void orderedValues()
    {
        for(size_t i = 0; i < width*width; i++){
            this->array[i] = i;
        }
    }

    /// \brief Provides a standard in-place swap method, using
    /// a temporary value to swap the values at the indices in memory.
    /// When complete, A[x][y] <=> A[y][x]
    /// \param The row index
    /// \param The column index
    void swap(int x, int y)
    {
        int32_t temp = this->at(x, y);
        this->set(x, y, this->at(y, x));
        this->set(y, x, temp);
    }

    /// \brief Array-style indexing
    /// \param The index (or a row-major ordered 2d Matrix as a row vector)
    int &operator[](int i) {
        if( i > width*width ) {
            throw "Index out of bounds";
        }
        return array[i];
    }

protected:
    /// \brief Method of indexing the 1D array as a 2D matrix
    /// \param The row index
    /// \param The column index
    int _index(int x, int y) const
    {
        return x * width + y;
    } 
};

#endif