/** /brief BASE64
* A program for encoding and decoding strings in the BASE64 format
*/
#ifndef BASE64_BASE64_HH
#define BASE64_BASE64_HH

#include <cstdint>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

const unsigned char base64_alphabet[64] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
    'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b',
    'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', '+', '/'
}; /** symbols that can be encoded*/

const unsigned char base64_table[128] = {
    77,77,77,77,77,77,77,77,77,77,77,77,77,77,
    77,77,77,77,77,77,77,77,77,77,77,77,77,77,
    77,77,77,77,77,77,77,77,77,77,77,77,77,77,
    77,62,77,77,77,63,52,53,54,55,56,57,58,59,
    60,61,77,77,77,0,77,77,77,0,1,2,3,4,
    5,6,7,8,9,10,11,12,13,14,15,16,17,18,
    19,20,21,22,23,24,25,77,77,77,77,77,77,26,
    27,28,29,30,31,32,33,34,35,36,37,38,39,40,
    41,42,43,44,45,46,47,48,49,50,51,77,77,77,
    77,77,
};

const unsigned char pad_character = '=';

union bits24 {
    struct {
        std::uint32_t i3 : 6;
        std::uint32_t i2 : 6;
        std::uint32_t i1 : 6;
        std::uint32_t i0 : 6;
        std::uint8_t     : 0;
    };
    struct {
        unsigned char bytes[4];
    };
};

static_assert(sizeof(bits24) >= 3, "bad 24-bit group size");
/** \brief function to check a string for invalid index or symbol
* \param[in] ch element of string
* \return index
*/
inline unsigned char
char_to_index(unsigned char ch) {
    if (ch >= 128) {
        throw std::invalid_argument("bad base64 string");
    }
    unsigned char result = base64_table[ch];
    if (result == 77) {
        throw std::invalid_argument("bad base64 string");
    }
    return result;
}
/** \brief A function to calculate the length of the string after encoding
* \param[in] length of string
* \return size of final string
*/
inline size_t
base64_encoded_size(size_t len) {
    if (len > std::numeric_limits<size_t>::max()/4u*3u-2u) {
        throw std::length_error("base64 length is too large");
    }
    return ((len + 2u) / 3u) * 4u;
}

/** \brief A function that encodes a string into the BASE64 format
* \param[in] first original string
* \param[in] n the size of the original string
* \param[in] result a string where the result of the program will be written
*/
void
base64_encode(const char* first, size_t n, char* result) noexcept {
    const size_t rem = n%3;
    const size_t m = (rem == 0) ? n : (n-rem);
    for (size_t i=0; i<m; i+=3) {
        bits24 bits{};
        bits.bytes[2] = *first;
        bits.bytes[1] = *++first;
        bits.bytes[0] = *++first;
        *result++ = base64_alphabet[bits.i0];
        *result++ = base64_alphabet[bits.i1];
        *result++ = base64_alphabet[bits.i2];
        *result++ = base64_alphabet[bits.i3];
        ++first;
    }
    if (rem == 1) {
        bits24 bits{};
        bits.bytes[2] = *first;
        *result++ = base64_alphabet[bits.i0];
        *result++ = base64_alphabet[bits.i1];
        *result++ = pad_character;
        *result++ = pad_character;
    } else   if (rem == 2) {
        bits24 bits{};
        bits.bytes[2] = *first;
        bits.bytes[1] = *++first;
        *result++ = base64_alphabet[bits.i0];
        *result++ = base64_alphabet[bits.i1];
        *result++ = base64_alphabet[bits.i2];
        *result++ = pad_character;
    }
}
/**\brief A function to calculate the maximum length of a string after decoding
* \param[in] len length of oridginal string
* \return maximum length
*/
size_t
base64_max_decoded_size(size_t len) noexcept {
    return (len / 4u) * 3u;
}

/** \brief A function that decodes a string from the BASE64 format
* \param[in] first original string
* \param[in] n the size of the original string
* \param[in] result a string where the result of the program will be written
* \return decoded string
* \throw invalid_argument the length of the input string is not a multiple
* of four, or the string contains invalid characters, or if the string is too large
*/
size_t
base64_decode(const char* first, size_t n, char* result) {
    const char* old = result;
    if (n%4) {
        throw std::invalid_argument("bad base64 string");
    }
    if (n == 0) {
        return 0;
    }
    n -= 4;
    for (size_t i=0; i<n; i+=4) {
        bits24 bits{};
        bits.i0 = char_to_index(*first);
        bits.i1 = char_to_index(*++first);
        bits.i2 = char_to_index(*++first);
        bits.i3 = char_to_index(*++first);
        *result++ = bits.bytes[2];
        *result++ = bits.bytes[1];
        *result++ = bits.bytes[0];
        ++first;
    }
    // process last four bytes
    if (first[2] == pad_character && first[3] == pad_character) {
        bits24 bits{};
        bits.i0 = char_to_index(*first);
        bits.i1 = char_to_index(*++first);
        *result++ = bits.bytes[2];
    } else if (first[3] == pad_character) {
        bits24 bits{};
        bits.i0 = char_to_index(*first);
        bits.i1 = char_to_index(*++first);
        bits.i2 = char_to_index(*++first);
        *result++ = bits.bytes[2];
        *result++ = bits.bytes[1];
    } else {
        bits24 bits{};
        bits.i0 = char_to_index(*first);
        bits.i1 = char_to_index(*++first);
        bits.i2 = char_to_index(*++first);
        bits.i3 = char_to_index(*++first);
        *result++ = bits.bytes[2];
        *result++ = bits.bytes[1];
        *result++ = bits.bytes[0];
    }
    return result - old;
}

#endif // vim:filetype=cpp
