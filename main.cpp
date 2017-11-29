#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "maxHeapDijkstra.h"
#include "noHeapDijkstra.h"
#include "Kruskal.h"


int main(int argc, const char **argv) {
    int e;
    char type = argv[2][0];
    if (argc != 3 || std::atoi(argv[1])<1 || (type != 's' && type != 'd')) {
	std::cout<<"argc="<<argc<<" argv[1]="<<argv[1]<<" argv[2][0]="<<argv[2][0]<<std::endl;
	std::cout<<" use ./main [#vertices] [s/d]"<<std::endl;
	return 0;
    }
    int size = std::atoi(argv[1]);
    if (type == 's') {
	e = 8;
    } else {
	e = size/5;
    }

    srand(time(0));
    int s = 0;
    int t = 0;
    Graph G(size, e);
    while (s == t) {
	s = rand()%size + 1;
	t = rand()%size + 1;
    }
    noHeapDijkstra NHD(G);
    MaxBWPath sol1;
    maxHeapDijkstra MHD(G);
    MaxBWPath sol2;
    Kruskal K(G);
    MaxBWPath sol3;


    clock_t start_s1 = clock();
    sol1 = MHD.Search(s, t);
    clock_t stop_s1 = clock();
    double t1 = ((double)(stop_s1-start_s1))/(double)CLOCKS_PER_SEC*1000;

    clock_t start_s2 = clock();
    sol2 = NHD.Search(s, t);
    clock_t stop_s2 = clock();
    double t2 = ((double)(stop_s2-start_s2))/(double)CLOCKS_PER_SEC*1000;

    clock_t start_s3 = clock();
    sol3 = K.FindPath(s, t);
    clock_t stop_s3 = clock();
    double t3 = ((double)(stop_s3-start_s3))/(double)CLOCKS_PER_SEC*1000;

    std::cout<<"Max Heap: "<<std::endl;
    std::cout<<"Time (ms): "<<t1<<std::endl;
    std::cout<<"BW: "<<sol1.bw<<std::endl;
    std::cout<<"Path: "<<std::endl;
    for (int i=0; i<sol1.path.size(); i++) {
	std::cout<<sol1.path[i]<<std::endl;
    }

    std::cout<<std::endl;

    std::cout<<"No Heap: "<<std::endl;
    std::cout<<"Time (ms): "<<t2<<std::endl;
    std::cout<<"BW: "<<sol2.bw<<std::endl;
    std::cout<<"Path: "<<std::endl;
    for (int i=0; i<sol2.path.size(); i++) {
	std::cout<<sol2.path[i]<<std::endl;
    }

    std::cout<<std::endl;

    std::cout<<"Kruskal: "<<std::endl;
    std::cout<<"Time (ms): "<<t3<<std::endl;
    std::cout<<"BW: "<<sol3.bw<<std::endl;
    std::cout<<"Path: "<<std::endl;
    for (int i=0; i<sol3.path.size(); i++) {
	std::cout<<sol3.path[i]<<std::endl;
    }

    std::cout<<std::endl;

    return 0;
}
