#pragma once

#include "ft2build.h"
#include FT_FREETYPE_H 

class Text{
public:
    int init();

protected:
    FT_Library ft;
    FT_Face face;
};