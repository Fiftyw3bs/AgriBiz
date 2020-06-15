#include "AddFarmProduce.hpp"

using namespace demystify;
using namespace AgriBiz;
using namespace action;

AddFarmProduce::AddFarmProduce(const FarmProduce& FarmProduce, PGPoolPtr pgPool) : _FarmProduce{FarmProduce}, _pgPool{pgPool}
{
}

bool AddFarmProduce::perform()
{
    auto FarmProduceDbo = FarmProduceCRUD(this->_pgPool);
    this->_farmProduceId = FarmProduceDbo.add(this->_FarmProduce);
    return this->_farmProduceId != 0;
}

FarmProduceID AddFarmProduce::result()
{
    return this->_farmProduceId;
}