#ifndef ORDER_HPP_
#define ORDER_HPP_

#include "Models.hpp"
#include "Bid.hpp"
#include "FarmProduce.hpp"
#include "MarketPlace.hpp"

#include <string>

namespace demystify
{
namespace AgriBiz
{

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

class Order : public Identifiable, public Datable, private Subscribable<Bid>
{
private:
    FarmProduce _farmProduce;
    const User& _orderer;
    float _costPerKg;
    float _quantity; // In Kg
    personal::Location _location;
    Datable _harvestDate;
    std::string _description;
    Datable _dateComplete;
    OrderType _orderType;
    OrderStatus _status;

    OrderStatus status() const;
    OrderStatus status(const OrderStatus& status);
    const float totalCost(const float& quantity, const float& costPerKg) const;
 
    friend class MarketPlace; // Needed to use addSubscriber()

public:
    Order();
    Order(OrderType orderType, const FarmProduce& farmProduce, const float& costPerKg, const User& orderer, const Location& location);

    void costPerKg(const float& cost);
    void harvestDate(const Datable& harvestDate);
    void location(const Location& location);
    void description(const std::string& descr );
    void completionDate(const Datable& completionDate);

    const float costPerKg() const;
    const Datable harvestDate() const;
    const std::string description() const;
    const Location& location() const;
    const Datable completionDate() const;
    const User& orderer() const;
    const FarmProduce& farmProduce() const;
    const float quantity() const;
    OrderType orderType() const;
};

} // namespace AgriBiz

} // namespace demystify

#endif //ORDER_HPP_
