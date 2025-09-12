#ifndef ALMOG_STRING_MANIPULATION_H_
#define ALMOG_STRING_MANIPULATION_H_

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>

#define MAXDIR 100
#define MAX_LEN_LINE (int)1e3
#define dprintSTRING(expr) printf(#expr " = %s\n", expr)
#define dprintCHAR(expr) printf(#expr " = %c\n", expr)
#define dprintINT(expr) printf(#expr " = %d\n", expr)
#define dprintSIZE_T(expr) printf(#expr " = %zu\n", expr)


int asm_get_line(FILE *fp, char *dst);
int asm_length(char *str);
int asm_get_next_word_from_line(char *dst, char *src, char seperator);
void asm_copy_arry_by_indesies(char *target, int start, int end, char *src);
int asm_get_word_and_cut(char *dst, char *src, char seperator);
int asm_str_in_str(char *src, char *word2search);
int asm_strncmp(const char *s1, const char *s2, const int N);

#endif /*ALMOG_STRING_MANIPULATION_H_*/

#ifdef ALMOG_STRING_MANIPULATION_IMPLEMENTATION
#undef ALMOG_STRING_MANIPULATION_IMPLEMENTATION

int asm_get_line(FILE *fp, char *dst)
{
    int i = 0;
    char c;

    while ((c = fgetc(fp)) != '\n' && c != EOF) {
        dst[i] = c;
        i++;
        if (i >= MAX_LEN_LINE) {
            fprintf(stderr, "ERROR: line too long\n");
            exit(1);
        }
    }
    dst[i] = '\0';
    if (c == EOF && i == 0) {
        return -1;
    }
    return i;
}

int asm_length(char *str)
{
    char c;
    int i = 0;

    while ((c = str[i]) != '\0') {
        i++;
    }
    return i++;
}

int asm_get_next_word_from_line(char *dst, char *src, char seperator)
{
    int i = 0, j = 0;
    char c;

    while (isspace((c = src[i]))) {
        i++;
    }

    while ((c = src[i]) != seperator &&
                      c != '\n'&&
                      c != '\0') {
                        dst[j] = src[i];
                        i++;
                        j++;
    }

    if ((c == seperator || 
         c == '\n'||
         c == '\0') && i == 0) {
            dst[j++] = c;
            i++;
    }

    dst[j] = '\0';

    if (j == 0) {
        return -1;
    }
    return i;

}

void asm_copy_arry_by_indesies(char *target, int start, int end, char *src)
{
    int j = 0;
    for (int i = start; i < end; i++) {
        target[j] = src[i];
        j++;
    }
    target[j] = '\0';
}

int asm_get_word_and_cut(char *dst, char *src, char seperator)
{
    int last_pos;

    if (src[0] == '\0') {
        return 0;
    }
    last_pos = asm_get_next_word_from_line(dst, src, seperator);
    if (last_pos == -1) {
        return 0;
    }
    asm_copy_arry_by_indesies(src, last_pos, asm_length(src), src);
    return 1;
}

int asm_str_in_str(char *src, char *word2search)
{
    int i = 0, num_of_accur = 0;
    while (src[i] != '\0') {
        if (asm_strncmp(src+i, word2search, asm_length(word2search))) {
            num_of_accur++;
        }
        i++;
    }
    return num_of_accur;
}

/* return 1 if equal, 0 if different */
int asm_strncmp(const char *s1, const char *s2, const int N)
{
    int i = 0;
    while (i < N) {
        if (s1[i] == '\0' && s2[i] == '\0') {
            break;
        }
        if (s1[i] != s2[i] || (s1[i] == '\0') || (s2[i] == '\0')) {
            return 0;
        }
        i++;
    }
    return 1;
}


#endif /*ALMOG_STRING_MANIPULATION_IMPLEMENTATION*/

