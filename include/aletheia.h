#ifndef TBD_H
#define TBD_H

// Common definitions, classes, or types that are shared between many areas go here

#include <string>
#include <vector>

inline std::vector<char> hashToChars(const std::vector<uint8_t> &hash)
{
    std::vector<char> rval;
    for (auto h : hash) {
        rval.push_back(static_cast<char>(h));
    }
    return rval;
}

inline std::vector<unsigned char> charsToHash(const std::vector<char> &chars)
{
    std::vector<unsigned char> rval;
    for (auto c : chars) {
        rval.push_back(static_cast<unsigned char>(c));
    }
    return rval;
}

#endif  // TBD_H
