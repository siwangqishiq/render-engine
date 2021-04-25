#include "App.h"
// #include "Triangle.h"
// #include "RectRender.h"
// #include "CubeRender.h"
#include "Scene.h"
#include "SimpleCube.h"

int main() {
    SimpleCubeScene app;
    
    app.isFullScreen = false;
    app.init();
    return app.mainLoop();
}




