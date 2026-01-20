#pragma once
#include <string>

struct CliOps
{
    std::string file;
    std::string title;
    std::string artist;
    std::string album;
    std::string cover;
    int year = 0;
    int track = 0;
    bool show = false;
};

CliOps parseArgs(int argc, char *argv[]);
void printHelpStuff();
