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
    MarketPlace(const float& biddingPrice, const float& quantity, const User bidder);
    const float biddingPrice() const;
    const float quantity() const;
    const User bidder() const;
    const BidStatus status() const;

    void biddingPrice(const float& biddingPrice);
    void quantity(const float& quantity);
    void bidder(const User& bidder);
    void status(const BidStatus& status);

    bool bid(const Bid& bid);
    bool cancelBid(const Bid& bid);

    bool placeOrder(const Bid& bid);
    bool cancelOrder(const Bid& bid);
    
    ~MarketPlace();
};

} // namespace AgriBiz
    
} // namespace demystify


#endif // MARKET_PLACEID_HPP_
