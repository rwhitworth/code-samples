#pragma once

#if defined (__cplusplus)
extern "C" {
#endif


int chomp(char *input, char remove_char);
void chop(char *input);
char chr(const unsigned char input);
int hex(const char *input);
int index(const char *input, const char *substr);
int index_pos(const char* input, const char *substr, int pos);
char *lc(const char *input);
int ord(const char input);
char *q(const char *input);
char *qq(const char *input);
char *reverse(const char *input);
int rindex(const char *input, const char *substr);
char *substr(const char *input, const int offset, const int length);
char *substr_replace(const char *input, const int offset, const int length, const char *replstr);
char *uc(const char *input);
//split








#if defined (__cplusplus)
}
#endif