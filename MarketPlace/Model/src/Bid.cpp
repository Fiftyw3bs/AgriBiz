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
const User& Bid::bidder() const
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
const std::string Bid::status(StringOutput) const
{
    std::string status;

    switch (this->_status)
    {
    case BidStatus::PENDING:
        status = "PENDING";
        break;
    case BidStatus::ACCEPTED:
        status = "ACCEPTED";
        break;
    case BidStatus::DECLINED:
        status = "DECLINED";
        break;
    case BidStatus::SUSPENDED:
        status = "SUSPENDED";
        break;
    case BidStatus::COMPLETED:
        status = "COMPLETED";
        break;
    }

    return status;
}
void Bid::status(const std::string& status)
{
    if (status == "PENDING")
    {
        this->_status = BidStatus::PENDING;
    }
    else if (status == "ACCEPTED")
    {
        this->_status = BidStatus::ACCEPTED;
    }
    else if (status == "DECLINED")
    {
        this->_status = BidStatus::DECLINED;
    }
    else if (status == "SUSPENDED")
    {
        this->_status = BidStatus::SUSPENDED;
    }
    else if (status == "COMPLETED")
    {
        this->_status = BidStatus::COMPLETED;
    }
}
