#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#define b 256

int search(char ss[], char text[], int q) // ss->sub string
{
    int M = strlen(ss);
    int N = strlen(text);
    int i, j;
    int p, t, h;
    p = 0; // hash value for pattern
    t = 0; // hash value for text
    h = 1;

    // The value of h would be "pow(b, M-1)%q"  , q is prime number
    for (i = 0; i < M - 1; i++)
        h = (h * b) % q;

    for (i = 0; i < M; i++)
    {
        p = (b * p + ss[i]) % q;
        t = (b * t + text[i]) % q;
    }

    for (i = 0; i <= N - M; i++)
    {
        if (p == t)
        {

            for (j = 0; j < M; j++)
            {
                if (text[i + j] != ss[j])
                    break;
            }

            if (j == M)
            {
                return 1;
            }
        }
        // assign new value to t
        if (i < N - M)
        {
            t = (b * (t - text[i] * h) + text[i + M]) % q;

            if (t < 0)
                t = (t + q);
        }
    }

    return 0;
}

// CREATE STRING
char *creat_string(int i, int j)
{

    // SIZE IS ASSIGNED RANDOMLY
    char *buffer = (char *)malloc(500 * sizeof(char));
    struct node *temp = head;
    while (temp->index_no != i)
    {
        temp = temp->next;
    }
    while (temp->index_no != j)
    {

        if (temp->index_no == i)
        {
             strcat(buffer,temp->word);
            // buffer = temp->word;
        }
        else
        {
            strcat(buffer, " ");
            strcat(buffer, temp->word);
        }
        temp = temp->next;
    }
    // if(temp->index_no == i){
    //         strcat(buffer,temp->word);
    //         // buffer=temp->word;
    //     }
    //     else{
    //         strcat(buffer," ");
    //         strcat(buffer,temp->word) ;
    //     }
    strcat(buffer, " ");
    strcat(buffer, temp->word);
    return buffer;
}

void display_word_details()
{
    struct node *t = head;
    while (t != NULL)
    {
        printf("%s  %d\n", t->word, t->index_no);
        t = t->next;
        //  number_of_words++;
    }
    printf("Total number of words: %d\n", number_of_words);
}
// close file
void close_file()
{
    if (srcfd != NULL)
    {
        fclose(srcfd);
    }
}

// char_details
void char_details(int arr[])
{
    char ch;

    ch = fgetc(srcfd);

    while (ch != EOF)
    {
        total_char++;
        int x = ch;
        // convert into lowercase
        if (x >= 65 && x <= 90)
        {
            x = x + 32;
        }
        // calculating the number of each characters
        arr[x - 97]++;

        ch = fgetc(srcfd);
    }

    // printing the details of characters
    for (int i = 0; i < 26; i++)
    {
        printf("%c   %d   %f\n", i + 97, arr[i], (float)((float)arr[i] * 100 / (float)total_char));
    }
    printf("total numbers of characters: %d\n", total_char);
}


// for insertig the words
void insert(char s[])
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->next = NULL;
    strcpy(temp->word, s);
    temp->index_no = idx;
    idx++;
    // printf("%s    %s",s,temp->word);
    number_of_words++;
    if (head == NULL)
    {
        head = temp;
        tail = temp;
    }
    else
    {
        tail->next = temp;
        tail = temp;
    }
}

//for getting word details
void word_details()
{
    // printf("tid:%u\n",pthread_self())
    char ch;
    ch = fgetc(srcfd);
    // convert to small
    if (ch >= 65 && ch <= 90)
    {
        ch = ch + 32;
    }
    char s[50]; // storing words as a string which overwrite
    int n = 0;

    while (ch != EOF)
    {
        if (ch == ' ' || ch == '.' || ch == '?' || ch == '!')
        {
            //insert(s);
             struct node *temp = (struct node *)malloc(sizeof(struct node));
             temp->next = NULL;
             strcpy(temp->word, s);
             temp->index_no = idx;
    idx++;
    // printf("%s    %s",s,temp->word);
    number_of_words++;
    if (head == NULL)
    {
        head = temp;
        tail = temp;
    }
    else
    {
        tail->next = temp;
        tail = temp;
    }


            n = 0;
            memset(s, 0, sizeof(s));
            ch = fgetc(srcfd);

            if (ch >= 65 && ch <= 90)
            {
                ch = ch + 32;
            }
        }
        s[n] = ch;
        n++;
        ch = fgetc(srcfd);
        if (ch >= 65 && ch <= 90)
        {
            ch = ch + 32;
        }
    }
    insert(s);
}

// plag check
void plag_check()
{
    // taking input of another text file
    // convert into small alfabets
    FILE *ptr;

    // OPEING SECOND FILE FOR GETTING TOTAL CHAR IN STRING
    ptr = fopen("text_file_2.txt", "r");
    char ch2;
    int n2 = 0;
    ch2 = fgetc(ptr);
    while (ch2 != EOF)
    {
        n2++;
        ch2 = fgetc(ptr);
    }
    s2 = (char *)malloc(n2 * sizeof(char));
    fclose(ptr);

    // OPENING 2ND FILE TO COPY ITS VALUE IN S2
    ptr = fopen("text_file_2.txt", "r");
    ch2 = fgetc(ptr);
    int i = 0;
    while (ch2 != EOF)
    {
        // CONVERTING THE FILE INTO LOWER CASE
        if (ch2 >= 65 && ch2 <= 90)
        {
            ch2 = ch2 + 32;
        }

        s2[i] = ch2;
        i++;
        ch2 = fgetc(ptr);
    }
    fclose(ptr);

    // s1 = (char *)malloc(total_char * sizeof(char));
    // int j = 0;

    // char c = fgetc(srcfd);
    // while (c != EOF)
    // {
    //     s1[j] = c;
    //     j++;
    //     c = fgetc(srcfd);
    // }

    printf("%s\n", s2);
    // STRING 2ND IS S2
    //------------------------------------------------------------------------------//

    // char *r = creat_string(0,2);
    // printf("%s\n",r);
    int total_strings = 0;
    int total_mach = 0;

    printf("words number:%d\n", number_of_words);

    for (int i = 0; i < number_of_words; i++)
    {
        int count_me = 0;
        int max = -1;
        total_strings++;
        // char *str1 = (char*)malloc(500*sizeof(char));
        for (int j = i; j < number_of_words; j++)
        {
            count_me++;
            if (count_me >= 2 && count_me < 20)
            {
               char *str1 = (char *)malloc(500 * sizeof(char));
                str1 = creat_string(i, j);
                // printf("%d to %d = %s\n", i, j, str1);
                int check = search(str1, s2, 101);
                if (check == 1)
                {
                    if (max < j - i)
                    {
                        max = j - i;
                    }
                }
            }
        }
        if (max >= 0)
        {
            total_mach++;
        }
    }

    float ans = (float)total_mach / (float)total_strings * 100;

    printf("%f\n", ans);
}