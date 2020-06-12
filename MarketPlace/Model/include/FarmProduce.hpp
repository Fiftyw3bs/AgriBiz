#ifndef FARM_PRODUCE_HPP_
#define FARM_PRODUCE_HPP_

#include "Models.hpp"

#include <string>

namespace demystify
{
namespace AgriBiz
{
using namespace personal;

class FarmProduce : public Identifiable, public Subscribable<User>
{
private:
    std::string _name;
    float _costPerKg; // Per Kg
    Datable _harvestDate;
    uint32_t _quantity = 1;
    std::string _description;

public:
    FarmProduce();
    FarmProduce(const std::string& name);
    
    void name(const std::string& name);
    void costPerKg(const float& cost);
    void harvestDate(const Datable& duration);
    void quantity(const uint32_t& quantity);
    void description(const std::string& descr );

    const std::string name() const;
    const uint32_t costPerKg() const;
    const Datable harvestDate() const;
    const std::string description() const;
    const float quantity() const;
};

} // namespace AgriBiz

} // namespace demystify

#endif // FARM_PRODUCEER_HPP_
