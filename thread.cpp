#include <thread>
#include <iostream>
#include <atomic> 
#include <vector> 

void f(std::atomic<unsigned>& count, unsigned iter) {
  for (unsigned i = 0; i < iter; ++i)
    count++;
}
int main(int ac, char *av[]) {
  
  std::string s("hamza");
  std::cout << s + "hh";
  long                          worker = 8;
  if (ac > 1)
    worker = std::strtoul(av[1], NULL, 10);
  std::atomic<unsigned>         count;
  count = 0;
  std::vector<std::thread>      pool;
  for (int i = 0; i < worker; ++i)
    pool.emplace_back(f, std::ref(count), unsigned(100));
  for (auto& th : pool)
    th.join();
  std::cout << "count : " << count << std::endl;
}
