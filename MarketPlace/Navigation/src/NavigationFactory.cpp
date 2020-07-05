#include "NavigationFactory.hpp"

using namespace demystify;
using namespace AgriBiz;

PointerOf<Navigator> NavigationFactory::operator()(const http_request& message, PGPoolPtr& pgPool)
{
    auto [controller, args] = Navigator::parseRequest(message);

    if (controller == "bids")
    {
        BidNavigator navigator(message, pgPool);
        return MakePointerOf<BidNavigator>(navigator);
    }
    else if (controller == "orders")
    {
        OrderNavigator navigator(message, pgPool);
        return MakePointerOf<OrderNavigator>(navigator);
    }
    else if (controller == "farmProducts")
    {
        FarmProduceNavigator navigator(message, pgPool);
        return MakePointerOf<FarmProduceNavigator>(navigator);
    }
    
    
}