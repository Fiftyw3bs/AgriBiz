#include "MarketPlace.hpp"

using namespace demystify;
using namespace AgriBiz;
using namespace personal;

MarketPlace::MarketPlace()
{

}

bool MarketPlace::bid(const PointerOf<Bid>& bid, const PointerOf<Order>& order)
{
    bool success = false;

    if (bid->bidder() != order->orderer())
    {
        if (bid->quantity() <= order->quantity())
        {
            success = order->addSubscriber(bid);
        }
        else
        {
            // Offered quantity cannot exceed what is ordered
        }
    }
    else
    {
        // Owner of Order can't bid for his own Order
    }
    
    return success;
    
}

bool MarketPlace::cancelBid(const PointerOf<Bid>& bid, const PointerOf<Order>& order)
{
    return order->removeSubscriber(bid);
}

bool MarketPlace::placeOrder(const PointerOf<Order>& order)
{

}
bool MarketPlace::cancelOrder(const PointerOf<Order>& order)
{

}
bool MarketPlace::contactOrderer(const PointerOf<User>& sender, const PointerOf<Order>& order)
{

}
bool MarketPlace::report(const PointerOf<User>& reporter, const PointerOf<Order>& order)
{

}
VectorOf<Order> MarketPlace::orders(OrderStatus orderStatus)
{
    VectorOf<Order> orders;

    if (!this->getSubscribers().empty())
    {
        for(auto &orderPtr : this->getSubscribers())
        {
            if (auto order = orderPtr.lock(); order->status() == orderStatus)
            {
                orders.push_back(*order);
            } else if (orderStatus == OrderStatus::UNKNOWN)
            {
                orders.push_back(*order);
            } else
            {
                // Do Nothing!
            }
        }    
    } else
    {
        orders.push_back(Order());
    }

    return orders;    
}