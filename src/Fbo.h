#pragma once

class OffScreenTexture{
public:
    virtual void init();

    virtual void render();

    virtual void free();

private:
    unsigned int fbo;
};

