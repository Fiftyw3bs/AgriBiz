#ifndef DELETE_BID_HPP_
#define DELETE_BID_HPP_

#include "IAction.hpp"
#include "Bid.hpp"
#include "BidCRUD.hpp"

namespace demystify
{
namespace AgriBiz
{

namespace action {

using namespace persistence;

class DeleteBid : public IAction
{
private:
    Bid _bid;
    PGPoolPtr _pgPool;
public:
    DeleteBid(const Bid& bid, PGPoolPtr pgPool);
    bool perform();
    ~DeleteBid();
};

} // action

} // namespace AgriBiz

} // namespace demystify


#endif //DELETE_BID_HPP_
