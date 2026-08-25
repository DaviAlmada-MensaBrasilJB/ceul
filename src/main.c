// Davi "Genetyn" Almada (LITERALSTRING) - 2026
// The Ceul Programming Language Official first CLI Interpreter

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 64
#define KB 1024
#define OUT stdout

typedef char * string;

typedef enum {
    STDFUNCTIONCALL,
    VARIABLEDEFINITION,
    VARIABLEDECLARATION,
    LITERALSTRING, //Uff, referências
    COMMENT,
} tokenType;

typedef struct {
    const string value;
    tokenType type;
    void (*function)(int argc, string argv[]);
} token;

// desistemo.
// typedef struct {
//     void (*function)(void);
// } methods;

// typedef struct Class{
//     const string name;
//     struct Class* parent;
//     void* (*constructor)(int argc, string argv[]);
//     const methods* m;
// } Class;

// faze isso n
// typedef struct{
//     token* super;
// }literalstring;

// ---------------[UTILS]---------------
// Cool function for adding \n to the end of texts, mind that it doesn't accept other arguments.
void println(string text){
    printf("%s", text);
    printf("\n");
}

// never remove this
void do_intro(){
    println("\"Hello, im a guy that likes programming in C because C++ is a little too bad and difficult.");
    println("Also, I like Oneshot (Never played the game cuz im broke), Minecraft (yeah, a broke guy bought it), Roblox,");
    println("The Amazing Digital Circus (Literally the first 3 episodes), Murder Drones (only the 7 first episodes) and Animator vs.");
    println("Animation.");
    println("Yeah, I made an entire function for an introduction to myself, it's mostly disabled, but im debbuging.");
    println("UPDATE: I BOUGHT ONESHOT!! (YAY!) 17/08/2026(DD/MM/YYYY)");
    println("Thank you so much for your attention.\"\n-Davi \"Genetyn\" Almada (LITERALSTRING)");
}

// changes the string pushing it backwards
void strmoveb(string str, size_t current, size_t *size){
    for(size_t i = current; i < *size; i++){
        str[i] = str[i + 1]; // pushes every character of the string backwards.
    }
    (*size)--;
}

void dbufferToLbuffer(char dbuffer[][MAX_SIZE], string lbuffer[], int counter){
    for(int i = 0; i < counter; i++){
        lbuffer[i] = dbuffer[i];
    }
}

// strtok but it has a(n) (eletrical) stroke
// still working cuz its hard asf
void stroke(string str, char dbuffer[][MAX_SIZE], int *counter){
    size_t size = strlen(str);
    bool is_string = false;
    bool separated = false; // tells if the string's spaces are already '\0' characters
    // so "Hello   world!" doesn't become "Hello\0\0\0world!\0"
    //                                           ^    ^
    //                                         true  false
    size_t word = 0;
    int debounce = 0; // a sign so the code works.
    int wpos = 0;
    for(size_t c = 0; c < size; c++){
        if(str[c] == ' ' && !is_string){
            if(!separated){
                str[c] = '\0';
            }else{
                // printf(
                //     "ANTES DO MOVE: c=%zu size=%zu debounce=%d word=%zu wpos=%d str=[%s]\n",
                //     c, size, debounce, word, wpos, str
                // );
                strmoveb(str, c, &size);
                // printf(
                //     "DEPOIS DO MOVE: c=%zu size=%zu debounce=%d word=%zu wpos=%d str=[%s]\n",
                //     c, size, debounce, word, wpos, str
                // );
                c--;
                continue;
            }
            separated = !separated;
        }
        if((str[c] == '\t' || str[c] == '\n' || str[c] == '\r') && !is_string){
            if(!separated){
                str[c] = '\0';
            }else{
                // printf(
                //     "ANTES DO MOVE: c=%zu size=%zu debounce=%d word=%zu wpos=%d str=[%s]\n",
                //     c, size, debounce, word, wpos, str
                // );
                strmoveb(str, c, &size);
                // printf(
                //     "DEPOIS DO MOVE: c=%zu size=%zu debounce=%d word=%zu wpos=%d str=[%s]\n",
                //     c, size, debounce, word, wpos, str
                // );
                c--;
                continue;
            }
            separated = !separated;
        }
        if(str[c] == '\0'){
            dbuffer[word][wpos] = '\0';
            debounce = c + 1;
            word++;
            wpos = 0;
            continue;
        }
        if(str[c] == '"'){
            is_string = !is_string;
            // printf(
            //     "ANTES DO MOVE: c=%zu size=%zu debounce=%d word=%zu wpos=%d str=[%s]\n",
            //     c, size, debounce, word, wpos, str
            // );
            strmoveb(str, c, &size);
            // printf(
            //     "DEPOIS DO MOVE: c=%zu size=%zu debounce=%d word=%zu wpos=%d str=[%s]\n",
            //     c, size, debounce, word, wpos, str
            // );
            c--; // lowers "C" so it repeats the loop with the same letter and processes the pushed character.
            // and if "C" is 0 it will just be the maximum possible value(SIZE_MAX; long long type), then it will be c = 0 after the "c++;".
            //size = strlen(str); // changes size so the loop doesn't acess NULL data in the new string.
            continue;
        }
        // printf("c=%zu size=%zu debounce=%d word=%zu wpos=%d char=[%c]\n",
        //     c, size, debounce, word, wpos, str[c]);
        // printf("STR=[%s]\n", str);
        dbuffer[word][wpos++] = str[c];//(c < size && c >= debounce)?
        //     c - debounce
        //     : 0];
        separated = false;
    }
    *counter = word;
}

