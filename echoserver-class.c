#include "echoserver-class.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int message_count_faked = 0;

Request *request_read(int fd) {
    if (message_count_faked > 3) {
        return NULL;
    }
    printf("faking a request");
    return (Request *)malloc(1);
}

void request_free(Request *req) {
    free(req);
}

void request_print(Request *req) {
    printf("got a request\n");
}





// request* req = request_red(sock_fd);
// we can now type these in the command line:
// dr code:

// if (argc == 2 && strcmp(argv[1], "-") == 0) {
//         Request* req = request_read(stdin);
//         if (req != NULL) {
//             request_print(req);
//             request_free(req);
//         }
//         printf("done with stdin\n");
//         return 0;
//     }