#include <iostream>
#include <MktDataReceiver.hpp>
#include <MktDataMasterData.hpp>
#include <MktDataOrderMsg.hpp>
#include <ByteConverter.hpp>
#include <OrderGenerator.hpp>
#include <OrderBook.hpp>
#include <fstream>
#include <OrderBookManager.hpp>
#include <LatencyChecker.hpp>
#include <boost/regex.hpp>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <MktDataTradeMsg.hpp>

using namespace obLib;

// packets: 558273 - each packet is 80 bytes == 44661840 bytes
// size: 53605089 -

/*
 * ankithbti@~/Development/Cpp/orderBookLib>ulimit -a
core file size          (blocks, -c) 0
data seg size           (kbytes, -d) unlimited
file size               (blocks, -f) unlimited
max locked memory       (kbytes, -l) unlimited
max memory size         (kbytes, -m) unlimited
open files                      (-n) 256
pipe size            (512 bytes, -p) 1
stack size              (kbytes, -s) 8192
cpu time               (seconds, -t) unlimited
max user processes              (-u) 709
virtual memory          (kbytes, -v) unlimited
 */

int main()
{

  OrderGenerator og;
  OrderBookManager obm;

  int count = 0;
  for(auto& o : og.getOrders()){
      try{
	  SimpleOrder * so = new SimpleOrder(*o);
	  //so->print();
	  {
	    LatencyChecker lc;
	    obm.addOrder(so);
	  }
	  std::cout << "Checked: " << ++count << std::endl;
	  if(count == 25000){
	      break;
	  }

      }catch(const std::runtime_error& err){
	  o->print();
	  std::cout << " Exception: " << err.what() << std::endl;
      }
  }
  obm.print();
  std::cout << " Min Latency: " << LatencyChecker::_minlatency << std::endl;
  std::cout << " Max Latency: " << LatencyChecker::_maxLatency << std::endl;
  std::cout << " Average Latency: " << LatencyChecker::getAverageLatency() << std::endl;


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
