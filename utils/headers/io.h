#pragma once
#include "../../screen/headers/highlight.h"

void print2header(const char *msg, unsigned char pos); // print string to header; pos = 1left 3right else center
char *input_header(const char *q); // return allocated 128 byte string, answer to question q, posted in header
#define clearline (wmove(text_win, y, 0), wclrtoeol(text_win))
#define mvprint_line(y, x, buffer, from, to) (wmove(text_win, y, x), print_line(buffer, from, to))
unsigned print_line(const gap_buf &buffer, unsigned from, unsigned to); // print substring of buffer, to = 0 -> fill line
void print_text(unsigned line); // print text string from line
vector<unsigned> search(const gap_buf &buf, const char *str, unsigned len); // search for str in buf, return vector with occurence position
void save(); // save buffer to filename
void read_fgets(FILE *fi); // read file with fgets
void read_fread(FILE *fi); // read file with fread (faster)
