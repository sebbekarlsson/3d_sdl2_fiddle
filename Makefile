FLAGZ = `pkg-config --libs sdl2` -lGL -lglut -lSDL2_image -lSDL2_ttf -lGLU -g


output:\
    src/main.o\
    src/App.o\
    src/Camera.o\
    src/Cube.o\
    src/Gun.o\
    src/Instance.o\
    src/MathHelper.o\
    src/Scene.o\
    src/TestScene.o
	g++ $(FLAGZ)\
	    src/main.o\
	    src/App.o\
	    src/Camera.o\
	    src/Cube.o\
	    src/Gun.o\
	    src/Instance.o\
	    src/MathHelper.o\
	    src/Scene.o\
	    src/TestScene.o\
	    -o sdl2fiddle

main.o: src/main.cpp
	g++ $(FLAGZ) -c src/main.cpp

Camera.o: src/Camera.cpp src/Camera.h
	g++ $(FLAGZ) -c src/Camera.cpp

App.o: src/App.cpp src/App.h
	g++ $(FLAGZ) -c src/App.cpp

Cube.o: src/Cube.cpp src/Cube.h
	g++ $(FLAGZ) -c src/Cube.cpp

Gun.o: src/Gun.cpp src/Gun.h
	g++ $(FLAGZ) -c src/Gun.cpp

Instance.o: src/Instance.cpp src/Instance.h
	g++ $(FLAGZ) -c src/Instance.cpp

MathHelper.o: src/MathHelper.cpp src/MathHelper.h
	g++ $(FLAGZ) -c src/MathHelper.cpp

Scene.o: src/Scene.cpp src/Scene.h
	g++ $(FLAGZ) -c src/Scene.cpp

TestScene.o: src/TestScene.cpp src/TestScene.h
	g++ $(FLAGZ) -c src/TestScene.cpp

clean:
	rm src/*.o
