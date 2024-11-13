#ifndef HEADER_H
#define HEADER_H

typedef struct {
    char* method;
    char* path;
    char* version;
} Request;

Request* request_read(int fd);

void request_free(Request* req);

void request_print(Request* req);

#endif