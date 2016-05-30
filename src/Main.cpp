#include <iostream>
#include <MktDataReceiver.hpp>
#include <MktDataMasterData.hpp>

using namespace obLib;

int main()
{

  short i = 1;
  char *c = (char*)&i;
  if(*c){
      std::cout << " Little Endian " ;
  }else{
      std::cout << " Big Endian " ;
  }
  std::cout << std::endl;


  LOG("Hello OrderBook");
  //std::cout << " Hello OrderBook " << std::endl;
  return 0;
};
