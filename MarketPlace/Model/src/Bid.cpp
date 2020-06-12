#include "Bid.hpp"

using namespace demystify;
using namespace AgriBiz;
using namespace personal;

Bid::Bid() : _biddingPrice{0}, _quantity{0}, _bidder{User()}
{

}
Bid::Bid(const float& biddingPrice, const float& quantity, const User& bidder)
    : _biddingPrice{biddingPrice}, _quantity{quantity}, _bidder{bidder}
{

}
const float Bid::biddingPrice() const
{
    return this->_biddingPrice;
}
const float Bid::quantity() const
{
    return this->_quantity;
}
const User Bid::bidder() const
{
    return this->_bidder;
}
const BidStatus Bid::status() const
{
    return this->_status;
}
void Bid::biddingPrice(const float& biddingPrice)
{
    this->_biddingPrice = biddingPrice;
}
void Bid::quantity(const float& quantity)
{
    this->_quantity = quantity;
}
void Bid::bidder(const User& bidder)
{
    this->_bidder = bidder;
}
void Bid::status(const BidStatus& status)
{
    this->_status = status;
}