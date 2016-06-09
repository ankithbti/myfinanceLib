/*
 * OrderBookManager.hpp
 *
 *  Created on: 30-May-2016
 *      Author: ankithbti
 */

#ifndef INCLUDE_ORDERBOOKMANAGER_HPP_
#define INCLUDE_ORDERBOOKMANAGER_HPP_

#include <Common.hpp>
#include <OrderBook.hpp>

namespace obLib{

  struct OrderBookManager : private boost::noncopyable
  {
    typedef std::unordered_map<TokenId, OrderBook*> OrderBookContainer;
    OrderBook* _tmpOb;
    OrderBookContainer _orderBooks;

    void addOrder(Order* order){
      // Check if we have already the OrderBook for this security
      std::pair<OrderBookContainer::iterator, bool> retVal = _orderBooks.insert(std::make_pair(order->tokenId(), _tmpOb));
      if(retVal.second){
	  retVal.first->second = new OrderBook();
      }
      // Now we have the orderBook
      OrderBook* book = retVal.first->second;
      switch(order->getType()){
	case 'N':
	  book->addNew(order);
	  break;
	case 'M':
	  book->replace(order);
	  break;
	case 'X':
	  book->cancel(order);
	  break;
	default:
	  throw std::runtime_error("Unsupported Order Type.");
	  break;
      }

    }

    void addTrade(){

    }

    void print(){
      for(auto i : _orderBooks){
	  std::cout << " TokenNo: " << i.first << " Transactions in orderBook: " << i.second->getTransactionId() << std::endl;
      }
    }

  };
}



#endif /* INCLUDE_ORDERBOOKMANAGER_HPP_ */
