#include "pi.h"

double pi_calc(long int n, int rank, int size) {
    // Write your code below
    ////////////////////////////////////////

    int rem = n % size;
    srand(time(NULL) + rank);

    int d = 0;
    int temp = size - 1;
    while (temp > 0) {
        d++;
        temp >>= 1;
    }
    
    // do local computation
    long int local_n = (n / size) + (rank < rem ? 1 : 0);
    long int local_sum = 0;
    for (int i = 0; i < local_n; ++i) {
        double rand_x = (double) (rand()) / RAND_MAX;
        double rand_y = (double) (rand()) / RAND_MAX;
        if (((rand_x * rand_x) + (rand_y * rand_y)) < 1) {
            ++local_sum;
        }
    }

    // coordinate send/recv
    for (int j = 0; j < d; ++j) {
        int permutation = (1 << j);
        if ((rank & permutation) != 0) {
            MPI_Send(&local_sum, 1, MPI_LONG, rank ^ permutation, 0, MPI_COMM_WORLD);
            break;
        } else {
            long int recv_sum;
            MPI_Recv(&recv_sum, 1, MPI_LONG, rank ^ permutation, 0, MPI_COMM_WORLD, NULL);
            local_sum += recv_sum;
        }
    }

    // return final result
    if (rank == 0) {
        return 4.0 * local_sum / n;
    }
    return 0.0;
}