CC := g++

SRC_DIR := src
BUILD_DIR := build
STD := c++11
OUTPUT := output 

build_dir:
	mkdir -p ${BUILD_DIR}

compile: build_dir \
		${BUILD_DIR}/main.o \
		${BUILD_DIR}/glad.o \
		${BUILD_DIR}/App.o \
		${BUILD_DIR}/Camera.o \
		${BUILD_DIR}/Shader.o \
		${BUILD_DIR}/Scene.o \
		${BUILD_DIR}/Material.o \
		${BUILD_DIR}/Light.o \
		${BUILD_DIR}/SimpleCube.o \
		${BUILD_DIR}/CubeRender.o \
		${BUILD_DIR}/CoordinateGrid.o

${BUILD_DIR}/App.o:${SRC_DIR}/App.cpp
	${CC} -std=${STD} -c ${SRC_DIR}/App.cpp -o ${BUILD_DIR}/App.o -I include/

${BUILD_DIR}/Shader.o:${SRC_DIR}/Shader.cpp
	${CC} -std=${STD} -c ${SRC_DIR}/Shader.cpp -o ${BUILD_DIR}/Shader.o -I include/

${BUILD_DIR}/Camera.o:${SRC_DIR}/Camera.cpp
	${CC} -std=${STD} -c ${SRC_DIR}/Camera.cpp -o ${BUILD_DIR}/Camera.o -I include/

${BUILD_DIR}/Scene.o:${SRC_DIR}/Scene.cpp
	${CC} -std=${STD} -c ${SRC_DIR}/Scene.cpp -o ${BUILD_DIR}/Scene.o -I include/

${BUILD_DIR}/Material.o:${SRC_DIR}/Material.cpp
	${CC} -std=${STD} -c ${SRC_DIR}/Material.cpp -o ${BUILD_DIR}/Material.o -I include/

${BUILD_DIR}/Light.o:${SRC_DIR}/Light.cpp
	${CC} -std=${STD} -c ${SRC_DIR}/Light.cpp -o ${BUILD_DIR}/Light.o -I include/
	
${BUILD_DIR}/glad.o:${SRC_DIR}/glad.cpp
	${CC} -std=${STD} -c ${SRC_DIR}/glad.cpp -o ${BUILD_DIR}/glad.o -I include/

${BUILD_DIR}/Triangle.o:${SRC_DIR}/Triangle.cpp
	${CC} -std=${STD} -c ${SRC_DIR}/Triangle.cpp -o ${BUILD_DIR}/Triangle.o -I include/

${BUILD_DIR}/RectRender.o:${SRC_DIR}/RectRender.cpp
	${CC} -std=${STD} -c ${SRC_DIR}/RectRender.cpp -o ${BUILD_DIR}/RectRender.o -I include/

${BUILD_DIR}/CubeRender.o:${SRC_DIR}/CubeRender.cpp
	${CC} -std=${STD} -c ${SRC_DIR}/CubeRender.cpp -o ${BUILD_DIR}/CubeRender.o -I include/

${BUILD_DIR}/CoordinateGrid.o:${SRC_DIR}/CoordinateGrid.cpp
	${CC} -std=${STD} -c ${SRC_DIR}/CoordinateGrid.cpp -o ${BUILD_DIR}/CoordinateGrid.o -I include/

${BUILD_DIR}/SimpleCube.o:${SRC_DIR}/SimpleCube.cpp
	${CC} -std=${STD} -c ${SRC_DIR}/SimpleCube.cpp -o ${BUILD_DIR}/SimpleCube.o -I include/

${BUILD_DIR}/main.o:${SRC_DIR}/main.cpp
	${CC} -std=${STD} -c ${SRC_DIR}/main.cpp -o ${BUILD_DIR}/main.o -I include/

link:compile
	${CC} ${BUILD_DIR}/*.o -o ${BUILD_DIR}/main.exe -Llib -lglfw3dll -lopengl32 
	
run:link
	${BUILD_DIR}/main

# test_compile:
# 	${CC} ${SRC_DIR}/test.cpp -o ${BUILD_DIR}/test -I include/
	
# test:test_compile
# 	${BUILD_DIR}/test

assemble:link
	mkdir -p ${BUILD_DIR}/${OUTPUT}
	cp -r assets ${BUILD_DIR}/${OUTPUT}
	cp -r shader ${BUILD_DIR}/${OUTPUT}
	cp -r ${BUILD_DIR}/main.exe ${BUILD_DIR}/${OUTPUT}
	cp -r glfw3.dll ${BUILD_DIR}/${OUTPUT}

clean:
	rm -f ${BUILD_DIR}/*.o 
	rm -f ${BUILD_DIR}/main.exe
	rm -rf ${BUILD_DIR}/${OUTPUT}