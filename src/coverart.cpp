#include "coverart.h"
#include <taglib/mp4file.h>
#include <taglib/mp4tag.h>
#include <taglib/mp4item.h>
#include <taglib/mpegfile.h>
#include <taglib/id3v2tag.h>
#include <taglib/attachedpictureframe.h>
#include <fstream>
#include <vector>
#include <iostream>

static std::vector<char> readFile(const std::string &path)
{
    std::ifstream f(path, std::ios::binary);
    if (!f)
    {
        std::cerr << "failed to open file: " << path << std::endl;
        return {};
    }
    return {std::istreambuf_iterator<char>(f), {}};
}

void addCoverArt(const std::string &audioFile, const std::string &imageFile)
{
    auto data = readFile(imageFile);
    if (data.empty())
        return;

    TagLib::ByteVector img(data.data(), data.size());
    if (audioFile.ends_with(".m4a"))
    {
        TagLib::MP4::File file(audioFile.c_str());
        TagLib::MP4::Tag *tag = file.tag();
        if (!tag)
        {
            std::cerr << "failed to read m4a tag: " << audioFile << std::endl;
            return;
        }

        TagLib::MP4::CoverArt cover(TagLib::MP4::CoverArt::JPEG, img);
        TagLib::MP4::CoverArtList list;
        list.append(cover);

        tag->setItem("covr", TagLib::MP4::Item(list));

        file.save();
    }
    else if (audioFile.ends_with(".mp3"))
    {
        TagLib::MPEG::File file(audioFile.c_str());
        TagLib::ID3v2::Tag *tag = file.ID3v2Tag(true);
        if (!tag)
        {
            std::cerr << "failed to read MP3 tag " << audioFile << std::endl;
            return;
        }

        auto *frame = new TagLib::ID3v2::AttachedPictureFrame;
        frame->setType(TagLib::ID3v2::AttachedPictureFrame::FrontCover);
        frame->setMimeType("image/jpeg");
        frame->setPicture(img);

        tag->addFrame(frame);
        file.save();
    }
    else
    {
        std::cerr << "unsupported file format: " << audioFile << std::endl;
    }
}
