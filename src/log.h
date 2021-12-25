#ifndef LOG_H
#define LOG_H

struct LogObject {
    unsigned bufferSize;
    char* buffer;

    char* filename;
};

struct LogObject* createLog(unsigned bufferSize, const char* filename);
void logPrintln(struct LogObject* log, char* string);
void logWrite(struct LogObject* log);

#endif