/*
 * MktDataOrder.hpp
 *
 *  Created on: 30-May-2016
 *      Author: ankithbti
 */

#ifndef INCLUDE_MKTDATAORDERMSG_HPP_
#define INCLUDE_MKTDATAORDERMSG_HPP_

#include <MktDataGlobalHeaderMsg.hpp>

namespace obLib{

#pragma pack(push, 1) // For memory alignment
  struct MktDataOrderMsg
  {
    MktDataGlobalHeaderMsg _globalMktDataHeader;
    char _msgType; // 'N' - New / 'M' - Modify / 'X' - Cancel
    int64_t _timestamp; // milliseconds from 01-Jan-1980 00:00:00
    int64_t _orderId; // Day Unique Order Ref #
    int32_t _toeknNo; // Unique Contract Identifier
    char _orderType; // 'B' / 'S'
    int32_t _price; // in paise , // The price is in multiples of the tick size.
		    // For FO and CM segments this should be divided by 100 for converting into Rupees
    		    // For CD segment this should be divided by 107 for converting into Rupees.
    int32_t _qty;
  };
#pragma pack(pop)

}



#endif /* INCLUDE_MKTDATAORDERMSG_HPP_ */
