#ifndef ADD_FARMPRODUCE_HPP_
#define ADD_FARMPRODUCE_HPP_

#include "IAction.hpp"
#include "FarmProduce.hpp"
#include "FarmProduceCRUD.hpp"

namespace demystify
{
namespace AgriBiz
{
namespace action {

using namespace persistence;

class AddFarmProduce : public IAction
{
private:
    FarmProduce _FarmProduce;
    FarmProduceID _farmProduceId;
    PGPoolPtr _pgPool;
public:
    AddFarmProduce(const FarmProduce& FarmProduce, PGPoolPtr pgPool);
    bool perform();
    FarmProduceID result();
    ~AddFarmProduce();
};

} // action

} // namespace AgriBiz

} // namespace demystify


#endif //ADD_FARMPRODUCE_HPP_
