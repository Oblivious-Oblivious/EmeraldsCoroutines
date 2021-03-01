#include <stdio.h>
#include <string.h>
#include <ctype.h>



#define coroutine static int __state = 0; switch(__state) { case 0:
#define yield(__x) do { __state = __LINE__; return __x; case __LINE__:; } while(0)
#define cend }



static const unsigned char *input = "2A2D3+5C2B1-4A";
static const unsigned char *input2 = "AADD+++CCCCCBB-AAAA";

static enum {
    WORD,
    PUNCT
} token;

static void emit(char in) {
    printf("%c", in);
}

static void add_to_token(char c) {
    printf("Adding %c to tokens\n", c);
}

static void got_token(int token) {
    if(token == WORD) puts("got WORD");
    if(token == PUNCT) puts("got PUNCT");
}

int parser(void) {
    int i;
    for(i = 0; i < strlen(input2); i++) {
        char c = input2[i];
        if(c == EOF) break;
        else if(isalpha(c)) {
            do {
                add_to_token(c);
                c = input2[++i];
            } while(isalpha(c));
            got_token(WORD);
        }
        add_to_token(c);
        got_token(PUNCT);
    }
}

int decompressor(void) {
    int i;
    for(i = 0; i < strlen(input); i += 2) {
        char c = input[i];
        if(c == EOF) break;
        else {
            int len = c - '0';
            c = input[i + 1];
            while(len--)
                emit(c);
        }
    }
    /*emit(EOF);*/
}

int main(void) {
    printf("input  = %s\noutput = ", input);
    decompressor();
    puts("");

    parser();

    return 0;
}
