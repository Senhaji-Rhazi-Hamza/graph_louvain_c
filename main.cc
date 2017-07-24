#include "graph_gen.h"
#include <iostream>
#include <string>
#include <vector> 
//std::mutex mtx;
int main()
{
  for (int i = 1; i <= 10; i++)
  {
    std::string arg1("rm cavemans/* bins/* trees/*  >/dev/null 2>&1");
    launch_cavemans(50, 35, 1,i);
    std::cout << "another";
    benchmark(50, 35, 1);
  }
}
