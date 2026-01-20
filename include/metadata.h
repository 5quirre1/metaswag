#pragma once
#include <string>

void readMetadata(const std::string &file);
void writeMetadata(
    const std::string &file,
    const std::string &title,
    const std::string &artist,
    const std::string &album,
    int year,
    int track);
