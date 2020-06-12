#include "Order.hpp"

#include <type_traits>

using namespace demystify;
using namespace ::ASUnity;
using namespace demystify::personal;


Order::Order() 
    : : _farmProduce{FarmProduce("Null")}, _costPerKg{0}, _orderer{User()}
{
}
Order::Order(const FarmProduce& farmProduce, const float& costPerKg, const User& orderer) 
    : _farmProduce{farmProduce}, _costPerKg{costPerKg}, _orderer{orderer}
{
}
void Order::name(const std::string& name)
{
    this->name = name;
}
void Order::cost(const float& cost)
{
    this->cost = cost;
}
void Order::location(const Location& location)
{
    this->location = location;
}
void Order::description(const std::string& descr )
{
    this->description = descr;
}
void Order::harvestDate(const Datable& harvestDate )
{
    this->harvestDate = harvestDate;
}
void Order::harvestDate(const Datable& harvestDate)
{
    this->_harvestDate = harvestDate;
}
void Order::completionDate(const Datable& completionDate)
{
    this->_dateComplete = completionDate;
}
const std::string Order::name() const
{
    return this->name;
}

const float Order::cost() const
{
    return this->cost;
}

const Datable Order::harvestDate() const
{
    return this->harvestDate;
}

const std::string Order::description() const
{
    return this->description;
}

const Location& Order::location() const
{
    return this->location;
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
    return this->farmProduce;
}
const float Order::quantity() const
{
    return this->_quantity;
}
const float Order::getTotalCost(const float& quantity, const float& costPerKg) const
{
    return quantity * costPerKg;
}