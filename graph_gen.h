#ifndef GRAPH_GEN_H
#define GRAPH_GEN_H
#include <fstream>
#include <vector>
#include <algorithm>
#include <time.h> 
#include <thread>
#include <atomic> 
#include <cstdlib>
#include <mutex> 
using namespace std; 
using Click = vector<pair<int, int>>;
struct Caveman {
    vector<Click> clicks; //list of clicks
    vector<pair<int, int>> links;//list of linked nodes
   // vector<int> nbrlinks;
    int nbrlinks = 1;
};
void remove_edge(Caveman caveman, int nbredge);

Click click_generator(long K, int start = 0);
void print_click(Click click);
void print_clickio(Click click, std::ostream& os);
Caveman caveman_generator(long K, long ncl, int nbrlinks = 1);


//link the clicker
//vector<pair<int, int>> click_linker(vector<Click> clicks);
vector<pair<int, int>> click_linker(vector<Click> clicks, int nbrlinks = 1);
void print_cavemanio(Caveman caveman, std::ostream& os);
void exec_louvain(long k, long n, int nbrlinks, std::fstream &fs);
void launch_cavemans(long K, long ncl, int nbrlinks = 1, int nbredge = 0);
Caveman write_caveman(long k, long n,int nbrlinks, std::fstream &fs);
void benchmark(long K, long ncl, int nbrlinks = 1);

#endif
