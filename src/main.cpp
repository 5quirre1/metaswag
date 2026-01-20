#include "cli.h"
#include "metadata.h"
#include "coverart.h"
#include <iostream>

int main(int argc, char *argv[])
{
    auto opt = parseArgs(argc, argv);

    if (opt.file.empty())
    {
        printHelpStuff();
        return 1;
    }

    if (opt.show)
    {
        readMetadata(opt.file);
        return 0;
    }

    writeMetadata(
        opt.file,
        opt.title,
        opt.artist,
        opt.album,
        opt.year,
        opt.track);

    if (!opt.cover.empty())
        addCoverArt(opt.file, opt.cover);

    std::cout << "done!!!\n";
}
