#ifndef GET_FARMPRODUCE_HPP_
#define GET_FARMPRODUCE_HPP_

#include "IAction.hpp"
#include "FarmProduce.hpp"
#include "FarmProduceCRUD.hpp"

namespace demystify
{
namespace AgriBiz
{
namespace action {

using namespace persistence;

class GetFarmProduce : public IAction
{
private:
    FarmProduce _farmProduce;
    PGPoolPtr _pgPool;
public:
    GetFarmProduce(const FarmProduce& farmProduce, PGPoolPtr pgPool);
    bool perform();
    FarmProduce result();
    ~GetFarmProduce();
};

} // action

} // namespace AgriBiz

} // namespace demystify


#endif //GET_FARMPRODUCE_HPP_
