#ifndef DELETE_FarmProduce_HPP_
#define DELETE_FarmProduce_HPP_

#include "IAction.hpp"
#include "FarmProduce.hpp"
#include "FarmProduceCRUD.hpp"

namespace demystify
{
namespace AgriBiz
{

namespace action {

using namespace persistence;

class DeleteFarmProduce : public IAction
{
private:
    FarmProduce _farmProduce;
    PGPoolPtr _pgPool;
public:
    DeleteFarmProduce(const FarmProduce& FarmProduce, PGPoolPtr pgPool);
    bool perform();
    ~DeleteFarmProduce();
};

} // action

} // namespace AgriBiz

} // namespace demystify


#endif //DELETE_FarmProduce_HPP_
