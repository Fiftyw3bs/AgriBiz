#include "DeleteBid.hpp"

using namespace demystify;
using namespace AgriBiz;
using namespace action;

DeleteBid::DeleteBid(const Bid& bid, PGPoolPtr pgPool) : _bid{bid}, _pgPool{pgPool}
{
}

bool DeleteBid::perform()
{
    auto bidDbo = BidCRUD(this->_pgPool);
    return bidDbo.remove(this->_bid);
}