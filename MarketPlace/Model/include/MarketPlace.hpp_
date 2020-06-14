#ifndef MARKET_PLACE_HPP_
#define MARKET_PLACE_HPP_

#include <iostream>

#include "Models.hpp"
#include "Bid.hpp"
#include "Order.hpp"
#include "IRole.hpp"

using namespace std;

namespace demystify
{
namespace AgriBiz
{

enum class SortEntity
{
    FARM_PRODUCE,
    SELLER,
    BUYER,
    DATE_POSTED,
    ORDER_END_DATE,
    SELLER_RATING,
    COST
};

enum class SortOrder
{
    ASCENDING,
    DESCENDING
};

using namespace personal;

class MarketPlace : public Identifiable, public Subscribable<Order>
{
public:
    MarketPlace();

    bool bid(const PointerOf<Bid>& bid, const PointerOf<Order>& order);
    bool cancelBid(const PointerOf<Bid>& bid, const PointerOf<Order>& order);

    bool placeOrder(const PointerOf<Order>& order);
    bool cancelOrder(const PointerOf<Order>& order);

    bool contactOrderer(const PointerOf<User>& sender, const PointerOf<Order>& order);
    bool report(const PointerOf<User>& reporter, const PointerOf<Order>& order);
    
    VectorOf<Order> orders(OrderStatus orderStatus);
    VectorOf<Order> sort(SortEntity sortBy, SortOrder sortOrder);
    
    ~MarketPlace();
};

} // namespace AgriBiz
    
} // namespace demystify


#endif // MARKET_PLACE_HPP_
