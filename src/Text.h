#pragma once

#include "ft2build.h"
#include FT_FREETYPE_H 
#include <string>
#include <glm/glm.hpp>
#include <map>
#include "Shader.h"

struct TextChar{
    unsigned int textureId;
    glm::ivec2 size;
    glm::ivec2 bearing;
    glm::ivec2 advance;
};

//文本渲染类
class Text{
public:
    Text(int w , int h);

    int init();

    void renderText(int x , int y ,std::wstring content , glm::vec4 color);

    void free();
private:
    unsigned int vao;
    unsigned int vbo;

    glm::mat4 orthMatrix;//正交视图 投影矩阵

    Shader shader;

    FT_Library ft;
    std::map<wchar_t , TextChar> charMap;

    int loadChar(wchar_t ch);//载入字符

    void renderTextChar(TextChar &textChar , glm::vec4 fontColor , float x , float y);

    const char* findFontPath();
};