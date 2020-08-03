#include "DeleteFarmProduce.hpp"

using namespace demystify;
using namespace AgriBiz;
using namespace action;

DeleteFarmProduce::DeleteFarmProduce(const FarmProduce& FarmProduce, PGPoolPtr pgPool) : _farmProduce{FarmProduce}, _pgPool{pgPool}
{
}

bool DeleteFarmProduce::perform()
{
    auto FarmProduceDbo = FarmProduceCRUD(this->_pgPool);
    return FarmProduceDbo.remove(this->_farmProduce);
}