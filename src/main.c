// Davi "Genetyn" Almada (LITERALSTRING) - 2026
// The Ceul Programming Language Official first CLI Interpreter

// Only reusable code is still commented
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <time.h>
#endif

#define MAX_SIZE 64
#define KB 1024
//#define OUT stdout

typedef char * string;

typedef enum {
    STDFUNCTIONCALL,
    VARIABLEDEFINITION,
    VARIABLEDECLARATION,
    LITERALSTRING, //Uff, referências
    COMMENT,
    KEYWORD,
} tokenType;

typedef struct token{
    const string value;
    const size_t args;
    tokenType type;
    void (*function)(size_t argc, string argv[], size_t place, struct token *commands, size_t command_count);
} token;

// token tokonstructor(){
    
// }

typedef enum{
    NOSTRINGLITERAL,
    INVALIDCOMMAND,
    
} errorType;

// later.
// typedef struct {
//     void (*function)(void);
// } methods;

// typedef struct Class{
//     const string name;
//     struct Class* parent;
//     void* (*constructor)(int argc, string argv[]);
//     const methods* m;
// } Class;

// ---------------[UTILS]---------------
// Cool function for adding \n to the end of texts, mind that it doesn't accept other arguments.
void println(string text){
    printf("%s", text);
    printf("\n");
}

// void send_error(er)

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

void scan_commands(size_t counter, token std_commands[], size_t command_count, string lbuffer[], size_t start, size_t end){
    size_t err_index = 0;
    size_t index = 0;
    for(size_t i = start; i < end; i++){ // runs through the tokens.
        bool valid = false;
        for(size_t j = 0; j < command_count /*(sizeof(lbuffer) / sizeof(lbuffer[0]))*/; j++){
            if(strcmp(lbuffer[i], std_commands[j].value) == 0){ // checks if it is a valid command
                valid = true;
                std_commands[j].function(counter, lbuffer, i, std_commands, command_count); // executes da function
                index = j;
                break;
            }else{
                err_index = i;
            }
        }
        if(valid){
            i += std_commands[index].args;
        }else{
            printf("\a[ERR][INDEX=%zu]: Command \"%s\" not recognized\n", i, lbuffer[err_index]);// still working for the send_error() function
        }
    }
}

// changes the string pushing it backwards
void strmoveb(string str, size_t current, size_t *size){
    for(size_t i = current; i < *size; i++){
        str[i] = str[i + 1]; // pushes every character of the string backwards.
    }
    (*size)--;
}

void dbufferToLbuffer(char dbuffer[][MAX_SIZE], string lbuffer[], size_t counter){
    for(size_t i = 0; i < counter; i++){
        lbuffer[i] = dbuffer[i];
    }
}

// strtok but it has a(n) (eletrical) stroke
// still working cuz its hard asf
void stroke(string str, char dbuffer[][MAX_SIZE], size_t *counter){
    size_t size = strlen(str);
    bool is_string = false;
    bool separated = false; // tells if the string's spaces are already '\0' characters
    // so "Hello   world!" doesn't become "Hello\0\0\0world!\0"
    //                                           ^    ^
    //                                         true  false
    size_t word = 0;
    //int debounce = 0; // a sign so the code works.
    size_t wpos = 0;
    for(size_t c = 0; c < size; c++){
        if(str[c] == ' ' && !is_string){
            if(!separated){
                str[c] = '\0';
            }else{
                strmoveb(str, c, &size);
                c--;
                continue;
            }
            separated = !separated;
        }
        if((str[c] == '\t' || str[c] == '\n' || str[c] == '\r') && !is_string){
            if(!separated){
                str[c] = '\0';
            }else{
                strmoveb(str, c, &size);
                c--;
                continue;
            }
            separated = !separated;
        }
        if(str[c] == '\0'){
            if (word >= KB) {
                printf("[ERR]: Too many tokens in one line\n");
                return;
            }
            dbuffer[word][wpos] = '\0';
            // debounce = c + 1;
            word++;
            wpos = 0;
            continue;
        }
        if(str[c] == '"' || str[c] == '\''){
            is_string = !is_string;
            strmoveb(str, c, &size);
            c--; // lowers "C" so it repeats the loop with the same letter and processes the pushed character.
            // and if "C" is 0 it will just be the maximum possible value(SIZE_MAX; long long type), then it will be c = 0 after the "c++;".
            //size = strlen(str); // changes size so the loop doesn't acess NULL data in the new string.
            continue;
        }
        if(str[c] == '\\' && c + 1 < size && is_string){
            // switch (expression)
            // {
            // case constant expression:
            //     /* code */
            //     break;
            
            // default:
            //     break;
            // }
            bool valid_escape = true;
            switch(str[c + 1]){
                case 'n': str[c] = '\n'; break;
                case 't': str[c] = '\t'; break;
                case 'r': str[c] = '\r'; break;
                case 'v': str[c] = '\v'; break;
                case '\\': str[c] = '\\'; break;
                case '\'': str[c] = '\''; break;
                case '"': str[c] = '\"'; break;
                case 'b': str[c] = '\b'; break;
                case 'a': str[c] = '\a'; break;
                
                default:
                    valid_escape = false;
            }
            if(!valid_escape){
                printf("[ERR]: Escape not valid: \"\\%c\"", str[c + 1]);
                continue;
            }
            strmoveb(str, c + 1, &size);
        }
        if (wpos >= MAX_SIZE - 1) {
            printf("[ERR]: Token exceeds maximum length of %d characters\n", MAX_SIZE - 1);
            return;
        }
        dbuffer[word][wpos++] = str[c];//(c < size && c >= debounce)?
        //     c - debounce
        //     : 0];
        separated = false;
    }
    if(is_string){
        printf("[WARN]: String literal was not closed\n");
    }

    if(wpos > 0){
        dbuffer[word][wpos] = '\0';
        word++;
    }

    *counter = word;
}

