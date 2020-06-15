#ifndef EDIT_FarmProduce_HPP_
#define EDIT_FarmProduce_HPP_

#include "IAction.hpp"
#include "FarmProduce.hpp"
#include "FarmProduceCRUD.hpp"

namespace demystify
{
namespace AgriBiz
{
namespace action {

using namespace persistence;

class EditFarmProduce : public IAction
{
private:
    FarmProduce _farmProduce;
    PGPoolPtr _pgPool;
public:
    EditFarmProduce(const FarmProduce& farmProduce, PGPoolPtr pgPool);
    bool perform();
    ~EditFarmProduce();
};

} // action

} // namespace AgriBiz

} // namespace demystify


#endif //EDIT_FarmProduce_HPP_
