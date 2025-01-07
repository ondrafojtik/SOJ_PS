#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <iostream>
#include <math.h>

void task_one(void)
{
    const int32_t FORK_SIZE = 5;
    // exercise one
    int32_t status_codes[FORK_SIZE];

    for (int32_t i = 0; i < FORK_SIZE; i++)
    {
        int32_t j = fork();
        if (j == 0)
        {
            std::cout << "Vytvoren potomek: " << i;
            // do the thing
            usleep(1000000 * (i+1));
            exit(i);
            // exit code
        }
        int32_t status_;
        while(waitpid(-1, &status_, 0) > 0);
        std::cout << " code: " << status_/256 << std::endl;
        status_codes[i] = status_/256;
    }

    // print out the status array
    for (int32_t i = 0; i < FORK_SIZE; i++)
    {
        std::cout << status_codes[i] << " ";
    }
    std::cout << std::endl;
}

void bubble_sort(void)
{
    const int32_t ARRAY_SIZE = 5;
    int32_t array[ARRAY_SIZE] = {2, 3, 5, 1, 4};
    int32_t swap_count = 0;

    for(;;)
    {
        for (int32_t i = 0; i < ARRAY_SIZE - 1; i++)
        {
            if (array[i] > array[i+1])
            {
                // swap
                int tmp_ = array[i];
                array[i] = array[i+1];
                array[i+1] = tmp_;
                swap_count += 1;
            }
        }

        if(swap_count == 0)
            break;
        swap_count = 0;
    }

    for (int32_t i = 0; i < ARRAY_SIZE; i++)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

void task_two(void)
{
    const int32_t ARRAY_SIZE = 11;
    int32_t array[ARRAY_SIZE] = { 11, 9, 10, 2, 1, 3, 5, 6, 7, 4, 8 };
    bool repeat = 0;

    // shared memory
    int shmid; // memory ID
    int *shmp;  // memory ast
    int shmkey = getuid(); // explicit ID for every _thread_
    shmid = shmget(shmkey, (size_t)ARRAY_SIZE*sizeof(int), 0644|IPC_CREAT);
    shmp  = (int32_t*)shmat(shmid,NULL,0); // link ast with actaull memory block

    // fill the array
    for (int i = 0; i < ARRAY_SIZE; i++)
        shmp[i] = array[i];
    for (int i = 0; i < ARRAY_SIZE; i++)
        std::cout << shmp[i] << " ";
    std::cout << std::endl;

    for(;;)
    {
        repeat = 0;
        // even number of fokrs
        for (int i = 0; i < ARRAY_SIZE / 2; i++)
        {
            int j = fork();
            if (j == 0)
            {
                if (shmp[i*2] > shmp[(i*2)+1])
                {
                    // swap
                    int tmp = shmp[i*2];
                    shmp[i*2] = shmp[(i*2)+1];
                    shmp[(i*2)+1] = tmp;
                    exit(1);
                }
                exit(0);
            }
            int32_t status_;
            while(waitpid(-1, &status_, 0) > 0);
            if (status_ != 0)
                repeat = 1;
        }

        // odd number of forks
        int ODD_NUM = 0;
        if (ARRAY_SIZE % 2 == 0)
            ODD_NUM = (ARRAY_SIZE / 2) - 1;
        else
            ODD_NUM = (ARRAY_SIZE / 2);


        for (int i = 0; i < ODD_NUM; i++)
        {
            int j = fork();
            if (j == 0)
            {
                if (shmp[(i*2)+1] > shmp[(i*2)+2])
                {
                    // swap
                    int tmp = shmp[(i*2)+1];
                    shmp[(i*2)+1] = shmp[(i*2)+2];
                    shmp[(i*2)+2] = tmp;
                    exit(1);
                }
                exit(0);
            }
            int32_t status_;
            while(waitpid(-1, &status_, 0) > 0);
            if (status_ != 0)
                repeat = 1;
        }

        // print
        for (int i = 0; i < ARRAY_SIZE; i++)
            std::cout << shmp[i] << " ";
        std::cout << std::endl;

        // termination check
        if (!repeat)
            break;
    }

    // clean the memory
    shmctl(shmid, IPC_RMID, 0);

}

int main(void)
{
    //bubble_sort();
    //task_one();
    task_two();
}


// g++ main.cpp -o output

// to execute:  ./output
