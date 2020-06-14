#ifndef BID_HPP_
#define BID_HPP_

#include <iostream>

#include "Identifiable.hpp"
#include "Datable.hpp"
#include "Subscribable.hpp"
#include "User.hpp"

using namespace std;

namespace demystify
{
namespace AgriBiz
{
namespace persistence
{
    class BidCRUD;
}

class Order;

using namespace personal;

enum class BidStatus
{
    PENDING,
    ACCEPTED,
    DECLINED,
    SUSPENDED
};

class Bid : public Identifiable, public Datable
{
private:
    float _biddingPrice;
    float _quantity; // In Kg
    User _bidder;
    BidStatus _status = BidStatus::PENDING;

    friend class Order; // Needed to set Bid status
    friend class BidCRUD; // Needed to set Bid status
public:
    Bid();
    Bid(const float& biddingPrice, const float& quantity, const User& bidder);
    
    const float biddingPrice() const;
    const float quantity() const;
    const User& bidder() const;
    const BidStatus status() const;

    void status(const BidStatus& status);
    void biddingPrice(const float& biddingPrice);
    void quantity(const float& quantity);
    void bidder(const User& bidder);
    
    // ~Bid();
};

} // namespace AgriBiz
    
} // namespace demystify


#endif //BID_HPP_