// ---------------[COMMANDS]---------------
void ceul_write(int argc, string argv[]){
    for(int i = 1; i < argc; i++){
        fprintf(OUT, "%s", argv[i]);

        if(i < (argc - 1)){
            fprintf(OUT, " ");
        }
    }
    fprintf(OUT, "\n");
}

void ceul_close(int argc, string argv[]){
    exit(0);
}

void ceul_clear(int argc, string argv[]){
    // if(strcmp(argv[0], "w")){
    //     system("cls");
    // }else{
    //     system("clear");
    // }

    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// ---------------[main]---------------
int main(int argc, char *argv[]){
    char command[MAX_SIZE];
    char cache[KB]; // Code cache; saves the written code.
    char buffer[KB]; // Saves a limited amount of text data up to one kilobyte.
    char dbuffer[KB][MAX_SIZE]; // same as the buffer, but saves strings in an array. doublebuffer-
    // No, or 65.536(1024 * 64) Bytes will be wasted.
    // TODO: "How to make dbuffer waste dynamically?"
    // No, stroke() needs it, i'm here for it.

    string lbuffer[MAX_SIZE]; // almost the same as buffer, but saves only pointers up to 64 bytes. Lilbuffer

    token std_commands[] = {
        {"write", STDFUNCTIONCALL, ceul_write},
        {"exit", STDFUNCTIONCALL, ceul_close},
        {"clear", STDFUNCTIONCALL,  ceul_clear},
        //{"//", COMMENT, NULL},
    };

    //do_intro(); // enable whenever you want
    println("CEUL v0.0.1\n");

    // main loop
    while (true){
        bool valid_flag = false;
        int counter = 0; // resets the argument counter
        printf("> "); // cursor
        fgets(cache, sizeof(cache), stdin); // reads

        string comment = strstr(cache, "//");
        if(comment != NULL){
            *comment = '\0';
        }
        strcpy(buffer, cache); // so the cache is the base and its not overwritten

        // string token_ptr = strtok(buffer, " \t\r\n");
        // while(token_ptr != NULL) {
        //     //strcpy(dbuffer[j], token);
        //     lbuffer[counter++] = token_ptr; // writes to lbuffer
        //     token_ptr = strtok(NULL, " \t\r\n"); // updates the token
        // }
        stroke(buffer, dbuffer, &counter);
        dbufferToLbuffer(dbuffer, lbuffer, counter);

        // chatgpt debug thing
        // for(int i = 0; i < counter; i++){
        //     printf("TOKEN %d: [%s]\n", i, lbuffer[i]);
        // }

        if(counter <= 0){ continue; }
        for(int i = 0; i < (sizeof(std_commands) / sizeof(std_commands[0])); i++){ // runs through the std_commands.
            if(strcmp(lbuffer[0], std_commands[i].value) == 0){ // checks if it is a valid command
                //printf("%s", &std_commands[i].value); // debugging rn
                valid_flag = true;
                std_commands[i].function(counter, lbuffer); // executes da function
            }
        }
        if(counter > 0 && !valid_flag){
            printf("[ERR]: Command \"%s\" not reconized\n", lbuffer[0]);
        }
    }
    return 0;
}