#include <iostream>
#include <MktDataReceiver.hpp>
#include <MktDataMasterData.hpp>
#include <MktDataOrderMsg.hpp>
#include <UdpPackets.hpp>
#include <ByteConverter.hpp>
#include <OrderGenerator.hpp>
#include <OrderBook.hpp>
#include <fstream>
#include <OrderBookManager.hpp>
#include <LatencyChecker.hpp>

using namespace obLib;

// packets: 558273 - each packet is 80 bytes == 44661840 bytes
// size: 53605089 -

int main()
{
  OrderGenerator og;

  OrderBookManager obm;

  for(auto& o : og.getOrders()){
      try{
	  SimpleOrder * so = new SimpleOrder(o);
	  so->print();
	  {
	    LatencyChecker lc;
	    obm.addOrder(so);
	  }
      }catch(const std::runtime_error& err){
	  o.print();
	  std::cout << " Exception: " << err.what() << std::endl;
      }
  }
  obm.print();


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
