#include "App.h"
// #include "Triangle.h"
// #include "RectRender.h"
// #include "CubeRender.h"
#include "Scene.h"
#include "SimpleCube.h"
#include "Model.h"
#include "Shader.h"
#include "demo.hpp"

int main(){
    ShowModel app;
    app.init();
    return app.mainLoop();
}


// int main() {
//     LoadAndParseMtlFile("assets/zero_plane.mtl");
//     SimpleCubeScene app;
    
//     app.isFullScreen = false;
//     app.init();
//     return app.mainLoop();
// }

// int main(){
//     // std::vector<Material> list = Model::LoadAndParseMtlFile("assets/zero_plane.mtl");
//     std::vector<Material> list = Model::LoadAndParseMtlFile("assets/Tosa.mtl");
//     //std::vector<Material> list = Model::LoadAndParseMtlFile("E:\\assets\\fangzi\\models\\house-hill-small.mtl");
//     for(Material &material : list){
//         std::cout << material.name <<" ===== " << std::endl;
//         std::cout << " Ns = " <<material.shininess << std::endl;
//         std::cout << " Ka = " <<material.ambient[0] << material.ambient[1] <<material.ambient[2] << std::endl;
//         std::cout << " Ks = " <<material.specular[0] << material.specular[1] <<material.specular[2] << std::endl;
//         std::cout << " illum = " <<material.illum << std::endl;
//         std::cout << " map_Kd = " <<material.diffuseMapFile << std::endl;
//         std::cout << " map_Bump = " <<material.bumpFile << std::endl;
//     }
//     return 0;
// }

// int main(){
//     ObjModel objModel;
//     objModel.loadObjFile("assets/house-hill-small.obj");
//     return 0;
// }




