#ifndef ADD_BID_HPP_
#define ADD_BID_HPP_

#include "IAction.hpp"
#include "Bid.hpp"
#include "BidCRUD.hpp"

namespace demystify
{
namespace AgriBiz
{
namespace action {

using namespace persistence;

class AddBid : public IAction
{
private:
    Bid _bid;
    PGPoolPtr _pgPool;
    BidID _bidId;
public:
    AddBid(const Bid& bid, PGPoolPtr pgPool);
    bool perform();
    BidID result();
    ~AddBid();
};

} // action

} // namespace AgriBiz

} // namespace demystify


#endif //ADD_BID_HPP_
