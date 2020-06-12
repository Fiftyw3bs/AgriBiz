#include "Order.hpp"

#include <type_traits>

using namespace demystify;
using namespace AgriBiz;
using namespace demystify::personal;


Order::Order() 
    : _farmProduce{FarmProduce("Null")}, _costPerKg{0}, _orderer{User()}, _location{Location(0, 0)}
{
}
Order::Order(const FarmProduce& farmProduce, const float& costPerKg, const User& orderer, const Location& location) 
    : _farmProduce{farmProduce}, _costPerKg{costPerKg}, _orderer{orderer}, _location{location}
{
}
void Order::cost(const float& cost)
{
    this->_cost = cost;
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
void Order::harvestDate(const Datable& harvestDate)
{
    this->_harvestDate = harvestDate;
}
void Order::completionDate(const Datable& completionDate)
{
    this->_dateComplete = completionDate;
}
const float Order::cost() const
{
    return this->_cost;
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
const User& orderer Order::orderer() const
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
const float Order::getTotalCost(const float& quantity, const float& costPerKg) const
{
    return quantity * costPerKg;
}