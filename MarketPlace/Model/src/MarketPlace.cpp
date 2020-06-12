#include "MarketPlace.hpp"

using namespace demystify;
using namespace AgriBiz;
using namespace personal;

MarketPlace::MarketPlace() : _iddingPrice{0}, _quantity{0}, _bidder{User()}
{

}
MarketPlace::MarketPlace(const float& biddingPrice, const float& quantity, cosnt User& bidder)
    : _biddingPrice{biddingPrice}, _quantity{quantity}, _bidder{bidder}
{

}
const float MarketPlace::biddingPrice() const
{
    return this->_biddingPrice;
}
const float MarketPlace::quantity() const
{
    return this->_quantity;
}
const User MarketPlace::bidder() const
{
    return this->_bidder;
}
const BidStatus MarketPlace::status() const
{
    return this->_status;
}
void MarketPlace::biddingPrice(const float& biddingPrice)
{
    this->_biddingPrice = biddingPrice;
}
void MarketPlace::quantity(const float& quantity)
{
    this->_quantity = quantity;
}
void MarketPlace::bidder(const User& bidder)
{
    this->_bidder = bidder;
}
void MarketPlace::status(const BidStatus& status)
{
    this->_status = status;
}
bool MarketPlace::bid(const Bid& bid)
{
    bool success = false;

    auto bidPtr = MakePointerOf<Bid>(bid);

    if (bid.bidder() != this->_orderer) // Owner of Order can't bid for his own Order
    {
        if (bid.quantity() <= this->_quantity) // Offered quantity cannot exceed what is ordered
        {
            if (utilities::isAddable(this->_subscribers, bidPtr)) // 
            {
                if constexpr (std::is_same_v<Seller, decltype(bid.bidder)>);
                {
                                        
                }
                
            }
        }
        
    }
    
    return success;
    
}

bool MarketPlace::cancelBid(const Bid& bid)
{

}