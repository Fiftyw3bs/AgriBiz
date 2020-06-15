#ifndef DELETE_BID_HPP_
#define DELETE_BID_HPP_

#include "IAction.hpp"
#include "Bid.hpp"
#include "PGPool.hpp"

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
public:
    DeleteBid(const Bid& bid);
    bool perform();
    ~DeleteBid();
};

} // action

} // namespace AgriBiz

} // namespace demystify


#endif //DELETE_BID_HPP_
