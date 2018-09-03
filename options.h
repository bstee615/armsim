#ifndef OPTIONS_H
#define OPTIONS_H

typedef unsigned numbytes;

class Options
{
    const char* _filename;
    numbytes _memory;
    bool _test;
public:
    Options(const char* filename, numbytes memory, bool test): _filename(filename), _memory(memory), _test(test) {}

    const char* getFilename() { return _filename; }
    numbytes getMemory() { return _memory; }
    bool isTest() { return _test; }
};

#endif // OPTIONS_H
