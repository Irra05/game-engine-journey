CXX = g++
CXXFLAGS = -g -std=c++17
INCFLAGS = -Iinclude
LDFLAGS = -lGL -lGLU -lglfw -lGLEW

RM = rm -rf

all: main
main: out/main.o out/Camera.o out/FloorBox.o out/Player.o out/InputStatus.o out/SceneData.o
	$(CXX) -o main out/main.o out/SceneData.o out/FloorBox.o out/Camera.o out/Player.o out/InputStatus.o $(LDFLAGS)
out/main.o: out/
	$(CXX) -c -o out/main.o $(CXXFLAGS) $(INCFLAGS) src/main.cpp
out/Camera.o:
	$(CXX) -c -o out/Camera.o $(CXXFLAGS) $(INCFLAGS) src/gameObjects/Camera.cpp
out/FloorBox.o:
	$(CXX) -c -o out/FloorBox.o $(CXXFLAGS) $(INCFLAGS) src/gameObjects/FloorBox.cpp 
out/Player.o:
	$(CXX) -c -o out/Player.o $(CXXFLAGS) $(INCFLAGS) src/gameObjects/Player.cpp 
out/InputStatus.o:
	$(CXX) -c -o out/InputStatus.o $(CXXFLAGS) $(INCFLAGS) src/InputStatus.cpp 
out/SceneData.o:
	$(CXX) -c -o out/SceneData.o $(CXXFLAGS) $(INCFLAGS) src/SceneData.cpp 
out/:
	mkdir out

clean:
	$(RM) out/

update:
	make clean && make