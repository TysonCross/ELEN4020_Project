#include <math.h>
#include "transpose.h"
/// \file
/// \brief The in-place matrix transposition algorithms  (Implementation)

struct matrix_args{
         Matrix *matrix;
         int row_start;
         int row_end;
};


void transposeMatrixBlockOpenMP(Matrix A)
{
    auto N = A.size();
    auto stride = 2;
    #pragma omp parallel for
    for(auto row = 0; row < N; row+=stride) {
        for(auto col = 0; col <= row; col+=stride) {
            if (row == col) {
                uint32_t temp1 = A.at(row+1, col);
                A.set(row+1, col, A.at(row, col+1));
                A.set(row, col+1, temp1);
            } else {
                for(auto i = 0; i < stride; i++){
                    for(auto j = 0; j < stride; j++) {
                        uint32_t temp = A.at(col+j, row+i);
                        A.set(col+j, row+i, A.at(row+i, col+j));
                        A.set(row+i, col+j, temp);
                    }
                }
            }
        }
    }
}



