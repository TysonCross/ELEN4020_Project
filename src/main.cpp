#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdexcept>
#include <mpi.h>
#include "Matrix.h"
#include "utilities.h"
#include "transpose.h"

int main (int argc, char* argv[]) {

    // Get N from the commandline
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << "<N> (power of 2 greater than 4)" << endl;
        return -1;
    }
    int N;
    string arg = argv[1];
    try
    {
        size_t pos;
        N = stoi(arg, &pos);
        if (pos < arg.size())
        {
            cerr << "Trailing characters after number: " << arg << endl;
            return -1;
        }
        if (!isPowerOfTwo(N))
        {
            cerr << "N must be a power of two" << endl;
            return -1;
        }
        if (N < 4)
        {
            cerr << "N must be >= 4" << endl;
            return -1;
        }
    } catch (invalid_argument const &ex) {
        cerr << "Invalid number: " << arg << '\n';
    } catch (out_of_range const &ex) {
        cerr << "Number out of range: " << arg << '\n';
    }

    //  Output timing file setup
    const string timing_file_name = string("matrixFile_") + to_string(N) + "_timing.txt";
    ofstream timing_file(timing_file_name, ios::out | ios::app);
    if (!timing_file.is_open()) { cerr << "Unable to open file:" << timing_file_name << endl; return -1;}
    const auto width = 20;  // File formatting

    // MPI number of processors setup
    const int procs = 4;
    const int block = procs/2;
    double t1, t2;

    // Create matrices
    Matrix global(N);                   // global matrix
    global.zeroValues();                // <- not required, but useful (zeros out values)
    Matrix local( N / block);           // <- each rank has a local [N/2 x N/2] submatrix, for a quadrant of the main matrix
    Matrix validation(N);               // validation of transpose

    // MPI setup
    int rank, size;         // rank of current process and no. of processes
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (size != procs)
    {
        fprintf(stderr, "%s only works with np=%d\n", argv[0], procs);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    if (rank == 0) {
        cout << endl << "Process begin: " << N << "x" << N << " matrix" << endl;
        cout << "   Generating (" << procs << ") " << N/2 << "x" << N/2 <<  " local sub-matrices" << endl;
        t1 = MPI_Wtime();       // Start timing operation from here
    }

    // Generate local block values
    local.randomizeValues(rank);          // each block generates values

    // Create a new MPI type (a 2d array)
    MPI_Datatype MPI_Matrix, MPI_SubMatrix;
    const int sizes[2] = {N, N};
    const int subsizes[2] = {N / block, N / block};
    const int starts[2] = {0, 0};

    // Create the types (the main 2d MPI_matrix, and the quadrant sub-matrix type, derived from MPI_UINT21_T
    // The ordering is using MPI_ORDER_C, which is row-major on a contiguous block of memory,
    // This matches the Matrix.h memory layout.
    MPI_Type_create_subarray(2, sizes, subsizes, starts, MPI_ORDER_C, MPI_INT, &MPI_Matrix);
    MPI_Type_create_resized(MPI_Matrix, 0, N / block * sizeof(int), &MPI_SubMatrix);
    MPI_Type_commit(&MPI_SubMatrix);

    int *globalptr = NULL;
    if (rank == 0) globalptr = global.begin();

    // Calculate the memory offsets for the array to send/receive from all processors
    int sendcounts[block * block];
    int displaces_send[block * block];
    int displaces_receive[block * block];

    // Setup the offsets in memory to send to local
    if (rank == 0) {
        int offset = 0;
        for (int i = 0; i < block * block; i++)
        {
            sendcounts[i] = 1;
        }
        for (int i = 0; i < block; i++)
        {
            for (int j = 0; j < block; j++)
            {
                displaces_send[i * block + j] = offset;
                offset += 1;
            }
            offset += ((N / block) - 1) * block;
        }

        // Setup the offsets in memory to put back into global
        displaces_receive[0] = displaces_send[0];
        displaces_receive[1] = displaces_send[2];
        displaces_receive[2] = displaces_send[1];
        displaces_receive[3] = displaces_send[3];
    }

    // get the locally generated values for the matrix and collect into global
    MPI_Gatherv(local.begin(), N * N / (block * block), MPI_INT,
                globalptr, sendcounts, displaces_send, MPI_SubMatrix,
                0, MPI_COMM_WORLD);

    if (rank == 0) {
        // write to disk
        string matrixfile_in = string("matrixFile_") + to_string(N) + ".txt";
        writeMatrixToFile(matrixfile_in, global);

        // read the matrix in for later validation:
        validation = readMatrixfromFile(matrixfile_in);

        // Shell output
        cout << "   Global matrix written to " <<  matrixfile_in << endl;
        cout << "   Transposing matrix across " << procs << " processors..." << endl;
        // Timings file headings:
        timing_file << setw(width) << left << N;
    }

    // Scatter transposed sub-matrices
    MPI_Scatterv(globalptr, sendcounts, displaces_send, MPI_SubMatrix, &(local[0]),
                 N * N / (block * block), MPI_UINT32_T,
                 0, MPI_COMM_WORLD);

    //  Process local data
    transposeMatrixBlockOpenMP(local);

    // Gather back to rank 0
    MPI_Gatherv(local.begin(), N * N / (block * block), MPI_INT,
                globalptr, sendcounts, displaces_receive, MPI_SubMatrix,
                0, MPI_COMM_WORLD);

    // Free the derived type
    MPI_Type_free(&MPI_SubMatrix);

    if (rank == 0)
    {
        t2 = MPI_Wtime();
        auto time_taken = t2 - t1;     // record the time delta

        // Transposition validation matrix with guaranteed, local method
        transposeMatrixSerial(validation);
        try{
            if(!matricesAreEqual(global, validation)){
                throw N;
            } else {
                cout << "   Operation verified!" << endl;
                cout << "   Transposition completed in " << time_taken << " sec" << endl;
            }
        } catch (int i){
            cerr << "Error: Matrix of size " << i << " was not correctly transposed. Aborting." << endl;
            timing_file.close();
            remove(timing_file_name.c_str());
            MPI_Abort(MPI_COMM_WORLD, 1);
            return i;
        }

        timing_file << setw(width) << left << setprecision(7) << fixed << time_taken << endl;

        // Write transposed Matrix to file
        string matrixfile_transpose = string("matrixFile_") + to_string(N) + "_transpose.txt";
        writeMatrixToFile(matrixfile_transpose, global);
        cout << "   Transposed matrix written to " <<  matrixfile_transpose << endl;
        cout << "   Timing appended to " <<  timing_file_name << endl;
        cout << "Process complete." << endl << endl;

    }

    // clean up
    timing_file.close();
    MPI_Finalize();
    return 0;
}

