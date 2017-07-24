#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "graph_gen.h"
using namespace std;
mutex mtx;
Click click_generator(long k, int start)
{
  k = k + start;
  Click click;
  for (long i = start; i < k; i ++)
  {
    for (long j = i; j < k ; j ++)
    {
      click.push_back(std::make_pair(i,j + 1));
    }
  }
  return click;
}
void print_click(Click click)
{
  long size = click.size();
  for (int i = 0; i < size; i++)
  {
    std::cout << click[i].first << "-->" << click[i].second << std::endl;
  }
}
void print_clickio(Click click, std::ostream& os)
{
  long size = click.size();
  for (int i = 0; i < size; i++)
  {
    os << click[i].first << " " << click[i].second << std::endl;
  }
}
void print_cavemanio(Caveman caveman, std::ostream& os)
{
  long size = caveman.clicks.size();
  int linksize = caveman.links.size();
  int j = 0;
  for (int i = 0; i < size; i++)
  {
//os <<"other click" << std::endl; //decoment to mark a click
    print_clickio(caveman.clicks[i], os);
  }
  //  os <<"links" << std::endl; // decomment to mark the links
  for (int p = 0; p < linksize; p ++)
  {
    os << caveman.links[p].first << " " << caveman.links[p].second << std::endl;
  }
}
Caveman caveman_generator(long K,long ncl, int nbrlinks)
{
  Caveman caveman;
  ncl--;
  for (long i = 0; i < K; i++)
  {
    caveman.clicks.push_back(click_generator(ncl,i * (ncl + 1)));
  }
  caveman.links = click_linker(caveman.clicks, nbrlinks);
  caveman.nbrlinks = nbrlinks;
  return caveman;
}
vector<pair<int, int>> click_linker(vector<Click> clicks, int nbrlinks)
{
  vector<pair<int, int>> vec;
  long size = clicks.size();
  int nbrlinkss = 0;
  for (long i = 0; i < size - 1; i++)
  {
    long size1_click = clicks[i].size();
    long size2_click = clicks[i + 1].size();
    srand (time(NULL));
    if (nbrlinks > 0)
      nbrlinkss = nbrlinks;
    else
      nbrlinkss =  rand() % size1_click;
    for (int j = 0; j < nbrlinkss; j ++)
    {
      long ith1 =  rand() % size1_click;
      long ith2 =  rand() % size2_click;
      vec.push_back(std::make_pair(clicks[i][ith1].first, clicks[i + 1][ith2].second));
    }
  }
  return vec;
}
Caveman write_caveman(long k, long n,int nbrlinks, std::fstream &fs)
{
  std::string s1 = std::to_string(n);
  std::string s2 = std::to_string(k);
  mtx.lock();
  fs.open ("cavemans/graph" + s1 +"_" +s2 + ".txt" , std::ios_base::app);
  Caveman caveman =  caveman_generator(k,n,nbrlinks);
  print_cavemanio(caveman, fs);
  fs.close();
  mtx.unlock();
  return caveman;
}
void launch_cavemans(long K, long ncl, int nbrlinks, int nbredge)
{
  std::fstream fs;
  for (long n = 2; n <= ncl ; n ++)
  {
    for (long k = 1;  k <= K ; k ++)
    {
      Caveman caveman = write_caveman(k, n, nbrlinks, fs);
      if(nbredge != 0)
        remove_edge(caveman, nbredge);
    }
  }
}
void exec_louvain(long k, long n, int nbrlinks, std::fstream &fs)
{
  clock_t t;
  t = clock();
  std::string s1 = std::to_string(n);
  std::string s2 = std::to_string(k);
  std::string file("graph" + s1 +"_" +s2);
  std::string arg1("./convert -i cavemans/" +file + ".txt" + " -o " + "bins/" +file +".bin  >/dev/null 2>&1");
  std::string arg2(" ./community bins/"+file +".bin -l -1 -v > " + "trees/" + file + ".tree  >/dev/null 2>&1");
  std::system(arg1.c_str());
  std::system(arg2.c_str());
  t = clock() - t;
  mtx.lock();
  fs.open ("Result.txt" , std::ios_base::app);
  fs << n << " " << k << " " /*<< nbrlinks <<  " "*/ << ((float)t)/CLOCKS_PER_SEC << std::endl;
  fs.close();
  mtx.unlock();
}
void benchmark(long K, long ncl, int nbrlinks)
{
  std::fstream fs;
  mtx.lock();
  fs.open ("Result.txt" , std::ios_base::app);
  fs <<  nbrlinks << " "  << std::endl;
  std::cout << "fi\n";
  fs.close();
  mtx.unlock();
  for (long n = 2; n <= ncl; n ++)
  {
    for (long k = 1;  k <= K ; k ++)
    {
      exec_louvain(k, n, nbrlinks, fs);
    }
  }
}
void remove_edge(Caveman caveman, int nbredge)
{

  long size_click = caveman.clicks[0].size();
  if (nbredge >= size_click - caveman.nbrlinks)
  {
   
    nbredge = size_click - caveman.nbrlinks - 1;
  }
  for (int i = 0; i < nbredge; i++) 
  {
    for (int j = 0; j < caveman.clicks.size(); j ++)
    {
      long size_click = caveman.clicks[j].size();
      long ith1 =  rand() % size_click;
      auto elt = caveman.clicks[j][ith1];
      //std::cout << elt.first;
      auto it = std::find_if(caveman.links.begin(), caveman.links.end(),
          [elt](const std::pair<int , int>& element){ 
          return ((element.first == elt.first)); 
          //|| (element.first == elt.second) 
          // || (element.second == elt.second));
          // || (element.second == elt.first)); 
          } );

      if (it == caveman.links.end())
      { 
        auto elt = (caveman.clicks[j].begin() + ith1); 
        //std::cout << (*elt).first << " " << (*elt).second <<std::endl;
        caveman.clicks[j].erase(caveman.clicks[j].begin() + ith1);
      }
      else
      {
        j--;
        //std::cout <<caveman.clicks[j].size() <<"\n";
      }
    }
  }
}

