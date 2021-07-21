#include "Text.h"
#include <iostream>
#include <string>
#include "config.h"

Text::Text(int w , int h){
    orthMatrix = glm::ortho(0.0f , static_cast<float>(w) , 0.0f , static_cast<float>(h));
}

int Text::init(){
    if(FT_Init_FreeType(&ft)){
        std::cout << "init FreeType Library Error!" << std::endl;
        return -1;
    }

    shader = Shader::buildGPUProgramFromFile("text_vertex.glsl","text_frag.glsl");
    //std::cout << "shader ID = " << shader.programId << std::endl;
    
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void *)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);      
    return 0;
}

void Text::renderText(int x , int y ,std::wstring content , glm::vec4 color){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

    glEnable(GL_DEPTH_TEST);

    for(int i = 0 ; i < content.size() ; i++){
        wchar_t ch = content[i];
        if(charMap.find(ch) ==  charMap.end()){//not found
            if(loadChar(ch) < 0)
                continue;
        }

        TextChar textChar = charMap[ch];

        float xpos = x + textChar.bearing.x;
        float ypos = y - (textChar.size.y - textChar.bearing.y);

        renderTextChar(textChar ,color , xpos , ypos);
        
        //std::cout << (wchar_t)ch <<  " x = " << x << std::endl;
        x += (textChar.advance.x / 64);
        // x += textChar.size.x;
    }//end for i
}

const char* Text::findFontPath(){
    // std::string fontFilePath = ASSETS_FOLDER + std::string("rage.ttf");
    // std::cout << fontFilePath << std::endl;
    // std::string fontFilePath = "D:\\gits\\render-engine\\assets\\rage.ttf";
    return "assets/jianti.ttf";
}

int Text::loadChar(wchar_t ch){
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //禁用字节对齐限制

    FT_Face face;

    //std::cout << "load char " << ch << std::endl;
    // std::cout << "font path = " << findFontPath() << std::endl;
    if (FT_New_Face(ft, findFontPath(), 0, &face)){
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        FT_Done_Face(face);
        return -1;
    }

    FT_Set_Pixel_Sizes(face, 0, 64);
    if (FT_Load_Char(face, ch, FT_LOAD_RENDER)){
        std::cout << "ERROR::FREETYTPE: Failed to load Glyph for chat = " << ch << std::endl;
        FT_Done_Face(face);
        return -1;
    }

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RED,
        face->glyph->bitmap.width,
        face->glyph->bitmap.rows,
        0,
        GL_RED,
        GL_UNSIGNED_BYTE,
        face->glyph->bitmap.buffer
    );

    // 设置纹理选项
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    TextChar textChar = {
        texture, 
        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
        glm::ivec2(face->glyph->advance.x , face->glyph->advance.y)
    };

    charMap[ch] = textChar;
    FT_Done_Face(face);
    return 0;
}

void Text::renderTextChar(TextChar &textChar , glm::vec4 fontColor , float xpos , float ypos){
    shader.useShader();

    shader.setUniformMat4("orthMat" , this->orthMatrix);
    shader.setUniformVec4("fontColor", fontColor);

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(vao);

    float w = textChar.size.x;
    float h = textChar.size.y;

    float p1 = 300.0;
    
    float vertices[6][4] = {
        { xpos,     ypos + h,   0.0, 0.0 },            
        { xpos,     ypos,       0.0, 1.0 },
        { xpos + w, ypos,       1.0, 1.0 },
        
        { xpos,     ypos + h,   0.0, 0.0 },
        { xpos + w, ypos,       1.0, 1.0 },
        { xpos + w, ypos + h,   1.0, 0.0 }   
    };

    glBindTexture(GL_TEXTURE_2D, textChar.textureId);
    // 更新VBO内存的内容
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Text::free(){
    glDeleteVertexArrays(1 , &vao);
    glDeleteBuffers(1 , &vbo);

    for(auto p : charMap){
        glDeleteTextures(1 , &(p.second.textureId));
    }//end for each
    FT_Done_FreeType(ft);
}