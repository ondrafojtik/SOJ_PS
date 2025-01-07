#include <iostream>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include "md5.h"
#include <chrono>
#include <fstream>
#include <sstream>

//#define DEBUG
//#define PRINT_RESULT

#define FIRST_CHARACTER 65
#define LAST_CHARACTER 127

// begin - 65  - A
// end -   127 -null..

int solve(char* word_, int32_t word_length, int* start_array)
{
    // init
    char* word = new char[word_length];
    int32_t* array = new int32_t[word_length];
    for (int i = 0; i < word_length; i++)
        array[i] = 65;

    for (int i = 0; i < word_length; i++)
        array[i] = start_array[i];

    // solve
    for (;;)
    {
        // increment system
        for (int i = word_length - 1; i >= 0; i--)
        {
            if (array[i] < 127)
            {
                array[i] += 1;
                break;
            }
            else
            {
                array[i] = 65;
            }
        }

        // check for correctness
        for (int i = 0; i < word_length; i++)
            word[i] = array[i];
#if 0
        for (int i = 0; i < word_length; i++)
            std::cout << word[i];
        std::cout << std::endl;
#endif
        if (md5(word) == word_)
        {
#ifdef PRINT_RESULT
            std::cout << word << std::endl;
#endif
            delete[] word;
            delete[] array;
            return 0;
        }

    }
}

int solve_for_forks(int argc, char **argv, int n)
{
    int word_len = std::atoi(argv[2]);
    //int fork_count = std::atoi(argv[3]);
    int fork_count = n;
    int* pid_array = new int[fork_count];


    int combinations = 1;
    for (int i = 0; i < word_len; i++)
        combinations = combinations * (LAST_CHARACTER - FIRST_CHARACTER);
#ifdef DEBUG
    std::cout << "number of combinations: " << combinations << std::endl;
#endif
    // divide it by the number of threads
    float one_fork = combinations / fork_count;
#ifdef DEBUG
    std::cout << "words for one fork: " << one_fork << std::endl;
#endif

    // procces described below
    int number_of_chars = LAST_CHARACTER - FIRST_CHARACTER;
    int* len_array = new int[word_len];
    for (int i = 0; i < word_len; i++)
    {
        int cost = pow(number_of_chars, (word_len - 1) - i);
        int fork_dist = one_fork / cost;
        one_fork = one_fork - (fork_dist*cost);
        len_array[i] = fork_dist;
    }

    // printing to make sure its correct
#ifdef DEBUG
    for (int i = 0; i < word_len; i++)
    {
        std::cout << len_array[i] << std::endl;
    }
#endif
    int* array = new int[word_len];
    for (int i = 0; i < word_len; i++)
        array[i] = FIRST_CHARACTER;

    //one_fork = pow(number_of_chars + 1, word_len) / fork_count;
    one_fork = combinations / fork_count;

    for (int k = 0; k < fork_count; k++)
    {
#ifdef DEBUG
        std::cout << "TADY: \n";
        for (int i = 0; i < word_len; i++)
            std::cout << array[i] << " ";
        std::cout << std::endl;
#endif
        // calc with the calculated array
        pid_array[k] = fork();
        if (pid_array[k] == 0)
        {
            int return_val = solve(argv[1], std::atoi(argv[2]), array);
            exit(0);
        }


        // increment
        for (int j = 0; j < one_fork; j++)
        {

            for (int i = word_len - 1; i >= 0; i--)
            {
                if (array[i] < LAST_CHARACTER - 1)
                {
                    array[i] += 1;
                    break;
                }
                else
                {
                    array[i] = FIRST_CHARACTER;
                }
            }

        }

    }

    // kill children
    int status_;
    while (wait(&status_) > 0)
    for (int _i = 0; _i < fork_count; _i++)
    {
#ifdef DEBUG
        std::cout << "Killing PID: " << pid_array[_i] << std::endl;
#endif
        kill(pid_array[_i], SIGTERM);
    }

    delete[] pid_array;
    delete[] len_array;
    delete[] array;
    return 0;

}


int main(int argc, char **argv)
{

    int fork_count = std::atoi(argv[3]);

    auto _start = std::chrono::steady_clock::now();
    solve_for_forks(argc, argv, fork_count);
    auto _end = std::chrono::steady_clock::now();

    std::chrono::duration<double> _duration = _end - _start;
    std::cout << _duration.count() << std::endl;

    std::cout << _duration.count() << ";\n";

    return 0;



    std::stringstream ss;
    for (int i = 8; i < 100; i++)
    {
        std::cout << "i: " << i << std::endl;
        auto start = std::chrono::steady_clock::now();
        solve_for_forks(argc, argv, i);
        auto end = std::chrono::steady_clock::now();

        std::chrono::duration<double> duration = end - start;
        std::cout << duration.count() << std::endl;

        ss << i << "; " << duration.count() << ";\n";
    }
    std::ofstream file_handle;
    file_handle.open("times.csv");
    file_handle << ss.str();
    file_handle.close();

    return 0;

}

/*
FOR BENCHMARK
time ./testbinary dc0a993e43feeb583954acac26da52dd 3 2
file: chart_zim

*/

/*
md5sum

457cec4d12a2efe9c8eb46b0baf67a29 - Ahoj
79c2b46ce2594ecbcb5b73e928345492 - ahoj
1d5ffd3c4e0dde41443505d77bf49d45 - Aha
124534a0ae447b0872b3092731a37d8e - aha
f6df56c3bcacc68ca13b51a0b2cd140d - zima

eb470d6c13e2c4f889c32b8c402ee0b5 - Nero
d6a006eb17335d0521d971ff3ea5414e - Ner
4dec99baa99738721da9c9b0c1a92498 - Ne
8d9c307cb7f3c4a32822a51922d1ceaa - N


*/

/*
FOR COMPILATION

g++ main.cpp md5.cpp -o testbinary

testbinary is result
                                                             word_size, fork_count
to execute: time ./testbinary 1d5ffd3c4e0dde41443505d77bf49d45 3 2
*/

/*
MD5 FUNCTION
http://www.zedwood.com/article/cpp-md5-function
*/






/*
DOESNT WORK!!!!!!!!!!!!!!!!!!!!§§

time ./testbinary 79c2b46ce2594ecbcb5b73e928345492 4 2



// start solving for given bounds..
    int* pid_array = new int[fork_count];
    int* array = new int[word_len];
    for (int i = 0; i < word_len; i++)
        array[i] = FIRST_CHARACTER;

    for (int i = 0; i < fork_count; i++)
    {
        for (int k = 0; k < word_len; k++)
            array[k] = array[k] + (i * len_array[k]);
        // have to adjust array here (could be outside the bounds)
        for (;;)
        {
            bool change = 0;
            for (int _i = word_len - 1; _i >= 0; _i--)
            {
                if (array[_i] < 127)
                {

                }
                else
                {
                    array[_i] = 33;
                    array[_i+1] += 1;
                    change = 1;
                }
            }

            if (!change)
                break;
        }


        int j = fork();
        if (j == 0)
        {
            // child
            std::cout << "child created" << std::endl;
            for(int i = 0; i < word_len; i++)
                std::cout << array[i] << " ";
            std::cout << std::endl;
            //solve(argv[1], std::atoi(argv[2]), array);
            exit(0);
        }
        int32_t status_;
        while(waitpid(-1, &status_, 0) > 0);
        if (status_ == 0) std::cout << "found it" << std::endl;

    }

    // if smth gets here it means some child must have found it
    //for (int i = 0; i < fork_count; i++)
    //  kill(pid_array[i], SIGTERM);


*/
