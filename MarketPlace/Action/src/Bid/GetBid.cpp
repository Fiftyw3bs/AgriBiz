#include "GetBid.hpp"

using namespace demystify;
using namespace AgriBiz;
using namespace action;

GetBid::GetBid(const Bid& bid, PGPoolPtr pgPool) : _bid{bid}, _pgPool{pgPool}
{
}

bool GetBid::perform()
{
    auto bidDbo = BidCRUD(this->_pgPool);
    this->_bid = bidDbo.fetch(this->_bid);
    return this->_bid.getId() != 0;
}

Bid GetBid::result()
{
    return this->_bid;
}