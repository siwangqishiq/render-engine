#include "Text.h"
#include <iostream>
#include <string>
#include "config.h"

int Text::init(){
    if(FT_Init_FreeType(&ft)){
        std::cout << "init FreeType Library Error!" << std::endl;
        return -1;
    }

    std::string fontFilePath = ASSETS_FOLDER + "rage.ttf";
    if(FT_New_Face(ft , fontFilePath.c_str() , 0 , &face)){
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return -2;
    }

    FT_Set_Pixel_Sizes(face, 0, 48);

    if (FT_Load_Char(face, 'H', FT_LOAD_RENDER))
        std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;

    std::cout << "load font SUCCESS!" << std::endl;
    return 0;
}