void sleep_ms(unsigned int ms){
    #ifdef _WIN32
        Sleep(ms);
    #else
        struct timespec timer = {
            ms / 1000,
            (ms % 1000) * 1000000
        };
        nanosleep(&timer, NULL);
    #endif
}

// ---------------[COMMANDS]---------------
void ceul_write(size_t, string argv[], size_t place, token[], size_t){
    printf("%s", argv[place + 1]);
    // printf("LEN = %zu\n", strlen(argv[place + 1]));

    // for(size_t i = 0; argv[place + 1][i] != '\0'; i++){
    //     printf("[%zu] = %d\n", i, (unsigned char)argv[place + 1][i]);
    // }
    // for(int i = place + commands[0].args; i < argc; i++){

    //     // if(i < (argc - 1)){
    //     //     fprintf(OUT, " ");
    //     // }
    // }
    //fprintf(OUT, "\n");
}

void ceul_close(size_t, string[], size_t, token[], size_t){
    exit(0);
}

void ceul_clear(size_t, string[], size_t, token[], size_t){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void ceul_loop(size_t argc, string argv[], size_t place, token commands[], size_t command_count){
    long start = strtol(argv[place + 1], NULL, 10);
    long end = strtol(argv[place + 2], NULL, 10);
    long step = strtol(argv[place + 3], NULL, 10);
    size_t iterations = 0;

    if(step == 0){
        printf("[ERR]: Step cannot be 0\n");
        return;
    }

    for (size_t i = start; i < end; i += step){
        if(iterations >= 50){
            printf("[WARN]: Loop blocked by maximum 50 iterations\n");
            break;
        }
        scan_commands(argc, commands, command_count, argv, place + 4, argc);
        iterations++;
    }
}

void ceul_sleep(size_t, string argv[], size_t place, token[], size_t){
    sleep_ms((unsigned int)atoi(argv[place + 1]));
}

// ---------------[main]---------------
int main(int, char*[]){
    //char command[MAX_SIZE];
    char cache[KB]; // Code cache; saves the written code.
    char buffer[KB]; // Saves a limited amount of text data up to one kilobyte.
    char dbuffer[KB][MAX_SIZE]; // same as the buffer, but saves strings in an array. doublebuffer-
    // TODO: "How to make dbuffer waste dynamically?"

    string lbuffer[KB]; // almost the same as buffer, but saves only pointers up to 64 bytes. Lilbuffer

    token std_commands[] = {
        {"write", 1, STDFUNCTIONCALL, ceul_write},
        {"exit", 0, STDFUNCTIONCALL, ceul_close},
        {"clear", 0, STDFUNCTIONCALL,  ceul_clear},
        {"loop", 3, KEYWORD, ceul_loop},
        {"sleep", 1, STDFUNCTIONCALL, ceul_sleep}
        //{"//", COMMENT, NULL},
    };
    size_t command_count = sizeof(std_commands) / sizeof(std_commands[0]);

    // Secret loading bar command:
    /* write "[-----]\r" sleep 3000 write "[#----]\r" sleep 3000 write "[##---]\r" sleep 3000 write "[###--]\r"
    sleep 3000 write "[####-]\r" sleep 3000 write "[#####]\n" write "Complete!"*/

    //do_intro(); // enable whenever you want
    println("CEUL v0.0.3-alpha.2\nDocumentation in README.md at:\nhttps://github.com/DaviAlmada-MensaBrasilJB/ceul \n");

    // main loop
    while (true){
        //bool valid_flag = false;
        size_t counter = 0; // resets the argument counter
        printf("\n> "); // cursor
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

        if(counter <= 0){ continue; }
        // for(int i = 0; i < (sizeof(std_commands) / sizeof(std_commands[0])); i++){ // runs through the std_commands.
        //     for(int j = 0; j < (sizeof(lbuffer) / sizeof(lbuffer[0])); j++){
        //         if(strcmp(lbuffer[j], std_commands[i].value) == 0){ // checks if it is a valid command
        //             valid_flag = true;
        //             std_commands[i].function(counter, lbuffer, i, std_commands); // executes da function
        //         }
        //         if(!valid_flag){
        //             printf("[ERR]: Command \"%s\" not reconized\n", lbuffer[j]);
        //         }
        //     }
        // }
        scan_commands(counter, std_commands, command_count, lbuffer, 0, counter);
    }
    return 0;
}