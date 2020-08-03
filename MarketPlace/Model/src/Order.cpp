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
OrderType Order::type() const
{
    return this->_orderType;
}
OrderStatus Order::status() const
{
    return this->_status;
}
void Order::status(const OrderStatus& status)
{
    this->_status = status;
}
void Order::orderer(const User& orderer)
{
    this->_orderer = orderer;
}
void Order::farmProduce(const FarmProduce& farmProduce)
{
    this->_farmProduce = farmProduce;
}
void Order::quantity(const float& quantity)
{
    this->_quantity = quantity;
}
void Order::type(const OrderType& type)
{
    this->_orderType = type;
}
const User& Order::orderer()
{
    return this->_orderer;
}
std::string Order::status(StringOutput) const
{
    switch (this->_status)
    {
    case OrderStatus::PENDING:
        return "PENDING";
        break;
    case OrderStatus::ACCEPTED:
        return "ACCEPTED";
        break;
    case OrderStatus::COMPLETED:
        return "COMPLETED";
        break;
    case OrderStatus::SUSPENDED:
        return "SUSPENDED";
        break;
    default:
        return "UNKNOWN";
    }
}
std::string Order::type(StringOutput) const
{
    switch (this->_orderType)
    {
    case OrderType::BUY:
        return "BUY";
        break;
    case OrderType::SELL:
        return "SELL";
        break;
    }
}
void Order::type(const std::string& type)
{
    if (type == "BUY")
    {
        this->_orderType = OrderType::BUY;
    } 
    else if (type == "SELL")
    {
        this->_orderType = OrderType::SELL;
    }
}
void Order::status(const std::string& status)
{
    if (status == "ACCEPTED")
    {
        this->_status = OrderStatus::ACCEPTED;
    } 
    else if (status == "COMPLETED")
    {
        this->_status = OrderStatus::COMPLETED;
    }
    else if (status == "PENDING")
    {
        this->_status = OrderStatus::PENDING;
    }
    else if (status == "SUSPENDED")
    {
        this->_status = OrderStatus::SUSPENDED;
    }
    else
    {
        this->_status = OrderStatus::UNKNOWN;
    }
}