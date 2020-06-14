#include "Order.hpp"

#include <type_traits>

using namespace demystify;
using namespace AgriBiz;
using namespace demystify::personal;


Order::Order() 
    : _farmProduce{FarmProduce("Null")}, _costPerKg{0}, _orderer{User()}, _location{Location(0, 0)}
{
}
Order::Order(OrderType orderType, const FarmProduce& farmProduce, const float& costPerKg, const User& orderer, const Location& location) 
    : _farmProduce{farmProduce}, _costPerKg{costPerKg}, _orderer{orderer}, _location{location}
{
}
void Order::costPerKg(const float& cost)
{
    this->_costPerKg = cost;
}
void Order::location(const Location& location)
{
    this->_location = location;
}
void Order::description(const std::string& descr )
{
    this->_description = descr;
}
void Order::harvestDate(const Datable& harvestDate )
{
    this->_harvestDate = harvestDate;
}
void Order::completionDate(const Datable& completionDate)
{
    this->_dateComplete = completionDate;
}
const float Order::costPerKg() const
{
    return this->_costPerKg;
}

const Datable Order::harvestDate() const
{
    return this->_harvestDate;
}

const std::string Order::description() const
{
    return this->_description;
}

const Location& Order::location() const
{
    return this->_location;
}
const Datable Order::completionDate() const
{
    return this->_dateComplete;
}
const User& Order::orderer() const
{
    return this->_orderer;
}
const FarmProduce& Order::farmProduce() const
{
    return this->_farmProduce;
}
const float Order::quantity() const
{
    return this->_quantity;
}
const float Order::totalCost(const float& quantity, const float& costPerKg) const
{
    return quantity * costPerKg;
}
OrderType Order::orderType() const
{
    return this->_orderType;
}
OrderStatus Order::status() const
{
    return this->_status;
}
OrderStatus Order::status(const OrderStatus& status)
{
    this->_status = status;
}