#include "EditFarmProduce.hpp"

using namespace demystify;
using namespace AgriBiz;
using namespace action;

EditFarmProduce::EditFarmProduce(const FarmProduce& FarmProduce, PGPoolPtr pgPool) : _farmProduce{FarmProduce}, _pgPool{pgPool}
{
}

bool EditFarmProduce::perform()
{
    auto FarmProduceDbo = FarmProduceCRUD(this->_pgPool);
    return FarmProduceDbo.update(this->_farmProduce);
}