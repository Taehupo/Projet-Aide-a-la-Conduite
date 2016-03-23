all:
	g++ -Wall -o main main.cpp ocvCore.cpp laneDetection.cpp  Flux.cpp Erreur.cpp Element.cpp Filtre.cpp Panneaux.cpp Vehicule_A.cpp Vehicule_C.cpp myException.cpp voiesCirculations.cpp `pkg-config --cflags --libs opencv` -std=c++11
clean:
	rm -fr main