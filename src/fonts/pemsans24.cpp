#include <stdint.h>

#include "nyna/graphics/tiny_font.hpp"

namespace picoenvmon::fonts {

using namespace nyna::graphics;

static const uint8_t pemsans24_data[] = {
    0x7c, 0xe0, 0x03, 0xfe, 0xe0, 0x01, 0xff, 0xf1, 0x01, 0xc7, 0xf1, 0x00, 0xc7, 0xf9, 0x00, 0xc7, // '%' (0x25) : index=0, w=21
    0x79, 0x00, 0xff, 0x7d, 0x00, 0xfe, 0x3c, 0x00, 0x7c, 0x3e, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x1f, 
    0x00, 0x80, 0xcf, 0x07, 0x80, 0xe7, 0x0f, 0xc0, 0xf7, 0x1f, 0xc0, 0x73, 0x1c, 0xe0, 0x73, 0x1c, 
    0xe0, 0x71, 0x1c, 0xf0, 0xf1, 0x1f, 0xf0, 0xe0, 0x0f, 0xf8, 0xc0, 0x07, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // (BLANK) '&' (0x26) : index=72, w=0
    // (BLANK) ''' (0x27) : index=72, w=0
    // (BLANK) '(' (0x28) : index=72, w=0
    // (BLANK) ')' (0x29) : index=72, w=0
    // (BLANK) '*' (0x2a) : index=72, w=0
    // (BLANK) '+' (0x2b) : index=72, w=0
    // (BLANK) ',' (0x2c) : index=72, w=0
    // (BLANK) '-' (0x2d) : index=72, w=0
    // (BLANK) '.' (0x2e) : index=72, w=0
    // (BLANK) '/' (0x2f) : index=72, w=0
    // (BLANK) '0' (0x30) : index=72, w=0
    // (BLANK) '1' (0x31) : index=72, w=0
    // (BLANK) '2' (0x32) : index=72, w=0
    // (BLANK) '3' (0x33) : index=72, w=0
    // (BLANK) '4' (0x34) : index=72, w=0
    // (BLANK) '5' (0x35) : index=72, w=0
    // (BLANK) '6' (0x36) : index=72, w=0
    // (BLANK) '7' (0x37) : index=72, w=0
    // (BLANK) '8' (0x38) : index=72, w=0
    // (BLANK) '9' (0x39) : index=72, w=0
    // (BLANK) ':' (0x3a) : index=72, w=0
    // (BLANK) ';' (0x3b) : index=72, w=0
    // (BLANK) '<' (0x3c) : index=72, w=0
    // (BLANK) '=' (0x3d) : index=72, w=0
    // (BLANK) '>' (0x3e) : index=72, w=0
    // (BLANK) '?' (0x3f) : index=72, w=0
    // (BLANK) '@' (0x40) : index=72, w=0
    // (BLANK) 'A' (0x41) : index=72, w=0
    // (BLANK) 'B' (0x42) : index=72, w=0
    0xf0, 0x07, 0xfc, 0x1f, 0xfe, 0x3f, 0xfe, 0x7f, 0x3f, 0x3c, 0x1f, 0x18, 0x0f, 0x00, 0x0f, 0x00, // 'C' (0x43) : index=72, w=15
    0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x1f, 0x18, 0x3e, 0x3c, 
    0xfe, 0x7f, 0xfc, 0x3f, 0xf8, 0x1f, 0xe0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // (BLANK) 'D' (0x44) : index=120, w=0
    // (BLANK) 'E' (0x45) : index=120, w=0
    // (BLANK) 'F' (0x46) : index=120, w=0
    // (BLANK) 'G' (0x47) : index=120, w=0
    // (BLANK) 'H' (0x48) : index=120, w=0
    // (BLANK) 'I' (0x49) : index=120, w=0
    // (BLANK) 'J' (0x4a) : index=120, w=0
    // (BLANK) 'K' (0x4b) : index=120, w=0
    // (BLANK) 'L' (0x4c) : index=120, w=0
    // (BLANK) 'M' (0x4d) : index=120, w=0
    // (BLANK) 'N' (0x4e) : index=120, w=0
    // (BLANK) 'O' (0x4f) : index=120, w=0
    0xff, 0x03, 0xff, 0x0f, 0xff, 0x1f, 0x0f, 0x1f, 0x0f, 0x3e, 0x0f, 0x3c, 0x0f, 0x3c, 0x0f, 0x3c, // 'P' (0x50) : index=120, w=14
    0x0f, 0x3e, 0x0f, 0x1f, 0xff, 0x1f, 0xff, 0x0f, 0xff, 0x03, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 
    0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // (BLANK) 'Q' (0x51) : index=168, w=0
    // (BLANK) 'R' (0x52) : index=168, w=0
    // (BLANK) 'S' (0x53) : index=168, w=0
    // (BLANK) 'T' (0x54) : index=168, w=0
    // (BLANK) 'U' (0x55) : index=168, w=0
    // (BLANK) 'V' (0x56) : index=168, w=0
    // (BLANK) 'W' (0x57) : index=168, w=0
    // (BLANK) 'X' (0x58) : index=168, w=0
    // (BLANK) 'Y' (0x59) : index=168, w=0
    // (BLANK) 'Z' (0x5a) : index=168, w=0
    // (BLANK) '[' (0x5b) : index=168, w=0
    // (BLANK) '\' (0x5c) : index=168, w=0
    // (BLANK) ']' (0x5d) : index=168, w=0
    // (BLANK) '^' (0x5e) : index=168, w=0
    // (BLANK) '_' (0x5f) : index=168, w=0
    // (BLANK) '`' (0x60) : index=168, w=0
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x03, 0xfe, 0x0f, // 'a' (0x61) : index=168, w=13
    0xfe, 0x0f, 0x02, 0x1f, 0x00, 0x1e, 0xf0, 0x1f, 0xfc, 0x1f, 0xfe, 0x1f, 0x1f, 0x1e, 0x0f, 0x1e, 
    0x0f, 0x1f, 0xff, 0x1f, 0xfe, 0x1f, 0xfc, 0x1d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // (BLANK) 'b' (0x62) : index=216, w=0
    // (BLANK) 'c' (0x63) : index=216, w=0
    // (BLANK) 'd' (0x64) : index=216, w=0
    // (BLANK) 'e' (0x65) : index=216, w=0
    // (BLANK) 'f' (0x66) : index=216, w=0
    // (BLANK) 'g' (0x67) : index=216, w=0
    0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0xef, 0x03, 0xff, 0x0f, // 'h' (0x68) : index=216, w=13
    0xff, 0x0f, 0x1f, 0x1f, 0x0f, 0x1e, 0x0f, 0x1e, 0x0f, 0x1e, 0x0f, 0x1e, 0x0f, 0x1e, 0x0f, 0x1e, 
    0x0f, 0x1e, 0x0f, 0x1e, 0x0f, 0x1e, 0x0f, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // (BLANK) 'i' (0x69) : index=264, w=0
    // (BLANK) 'j' (0x6a) : index=264, w=0
    // (BLANK) 'k' (0x6b) : index=264, w=0
    // (BLANK) 'l' (0x6c) : index=264, w=0
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 'm' (0x6d) : index=264, w=18
    0x00, 0x00, 0xef, 0x70, 0x00, 0xff, 0xfb, 0x01, 0xff, 0xff, 0x01, 0x9f, 0xcf, 0x03, 0x8f, 0xc7, 
    0x03, 0x8f, 0xc7, 0x03, 0x8f, 0xc7, 0x03, 0x8f, 0xc7, 0x03, 0x8f, 0xc7, 0x03, 0x8f, 0xc7, 0x03, 
    0x8f, 0xc7, 0x03, 0x8f, 0xc7, 0x03, 0x8f, 0xc7, 0x03, 0x8f, 0xc7, 0x03, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // (BLANK) 'n' (0x6e) : index=336, w=0
    // (BLANK) 'o' (0x6f) : index=336, w=0
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xef, 0x03, 0xff, 0x0f, // 'p' (0x70) : index=336, w=13
    0xff, 0x0f, 0x1f, 0x1f, 0x0f, 0x1e, 0x0f, 0x1e, 0x0f, 0x1e, 0x0f, 0x1e, 0x0f, 0x1e, 0x0f, 0x1e, 
    0x1f, 0x1f, 0xff, 0x0f, 0xff, 0x0f, 0xef, 0x03, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 
    // (BLANK) 'q' (0x71) : index=384, w=0
    // (BLANK) 'r' (0x72) : index=384, w=0
    // (BLANK) 's' (0x73) : index=384, w=0
    // (BLANK) 't' (0x74) : index=384, w=0
    // (BLANK) 'u' (0x75) : index=384, w=0
    // (BLANK) 'v' (0x76) : index=384, w=0
    // (BLANK) 'w' (0x77) : index=384, w=0
    // (BLANK) 'x' (0x78) : index=384, w=0
    // (BLANK) 'y' (0x79) : index=384, w=0
    // (BLANK) 'z' (0x7a) : index=384, w=0
    // (BLANK) '{' (0x7b) : index=384, w=0
    // (BLANK) '|' (0x7c) : index=384, w=0
    // (BLANK) '}' (0x7d) : index=384, w=0
    // (BLANK) '~' (0x7e) : index=384, w=0
    // (BLANK) '' (0x7f) : index=384, w=0
    // (BLANK) '' (0x80) : index=384, w=0
    // (BLANK) '' (0x81) : index=384, w=0
    // (BLANK) '' (0x82) : index=384, w=0
    // (BLANK) '' (0x83) : index=384, w=0
    // (BLANK) '' (0x84) : index=384, w=0
    // (BLANK) '' (0x85) : index=384, w=0
    // (BLANK) '' (0x86) : index=384, w=0
    // (BLANK) '' (0x87) : index=384, w=0
    // (BLANK) '' (0x88) : index=384, w=0
    // (BLANK) '' (0x89) : index=384, w=0
    // (BLANK) '' (0x8a) : index=384, w=0
    // (BLANK) '' (0x8b) : index=384, w=0
    // (BLANK) '' (0x8c) : index=384, w=0
    // (BLANK) '' (0x8d) : index=384, w=0
    // (BLANK) '' (0x8e) : index=384, w=0
    // (BLANK) '' (0x8f) : index=384, w=0
    // (BLANK) '' (0x90) : index=384, w=0
    // (BLANK) '' (0x91) : index=384, w=0
    // (BLANK) '' (0x92) : index=384, w=0
    // (BLANK) '' (0x93) : index=384, w=0
    // (BLANK) '' (0x94) : index=384, w=0
    // (BLANK) '' (0x95) : index=384, w=0
    // (BLANK) '' (0x96) : index=384, w=0
    // (BLANK) '' (0x97) : index=384, w=0
    // (BLANK) '' (0x98) : index=384, w=0
    // (BLANK) '' (0x99) : index=384, w=0
    // (BLANK) '' (0x9a) : index=384, w=0
    // (BLANK) '' (0x9b) : index=384, w=0
    // (BLANK) '' (0x9c) : index=384, w=0
    // (BLANK) '' (0x9d) : index=384, w=0
    // (BLANK) '' (0x9e) : index=384, w=0
    // (BLANK) '' (0x9f) : index=384, w=0
    // (BLANK) ' ' (0xa0) : index=384, w=0
    // (BLANK) '¡' (0xa1) : index=384, w=0
    // (BLANK) '¢' (0xa2) : index=384, w=0
    // (BLANK) '£' (0xa3) : index=384, w=0
    // (BLANK) '¤' (0xa4) : index=384, w=0
    // (BLANK) '¥' (0xa5) : index=384, w=0
    // (BLANK) '¦' (0xa6) : index=384, w=0
    // (BLANK) '§' (0xa7) : index=384, w=0
    // (BLANK) '¨' (0xa8) : index=384, w=0
    // (BLANK) '©' (0xa9) : index=384, w=0
    // (BLANK) 'ª' (0xaa) : index=384, w=0
    // (BLANK) '«' (0xab) : index=384, w=0
    // (BLANK) '¬' (0xac) : index=384, w=0
    // (BLANK) '­' (0xad) : index=384, w=0
    // (BLANK) '®' (0xae) : index=384, w=0
    // (BLANK) '¯' (0xaf) : index=384, w=0
    // (BLANK) '°' (0xb0) : index=384, w=0
    // (BLANK) '±' (0xb1) : index=384, w=0
    // (BLANK) '²' (0xb2) : index=384, w=0
    // (BLANK) '³' (0xb3) : index=384, w=0
    // (BLANK) '´' (0xb4) : index=384, w=0
    // (BLANK) 'µ' (0xb5) : index=384, w=0
    // (BLANK) '¶' (0xb6) : index=384, w=0
    // (BLANK) '·' (0xb7) : index=384, w=0
    // (BLANK) '¸' (0xb8) : index=384, w=0
    // (BLANK) '¹' (0xb9) : index=384, w=0
    // (BLANK) 'º' (0xba) : index=384, w=0
    // (BLANK) '»' (0xbb) : index=384, w=0
    // (BLANK) '¼' (0xbc) : index=384, w=0
    // (BLANK) '½' (0xbd) : index=384, w=0
    // (BLANK) '¾' (0xbe) : index=384, w=0
    // (BLANK) '¿' (0xbf) : index=384, w=0
    // (BLANK) 'À' (0xc0) : index=384, w=0
    // (BLANK) 'Á' (0xc1) : index=384, w=0
    // (BLANK) 'Â' (0xc2) : index=384, w=0
    // (BLANK) 'Ã' (0xc3) : index=384, w=0
    // (BLANK) 'Ä' (0xc4) : index=384, w=0
    // (BLANK) 'Å' (0xc5) : index=384, w=0
    // (BLANK) 'Æ' (0xc6) : index=384, w=0
    // (BLANK) 'Ç' (0xc7) : index=384, w=0
    // (BLANK) 'È' (0xc8) : index=384, w=0
    // (BLANK) 'É' (0xc9) : index=384, w=0
    // (BLANK) 'Ê' (0xca) : index=384, w=0
    // (BLANK) 'Ë' (0xcb) : index=384, w=0
    // (BLANK) 'Ì' (0xcc) : index=384, w=0
    // (BLANK) 'Í' (0xcd) : index=384, w=0
    // (BLANK) 'Î' (0xce) : index=384, w=0
    // (BLANK) 'Ï' (0xcf) : index=384, w=0
    // (BLANK) 'Ð' (0xd0) : index=384, w=0
    // (BLANK) 'Ñ' (0xd1) : index=384, w=0
    // (BLANK) 'Ò' (0xd2) : index=384, w=0
    // (BLANK) 'Ó' (0xd3) : index=384, w=0
    // (BLANK) 'Ô' (0xd4) : index=384, w=0
    // (BLANK) 'Õ' (0xd5) : index=384, w=0
    // (BLANK) 'Ö' (0xd6) : index=384, w=0
    // (BLANK) '×' (0xd7) : index=384, w=0
    // (BLANK) 'Ø' (0xd8) : index=384, w=0
    // (BLANK) 'Ù' (0xd9) : index=384, w=0
    // (BLANK) 'Ú' (0xda) : index=384, w=0
    // (BLANK) 'Û' (0xdb) : index=384, w=0
    // (BLANK) 'Ü' (0xdc) : index=384, w=0
    // (BLANK) 'Ý' (0xdd) : index=384, w=0
    // (BLANK) 'Þ' (0xde) : index=384, w=0
    0x7c, 0x00, 0xfe, 0x00, 0xff, 0x01, 0xc7, 0x01, 0xc7, 0x01, 0xc7, 0x01, 0xff, 0x01, 0xfe, 0x00, // 'ß' (0xdf) : index=384, w=9
    0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

static const TinyFontGlyph pemsans24_index[] = {
    TinyFontGlyph(0, 21), 
    TinyFontGlyph(72, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(72, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(72, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(72, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(72, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(72, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(72, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(72, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(72, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(72, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(72, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(72, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(72, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(72, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(72, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(72, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(72, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(72, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(72, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(72, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(72, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(72, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(72, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(72, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(72, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(72, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(72, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(72, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(72, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(72, 15), 
    TinyFontGlyph(120, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(120, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(120, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(120, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(120, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(120, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(120, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(120, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(120, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(120, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(120, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(120, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(120, 14), 
    TinyFontGlyph(168, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(168, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(168, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(168, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(168, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(168, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(168, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(168, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(168, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(168, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(168, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(168, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(168, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(168, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(168, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(168, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(168, 13), 
    TinyFontGlyph(216, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(216, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(216, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(216, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(216, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(216, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(216, 13), 
    TinyFontGlyph(264, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(264, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(264, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(264, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(264, 18), 
    TinyFontGlyph(336, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(336, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(336, 13), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 0, TinyFontGlyph::BLANK), 
    TinyFontGlyph(384, 9), 
};

TinyFont pemsans24(24, 37, 187, 2, pemsans24_data, pemsans24_index);

}
