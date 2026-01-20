#include "cli.h"
#include <iostream>

void printHelpStuff()
{
    std::cout << "metaswag\n\n"
                 "usage:\n"
                 "  metaswag --file song.m4a (or mp3 whatever) [options]\n\n"
                 "options:\n"
                 "  --title   \"title\"\n"
                 "  --artist  \"artist\"\n"
                 "  --album   \"album\"\n"
                 "  --year    6969\n"
                 "  --track   1\n"
                 "  --cover   cover.jpg\n"
                 "  --show    show metadata\n"
                 "  --help    show this text stuff again\n";
}

CliOps parseArgs(int argc, char *argv[])
{
    CliOps opt;

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];

        if (arg == "--file")
            opt.file = argv[++i];
        else if (arg == "--title")
            opt.title = argv[++i];
        else if (arg == "--artist")
            opt.artist = argv[++i];
        else if (arg == "--album")
            opt.album = argv[++i];
        else if (arg == "--year")
            opt.year = std::stoi(argv[++i]);
        else if (arg == "--track")
            opt.track = std::stoi(argv[++i]);
        else if (arg == "--cover")
            opt.cover = argv[++i];
        else if (arg == "--show")
            opt.show = true;
        else if (arg == "--help")
        {
            printHelpStuff();
            std::exit(0);
        }
    }

    return opt;
}
