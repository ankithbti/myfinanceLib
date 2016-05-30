/*
 * Contract.hpp
 *
 *  Created on: 30-May-2016
 *      Author: ankithbti
 */

#ifndef INCLUDE_CONTRACT_HPP_
#define INCLUDE_CONTRACT_HPP_

#include <Common.hpp>

namespace obLib
{
  class Contract : private boost::noncopyable
  {

  private:
    short _streamId;
    int _tokenNo;
    std::string _instrument;
    std::string _symbol;
    int _expiryDate; // seconds from 01-Jan-1980 00:00:00
    int _strikePrice; // in paise
    std::string _optionType;

  public:
    Contract(int token, const std::string& symbol) : _tokenNo(token), _symbol(symbol){

    }

    int getToken() const {
      return _tokenNo;
    }

    const std::string& getSymbol() const {
      return _symbol;
    }

  };
}



#endif /* INCLUDE_CONTRACT_HPP_ */
