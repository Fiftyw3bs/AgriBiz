#ifndef MARKET_PLACE_HPP_
#define MARKET_PLACE_HPP_

#include <iostream>

#include "Identifiable.hpp"
#include "Datable.hpp"
#include "Subscribable.hpp"
#include "User.hpp"
#include "Bid.hpp"
#include "Order.hpp"

using namespace std;

namespace demystify
{
namespace AgriBiz
{

using namespace personal;

class MarketPlace : public Identifiable, public Subscribable<Order>
{
private:
    float _biddingPrice;
    float _quantity; // In Kg
    User _bidder;
    BidStatus _status = BidStatus::PENDING;

public:
    MarketPlace();

    bool bid(const Bid& bid);
    bool cancelBid(const Bid& bid);

    bool placeOrder(const Order& bid);
    bool cancelOrder(const Order& bid);
    
    ~MarketPlace();
};

} // namespace AgriBiz
    
} // namespace demystify


#endif // MARKET_PLACE_HPP_
