/*
 * LatencyChecker.hpp
 *
 *  Created on: 10-Jun-2016
 *      Author: ankithbti
 */

#ifndef INCLUDE_LATENCYCHECKER_HPP_
#define INCLUDE_LATENCYCHECKER_HPP_


#include <Common.hpp>

namespace obLib{
  struct LatencyChecker{

    std::chrono::high_resolution_clock::time_point _startTime;

    LatencyChecker() : _startTime(std::chrono::high_resolution_clock::now()){

    }

    ~LatencyChecker(){
      //auto latency = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - _startTime);
      std::cout << " Latency: " <<  (std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - _startTime)).count() << " ns" << std::endl;
    }

  };
}


#endif /* INCLUDE_LATENCYCHECKER_HPP_ */
