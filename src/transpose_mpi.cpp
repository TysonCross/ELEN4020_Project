#include <stdio.h>
#include <assert.h>
#include <mpi.h>
#include "Matrix.h"
#include "utilities.h"

int main (int argc, char* argv[]) {
    int N = 8;
    int procs = 4;
    int block = procs/2;

    assert(isPowerOfTwo(N));
    assert(N>4);
    Matrix global(N);       // global matrix

    int rank, size;         // rank of current process and no. of processes

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (size != procs) {
        fprintf(stderr,"%s only works with np=%d\n", argv[0], procs);
        MPI_Abort(MPI_COMM_WORLD,1);
    }

    if (rank == 0) {
//        global.randomizeValues();
        global.orderedValues();
        print2d(global);
    }

    // Create local sub-matrix
    Matrix local(N/block);

    // Create a new MPI type
    MPI_Datatype MPI_Matrix, MPI_SubMatrix;
    const int sizes[2] = {N,N};
    const int subsizes[2] = {N/block, N/block};
    const int starts[2] = {0,0};

    // Create the types
    MPI_Type_create_subarray(2, sizes, subsizes, starts, MPI_ORDER_C, MPI_INT, &MPI_Matrix);
    MPI_Type_create_resized(MPI_Matrix, 0, N/block*sizeof(uint32_t) , &MPI_SubMatrix);
    MPI_Type_commit(&MPI_SubMatrix);

    uint32_t *globalptr = NULL;
    if (rank == 0) globalptr = &(global[0]);

    /* scatter the array to all processors */
    int sendcounts[block*block];
    int displaces[block*block];

    if (rank == 0) {
        int offset = 0;
        for (int i=0; i<block*block; i++) {
            sendcounts[i] = 1;
        }
        for (int i=0; i<block; i++) {
            for (int j=0; j<block; j++) {
                displaces[i*block+j] = offset;
                offset += 1;
            }
            offset += ((N/block)-1)*block;
        }
    }

    MPI_Scatterv(globalptr, sendcounts, displaces, MPI_SubMatrix, &(local[0]),
                 N*N/(block*block), MPI_CHAR,
                 0, MPI_COMM_WORLD);

    // Print local data
    for (int p=0; p<size; p++) {
        if (rank == p) {
            printf("Local process on rank %d is:\n", rank);
            print2d(local);
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }

    //  Process local data
    for (int i=0; i<N/block; i++) {
        for (int j=0; j<N/block; j++) {
            local.set(i, j, rank);
        }
    }

    // Send back to rank 0
    MPI_Gatherv(&(local[0]), N*N/(block*block),  MPI_INT,
                globalptr, sendcounts, displaces, MPI_SubMatrix,
                0, MPI_COMM_WORLD);

    MPI_Type_free(&MPI_SubMatrix);

    if (rank == 0) {
        printf("Processed matrix:\n");
        print2d(global);
    }

//    MPI_Type_vector(rows, 1, cols, MPI_INT, &col);
//    MPI_Type_hvector(cols, 1, sizeof(int), col, &transpose);
//    MPI_Type_commit(&transpose);
//
//    MPI_Isend(&(send[0][0]), rows*cols, MPI_INT, 0, 1, MPI_COMM_WORLD,&req);
//    MPI_Recv(&(recv[0][0]), 1, transpose, 0, 1, MPI_COMM_WORLD, &status);
//
//    MPI_Type_free(&col);
//    MPI_Type_free(&transpose);

//    printf("Original:\n");
//    printarr(send,rows,cols);
//    printf("Received\n");
//    printarr(recv,rows,cols);

    MPI_Finalize();
    return 0;
}

