#ifndef BID_CONTROLLER_HPP_
#define BID_CONTROLLER_HPP_

#include "AgriBiz_Persistence.hpp"
#include "Controller_Impl.hpp"
#include "JsonConversion.hpp"
#include "Bid.hpp"

using namespace demystify;
using namespace AgriBiz::persistence;

using BidController = demystify::AgriBiz::controller::Controller<BidCRUD>;

namespace demystify::JsonConversion
{
    using namespace AgriBiz;
    web::json::value BidAsJSON(const Bid& bid);
    Bid BidFromJSON(const web::json::value& bidJson);
} // namespace JsonConversion


#endif //BID_CONTROLLER_HPP_
