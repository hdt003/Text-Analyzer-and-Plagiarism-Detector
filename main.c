#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include "head1.h"
#include "head2.h"
// #include <pthread>
// #include<pthread.h>

int main(int argc, char *argv[])
{
    int ret;

    // to store characters detail
    int arr[26] = {0};

    if (argc < 2)
    {
        fprintf(stderr, "USAGE: code_example.out file_or_dir_with_path\n");
        exit(1);
    }
    ret = open_file(argv[1]);
    if (ret != 0)
    {
        close_file();
        exit(ret);
    }

    char_details(arr);
    close_file();
    ret = open_file(argv[1]);
    printf("----------------------------------\n");
    word_details();
    // pthread_t tid;
    // pthread_create(&tid,NULL,word_details,NULL);
    display_word_details();
    close_file();
    // pthread_join(tid,NULL)
    ret = open_file(argv[1]);
    plag_check();
    close_file();
    return 0;
}
