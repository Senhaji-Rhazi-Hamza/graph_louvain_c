#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
void print(std::ostream& os) 
{   
  os << "Print something to wherever the caller wants to" << std::endl;
} 
int main()
{
  std::vector<std::pair<std::string, int> > sortList;
  sortList.push_back(std::make_pair("hamza", 3));
  sortList.push_back(std::make_pair("othman", 4));
  auto it = std::find_if( sortList.begin(), sortList.end(),
      [](const std::pair<std::string, int>& element){ return element.first == "hamza";} );
  std::cout << (it == sortList.end()) << std::endl;

}
