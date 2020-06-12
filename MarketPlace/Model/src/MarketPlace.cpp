#include "MarketPlace.hpp"

using namespace demystify;
using namespace AgriBiz;
using namespace personal;

MarketPlace::MarketPlace() : _biddingPrice{0}, _quantity{0}, _bidder{User()}
{

}

bool MarketPlace::bid(const Bid& bid, const Order& order)
{
    bool success = false;

    // auto bidPtr = MakePointerOf<Bid>(bid);

    if (bid.bidder() != order) // Owner of Order can't bid for his own Order
    {
        if (bid.quantity() <= order.quantity()) // Offered quantity cannot exceed what is ordered
        {
            success = this->addSubscriber(MakePointerOf<Bid>(bid));
        }
    }
    
    return success;
    
}

bool MarketPlace::cancelBid(const Bid& bid)
{

}

bool MarketPlace::placeOrder(const Order& bid)
{

}
bool MarketPlace::cancelOrder(const Order& bid)
{

}