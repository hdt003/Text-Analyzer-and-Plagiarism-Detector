#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>

int number_of_words = 0;
int total_char = 0;
char *s2;
char *s1;
int idx = 0;

struct node
{
    char word[50];
    struct node *next;
    int index_no;
} *head = NULL, *tail = NULL;

// open file
FILE *srcfd;
int open_file(char *srcfile)
{
    srcfd = fopen(srcfile, "r");

    if ((srcfd = fopen(srcfile, "r")) == NULL)
    {
        if (errno == ENOENT)
        {
            fprintf(stderr, "%s path or file does not exist", srcfile);
            return (2);
        }
        else
        {
            fprintf(stderr, "%s cannot be opened in read mode", srcfile);
            return (3);
        }
    }

    return 0;
}