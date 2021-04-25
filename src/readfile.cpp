#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

#include "../include/glm/vec4.hpp"

std::string& trim(std::string &s, std::string suffix = " "){
	if (s.empty()) 
		return s;
	     
	s.erase(0,s.find_first_not_of(suffix));
	s.erase(s.find_last_not_of(suffix) + 1);
	return s;
}

struct vec2{
	float x,y;
};

struct vec3{
	float x,y,z;
};


class ModelData{
public:
	long mVertexCount;
	float *pVertexBuf;
	
	ModelData(long vCount) : mVertexCount(vCount){
	}
	
	~ModelData() {
		if(pVertexBuf != nullptr){
			delete pVertexBuf;
		}
		
		std::cout << "free Modeldata" << std::endl;
	}
};

class ParseObj{
public:
	bool debug = false;
	int parse(std::string filePath){
		std::ifstream infile(filePath);
		
		if(infile.is_open()){
			prepareData();
			std::string line;
			while(std::getline(infile , line)){
				//std::cout << "read file line : " << line << std::endl;
				readFileLine(line);
			}
			
			std::cout << "vertexCount : " << vertexCount << std::endl;
			std::cout << "normalCount : " << normalCount << std::endl;
		}

		infile.close();
		return 0;
	}
	
	ModelData *mModelData = nullptr;
	
private:
	long vertexCount; //
	long normalCount; //
	
	void prepareData(){
		vertexCount = 0;
		normalCount = 0;
		
		if(mModelData != nullptr){
			delete mModelData;
		}	
		
	}
	
	void readFileLine(std::string &line){
		if(line==" " || line.empty())
			return;

		std::string content = trim(line);
		if(content.empty())
			return;


		if(content[0] == '#'){ //
			return; 
		}
		if(debug){
			std::cout << content << std::endl;
		}

		std::vector<std::string> contents;
		std::istringstream in(content);
		std::string tmp;
		while(in >> tmp){
			//std::cout << tmp;
			contents.push_back(tmp);
		}//end while
		//std::cout << std::endl;


		size_t dimension = contents.size();
		//std::cout << dimension << std::endl;
		
		if(dimension <= 0)
			return;		
		//std::cout << contents[0] << std::endl;
		std::string type = contents[0];
		
		if(type == "v"){ //
			float x = std::stof(contents[1]);
			float y = std::stof(contents[2]);
			float z = std::stof(contents[3]);
			
			vertexCount += 1;
			//std::cout << x << " " << y << "  " << z << std::endl;
		}else if(type == "vn") {//
			float nx = std::stof(contents[1]);
			float ny = std::stof(contents[2]);
			float nz = std::stof(contents[3]);
			normalCount += 1;
			//float len = nx * nx + ny * ny + nz * nz;
			//std::cout << len << std::endl;
			//std::cout << nx << " " << ny << "  " << nz << std::endl;
		}else if(type == "vt") {//
			float v = std::stof(contents[2]);
			//std::cout << u << " " << v << "  " << std::endl;
		}else if(type == "f") {//
			
		}
		
	}
	
	void readFaceData() {
		
	}

};

int main(){
	ParseObj parserObj;
	parserObj.parse(std::string("01Alocasia_obj.obj"));
	return 0;
}