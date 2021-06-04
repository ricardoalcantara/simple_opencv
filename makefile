build:
	g++ main.cpp -std=c++0x -o app $(pkg-config --cflags --libs opencv4 x11)