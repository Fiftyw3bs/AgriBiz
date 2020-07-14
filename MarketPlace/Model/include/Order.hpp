#ifndef ORDER_HPP_
#define ORDER_HPP_

#include "Models.hpp"
#include "Bid.hpp"
#include "FarmProduce.hpp"

#include <string>

namespace demystify
{
namespace AgriBiz
{

namespace persistence
{
    class OrderCRUD;
}

enum class OrderStatus
{
    ACCEPTED,
    PENDING,
    COMPLETED,
    SUSPENDED,
    UNKNOWN
};

enum class OrderType
{
    BUY,
    SELL
};

using namespace personal;

class Order : public Identifiable, public Datable, public Subscribable<Bid>
{
private:
    FarmProduce _farmProduce;
    User _orderer;
    float _costPerKg;
    float _quantity; // In Kg
    personal::Location _location;
    Datable _harvestDate;
    std::string _description;
    Datable _dateComplete;
    OrderType _orderType;
    OrderStatus _status;

    const float totalCost(const float& quantity, const float& costPerKg) const;


public:
    Order();
    Order(OrderType orderType, const FarmProduce& farmProduce, const float& costPerKg, const User& orderer, const Location& location);

    void status(const OrderStatus& status);
    void status(const std::string& status);
    void costPerKg(const float& cost);
    void harvestDate(const Datable& harvestDate);
    void location(const Location& location);
    void description(const std::string& descr );
    void completionDate(const Datable& completionDate);
    void orderer(const User& orderer);
    void farmProduce(const FarmProduce& farmProduce);
    void quantity(const float& quantity);
    void type(const OrderType& type);
    void type(const std::string& type);

    OrderStatus status() const;
    std::string status(StringOutput) const;
    const float costPerKg() const;
    const Datable harvestDate() const;
    const std::string description() const;
    const Location& location() const;
    const Datable completionDate() const;
    const User& orderer() const;
    const User& orderer();
    const FarmProduce& farmProduce() const;
    const float quantity() const;
    OrderType type() const;
    std::string type(StringOutput) const;
};

} // namespace AgriBiz

} // namespace demystify

#endif //ORDER_HPP_
