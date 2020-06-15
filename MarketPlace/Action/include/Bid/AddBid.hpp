#ifndef ADD_BID_HPP_
#define ADD_BID_HPP_

#include "IAction.hpp"
#include "Bid.hpp"
#include "PGPool.hpp"

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
public:
    AddBid(const Bid& bid, PGPoolPtr pgPool);
    bool perform();
    ~AddBid();
};

} // action

} // namespace AgriBiz

} // namespace demystify


#endif //ADD_BID_HPP_
