#ifndef EDIT_BID_HPP_
#define EDIT_BID_HPP_

#include "IAction.hpp"
#include "Bid.hpp"
#include "BidCRUD.hpp"

namespace demystify
{
namespace AgriBiz
{
namespace action {

using namespace persistence;

class EditBid : public IAction
{
private:
    Bid _bid;
    PGPoolPtr _pgPool;
public:
    EditBid(const Bid& bid, PGPoolPtr pgPool);
    bool perform();
    ~EditBid();
};

} // action

} // namespace AgriBiz

} // namespace demystify


#endif //EDIT_BID_HPP_
