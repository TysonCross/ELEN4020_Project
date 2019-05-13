#include <stdio.h>
#include <mpi.h>

int main (int argc, char ** argv)
{
    int rank, size;

    MPI_Init(&argc, &argv);

    MPI_Type_vector(rows, 1, cols, MPI_INT, &col);
    MPI_Type_hvector(cols, 1, sizeof(int), col, &transpose);
    MPI_Type_commit(&transpose);

    MPI_Isend(&(send[0][0]), rows*cols, MPI_INT, 0, 1, MPI_COMM_WORLD,&req);
    MPI_Recv(&(recv[0][0]), 1, transpose, 0, 1, MPI_COMM_WORLD, &status);

    MPI_Type_free(&col);
    MPI_Type_free(&transpose);

    printf("Original:\n");
    printarr(send,rows,cols);
    printf("Received\n");
    printarr(recv,rows,cols);



    $ mpirun -np 1 ./transpose2
    Original:
      0   1   2   3   4   5   6
     10  11  12  13  14  15  16
     20  21  22  23  24  25  26
     30  31  32  33  34  35  36
     40  41  42  43  44  45  46
     50  51  52  53  54  55  56
     60  61  62  63  64  65  66
    Received
      0  10  20  30  40  50  60
      1  11  21  31  41  51  61
      2  12  22  32  42  52  62
      3  13  23  33  43  53  63
      4  14  24  34  44  54  64
      5  15  25  35  45  55  65
      6  16  26  36  46  56  66
  }