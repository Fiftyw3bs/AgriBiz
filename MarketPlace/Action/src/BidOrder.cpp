#include "BidOrder.hpp"

using namespace demystify;
using namespace AgriBiz;
using namespace action;

BidOrder::BidOrder(const Bid& bid, Order& order) : _bid{bid}, _order{order}
{
}
bool BidOrder::perform()
{

}