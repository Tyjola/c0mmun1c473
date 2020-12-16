#ifndef DEF_STREAMS
#define DEF_STREAMS

#include <string>

std::string fopen(std::string filename);
int fcreate(std::string filename, std::string content);

#endif