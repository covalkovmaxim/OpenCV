run: 1.cpp 2.1.cpp 3.cpp 4.cpp 5.cpp
	g++ 1.cpp -std=c++11 `pkg-config opencv --cflags --libs` -o prog1
	g++ 2.1.cpp -std=c++11 `pkg-config opencv --cflags --libs` -o prog2
	g++ 3.cpp -std=c++11 `pkg-config opencv --cflags --libs` -o prog3
	g++ 4.cpp -std=c++11 `pkg-config opencv --cflags --libs` -o prog4
	g++ 5.cpp -std=c++11 `pkg-config opencv --cflags --libs` -o prog5
