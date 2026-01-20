#include "metadata.h"
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <iostream>

void readMetadata(const std::string &file)
{
    TagLib::FileRef f(file.c_str());
    if (f.isNull() || !f.tag())
        return;

    auto *tag = f.tag();
    std::cout
        << "title:  " << tag->title() << "\n"
        << "artist: " << tag->artist() << "\n"
        << "album:  " << tag->album() << "\n"
        << "year:   " << tag->year() << "\n"
        << "track:  " << tag->track() << "\n";
}

void writeMetadata(
    const std::string &file,
    const std::string &title,
    const std::string &artist,
    const std::string &album,
    int year,
    int track)
{
    TagLib::FileRef f(file.c_str());
    if (f.isNull() || !f.tag())
        return;

    auto *tag = f.tag();

    if (!title.empty())
        tag->setTitle(title);
    if (!artist.empty())
        tag->setArtist(artist);
    if (!album.empty())
        tag->setAlbum(album);
    if (year)
        tag->setYear(year);
    if (track)
        tag->setTrack(track);

    f.save();
}
