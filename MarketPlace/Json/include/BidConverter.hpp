#ifndef BID_CONTROLLER_HPP_
#define BID_CONTROLLER_HPP_

#include "JsonConversion.hpp"
#include "Bid.hpp"

using namespace demystify;

namespace demystify::JsonConversion
{
    using namespace AgriBiz;
    std::string BidAsJSON(const Bid& bid);
    Bid BidFromJSON(std::string bidJson);
} // namespace JsonConversion


#endif //BID_CONTROLLER_HPP_
