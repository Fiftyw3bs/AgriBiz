#include "FarmProduce.hpp"

using namespace demystify;
using namespace AgriBiz;
using namespace personal;


FarmProduce::FarmProduce() : _name{"Null"}
{

}
FarmProduce::FarmProduce(const std::string& name) : _name{name}
{

}
void FarmProduce::name(const std::string& name)
{
    this->_name = name;
}

void FarmProduce::description(const std::string& description )
{
    this->_description = description;
}
const std::string FarmProduce::name() const
{
    return this->_name;
}
const std::string FarmProduce::description() const
{
    return this->_description;
}