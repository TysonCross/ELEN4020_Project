/*
 * This program demonstrates the use of MPI_Bcast, MPI_Reduce and
 * MPI_Allreduce
 */

#include <stdio.h>
#include <mpi.h>

int
main (int argc, char *argv[])
{
    int nprocs;			/* number of processes */
    int rank;			/* the unique identification of this process */

    int i, mysum, sum, imin, imax;
    const int N = 60;

    /* initialize the MPI environment: */

    MPI_Init (&argc, &argv);	/* note: use argc and argv yourself only
				 * after this call */

    MPI_Comm_rank (MPI_COMM_WORLD, &rank);	/* rank will be different for
						 * all processes */
    MPI_Comm_size (MPI_COMM_WORLD, &nprocs);	/* nprocs will be the same for
						 * all processes */

    /* because a number of processes are executing this code now,
     * the next statement will cause a number of lines to be
     * printed, one line for each process. In general, this is
     * not the way to print in a MPI program, because the processes
     * print independently and lines can get mixed up.
     * In a real program, in general the printing is done by
     * one process, most of the time process 0. For debugging
     * and demonstration purposes however, printing by all
     * processes is of great value */

    printf ("Hello, this is process %d of a total of %d\n", rank, nprocs);

    /* Here follows the first example of a real parallel program:
     * We want to compute the sum of the first 60 integers.
     * Each process will perform part of the work: for example
     * with 4 processes: process 0 will sum up the numbers 1 to 15,
     * process 1 the numbers 16 to 30, and so on.
     * After this, the partial sums are summed up and the result
     * is printed */

    /* for simplicity we assume that N is divisible by the number
     * of processes. A generalization of this program is left as an
     * exercise for the reader */

    /* which numbers are to be added in this process: */

    imin = (N / nprocs) * rank + 1;
    imax = imin + N / nprocs -1;

    mysum = 0;			/* mysum will contain the sum of the numbers
				 * imin .. imax */
    for (i = imin; i <= imax; i++)
        mysum += i;

    /* Now, each process has it's own partial sum: mysum
     * We want that the process with rank equal to 0 will receive the
     * sum of the partials sums. MPI_Reduce is used for this: */

    MPI_Reduce (&mysum,		/* the partial sum */
                &sum,		/* the total sum */
                1,		/* the number of elements in sum, in this
				 * case one int */
                MPI_INT,		/* the type of sum: int. Other types are for
				 * example:
				 * MPI_DOUBLE
				   MPI_FLOAT    */
                MPI_SUM,		/* we want to sum the partial sums. Other
				 * operations are for example:
				 * MPI_MAX    find the maximum value
				 * MPI_MIN    find the minimum value
				 * MPI_PROD   find the product
				 */
                0,		/* the rank of the process that is going
				   to receive the sum. */
                MPI_COMM_WORLD	/* the communicator */
    );

    /* Now the sum of all mysum's is available on process 0 in
       variable sum */

    /* let's print it: */

    if (rank == 0)
        printf ("process zero reports: sum is %d\n", sum);

    /* Let's try to communicate the value of sum to all processes
     * using MPI_Bcast, a broadcasting subroutine: */

    MPI_Bcast (&sum,		/* the value to broadcast */
               1,			/* number of elements in sum */
               MPI_INT,		/* the datatype of sum */
               0,			/* the rank of the process that contains the
				   value to broadcast */
               MPI_COMM_WORLD	/* the communicator */
    );

    /* Note that ALL processes execute the same call to MPI_Bcast.
     * However, in this case the effect is that process 0 is sending
     * and processes 1..nproc-1 are receiving. */

    /* print the results: */

    printf ("process %d reports: mysum is %d and sum is %d\n", rank, mysum,
            sum);

    /* In practice, one would use MPI_Allreduce in stead of
     * MPI_Reduce followed by MPI_Bcast. MPI_Allreduce is more
     * efficient and leads to a shorter program: */

    MPI_Allreduce (&mysum, &sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    /* Note that MPI_Allreduce is even more simple to use than
     * MPI_Reduce: because the result is sent to every process,
     * there is no need to specify to which process the answer
     * must go */

    /* Let's print the result again: */

    printf ("process %d reports again: mysum is %d and sum is %d\n",
            rank, mysum, sum);

    MPI_Finalize ();		/* end of MPI. Do not forget this call: if a MPI
				 * program ends without calling MPI_Finalize(),
				 * strange things can happen ... */
    return 0;
}
