#ifndef GET_BID_HPP_
#define GET_BID_HPP_

#include "IAction.hpp"
#include "Bid.hpp"
#include "BidCRUD.hpp"

namespace demystify
{
namespace AgriBiz
{
namespace action {

using namespace persistence;

class GetBid : public IAction
{
private:
    Bid _bid;
    PGPoolPtr _pgPool;
public:
    GetBid(const Bid& Bid, PGPoolPtr pgPool);
    bool perform();
    Bid result();
    ~GetBid();
};

} // action

} // namespace AgriBiz

} // namespace demystify


#endif //GET_BID_HPP_
