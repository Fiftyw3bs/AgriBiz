#include "AddBid.hpp"

using namespace demystify;
using namespace AgriBiz;
using namespace action;

AddBid::AddBid(const Bid& bid, PGPoolPtr pgPool) : _bid{bid}, _pgPool{pgPool}
{
}

bool AddBid::perform()
{
    auto bidDbo = BidCRUD(this->_pgPool);
    this->_bidId = bidDbo.add(this->_bid);
    return this->_bidId != 0;
}

BidID AddBid::result()
{
    return this->_bidId;
}