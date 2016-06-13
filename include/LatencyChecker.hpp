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

    static long _averageLatency ;
    static long _count;
    static long _maxLatency;
    static long _minlatency;
    LatencyChecker() : _startTime(std::chrono::high_resolution_clock::now()){
    }

    ~LatencyChecker(){
      auto latency = (std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - _startTime)).count();
      if(_minlatency > latency){
	  _minlatency = latency;
      }
      if(_maxLatency < latency){
	  _maxLatency = latency;
      }
      _averageLatency += latency;
      ++_count;
      std::cout << " Latency: " <<  latency << " ns" << std::endl;
    }

    static long getAverageLatency(){
      return _averageLatency/_count;
    }

  };

  long LatencyChecker::_count = 0;
  long LatencyChecker::_maxLatency = 0;
  long LatencyChecker::_minlatency = 0;
  long LatencyChecker::_averageLatency = 0;
}


#endif /* INCLUDE_LATENCYCHECKER_HPP_ */
