/*
 * OrderGenerator.hpp
 *
 *  Created on: 10-Jun-2016
 *      Author: ankithbti
 */

#ifndef INCLUDE_ORDERGENERATOR_HPP_
#define INCLUDE_ORDERGENERATOR_HPP_


#include <Common.hpp>
#include <MktDataOrderMsg.hpp>
#include <MktDataTradeMsg.hpp>
#include <boost/regex.hpp>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <fstream>

namespace obLib{

  std::string hex_to_string(const std::string& input)
  {
    static const char* const lut = "0123456789abcdef";
    size_t len = input.length();
    if (len & 1) throw std::invalid_argument("odd length");

    std::string output;
    output.reserve(len / 2);
    for (size_t i = 0; i < len; i += 2)
      {
	char a = input[i];
	//std::cout << " Considering " << a << std::endl;
	const char* p = std::lower_bound(lut, lut + 16, a);
	if (*p != a) throw std::invalid_argument("not a hex digit");

	char b = input[i + 1];
	//std::cout << " Considering " << b << std::endl;
	const char* q = std::lower_bound(lut, lut + 16, b);
	if (*q != b) throw std::invalid_argument("not a hex digit");

	output.push_back(((p - lut) << 4) | (q - lut));
      }
    return output;
  }

  struct OrderGenerator{

    std::vector<MktDataOrderMsg*> _orders;
    std::vector<MktDataTradeMsg*> _trades;

    const std::vector<MktDataOrderMsg*>& getOrders() const {
      return _orders;
    }

    const std::vector<MktDataTradeMsg*>& getTrades() const {
      return _trades;
    }

    OrderGenerator(){
      std::ifstream in("/Users/ankithbti/Development/Cpp/orderBookIdeas/TCP_UDP_Dump/plainTextUDPDataPackets", std::ios::in|std::ios::binary);
      if(in.good()){
	  std::cout << " File is readable." << std::endl;
	  boost::regex expression("^[0-9]+[ \t]{2}([0-9 a-z]+)[ \t]{2}.+[ \t\n\r]*");

	  std::string line;
	  int count = 0;
	  int orderCount = 0;
	  int tradeCount = 0;
	  std::stringstream dataPacketStr;

	  int lineNo = 0;
	  while(std::getline(in, line)){
	      ++lineNo;
	      boost::cmatch what;

	      if(boost::regex_match(line.c_str(), what, expression))
		{
		  dataPacketStr << what[1] ;
		}
	      if(++count == 3){
		  std::string hexStr = dataPacketStr.str();
		  hexStr.erase(remove_if(hexStr.begin(), hexStr.end(), isspace), hexStr.end());
		  // Check
		  std::string decimalStr;
		  try{
		      decimalStr = hex_to_string(hexStr);
		  }catch(const std::invalid_argument& err){
		      std::cout << " Exception: " << err.what() << " While conveting string: " <<  hexStr << " || " << lineNo << " " << what[1] << std::endl;
		      count = 0;
		      dataPacketStr.clear();
		      dataPacketStr.str("");
		      continue;
		  }

		  char msgType;
		  memcpy((void*)&msgType, (void*)(decimalStr.c_str() + sizeof(MktDataGlobalHeaderMsg)) , sizeof(char));

		  switch(msgType){
		    case 'M':
		    case 'N':
		    case 'X':
		      {
			// Outright Order
			MktDataOrderMsg * mom = new MktDataOrderMsg();
			memcpy((void*)mom, (void*)decimalStr.c_str(), sizeof(MktDataOrderMsg));
			++orderCount;
			_orders.push_back(mom);
		      }
		      break;
		    case 'T':
		      {
			// Trade
			MktDataTradeMsg * mtm = new MktDataTradeMsg();
			memcpy((void*)mtm, (void*)decimalStr.c_str(), sizeof(MktDataTradeMsg));
			++tradeCount;
			_trades.push_back(mtm);
		      }
		      break;
		    case 'G':
		    case 'H':
		    case 'J':
		      {
			// Spread Order
			// G - New, H - Modify, J - Cancel
			std::cout << lineNo << " Spread Order. " << std::endl;
		      }
		      break;
		    case 'K':
		      // Spread Trade
		      std::cout << lineNo << " Spread Trade. " << std::endl;
		      break;
		    default:
		      throw std::runtime_error(" Unsupported MktData message.");
		      break;
		  }
		  count = 0;
		  dataPacketStr.clear();
		  dataPacketStr.str("");
	      }
	  }
	  std::cout << " OrderCount: " << orderCount << " " << _orders.size() << " TradeCount: " << tradeCount << " " << _trades.size() << std::endl;
	  in.close();
      }else{
	  std::cout << "File is not readable." << std::endl;
      }
    }

  };

}


#endif /* INCLUDE_ORDERGENERATOR_HPP_ */
