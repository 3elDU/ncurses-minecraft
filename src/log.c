#include "log.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct LogObject* createLog(unsigned bufferSize, const char* filename) {
    struct LogObject *obj = (struct LogObject*)malloc(sizeof(struct LogObject));

    obj->bufferSize = bufferSize;
    obj->buffer = (char*)malloc(bufferSize);
    obj->filename = malloc(strlen(filename));
    memcpy(obj->filename, filename, strlen(filename));

    return obj;
}

void logPrintln(struct LogObject* log, char* string) {
    if (strlen(log->buffer) + strlen(string) >= log->bufferSize) {
        // if buffer is full, first we write it out to the file ( so it empties ),
        // and then we add out message to empty buffer

        FILE *f = fopen(log->filename, "a");

        if (f) {
            fwrite(log->buffer, strlen(log->buffer), 1, f);
            memset(log->buffer, ' ', log->bufferSize);
            log->buffer[log->bufferSize-1] = '\0';
            fclose(f);
        }
    }

    strncat(log->buffer, string, log->bufferSize);
}

void logWrite(struct LogObject* log) {

}