#include "EditBid.hpp"

using namespace demystify;
using namespace AgriBiz;
using namespace action;

EditBid::EditBid(const Bid& bid, PGPoolPtr pgPool) : _bid{bid}, _pgPool{pgPool}
{
}

bool EditBid::perform()
{
    auto bidDbo = BidCRUD(this->_pgPool);
    return bidDbo.update(this->_bid);
}