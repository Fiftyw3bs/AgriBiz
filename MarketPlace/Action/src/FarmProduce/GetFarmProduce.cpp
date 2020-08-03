#include "GetFarmProduce.hpp"

using namespace demystify;
using namespace AgriBiz;
using namespace action;

GetFarmProduce::GetFarmProduce(const FarmProduce& FarmProduce, PGPoolPtr pgPool) : _farmProduce{FarmProduce}, _pgPool{pgPool}
{
}

bool GetFarmProduce::perform()
{
    auto FarmProduceDbo = FarmProduceCRUD(this->_pgPool);
    this->_farmProduce = FarmProduceDbo.fetch(this->_farmProduce);
    return this->_farmProduce.getId() != 0;
}

FarmProduce GetFarmProduce::result()
{
    return this->_farmProduce;
}