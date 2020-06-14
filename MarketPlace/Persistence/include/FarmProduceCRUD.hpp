/**
******************************************************************************
* @file	persistences\AntiGhostWorker\include\FarmProduceCRUD.hpp
* @author 	Fiftywebs
* @version
* @date 27.02.2020
* @brief
******************************************************************************
*/

#ifndef FARMPRODUCE_CRUD_HPP_
#define FARMPRODUCE_CRUD_HPP_

#include "FarmProduce.hpp"
#include "GenericCRUD.hpp"

namespace demystify
{
    
namespace AgriBiz 
{

namespace persistence
{
    
using namespace personal;
using FarmProduceID = uint32_t;
using Offset = uint32_t;
using Limit = uint32_t;

class FarmProduceCRUD : public GenericCRUD
{
private:
    static DBStatements crudStatements;
    static VectorOf<FarmProduce> processFetched(const result res);
    
public:
    FarmProduceCRUD(PGPoolPtr& pgPool);
    UserID add(const FarmProduce& farmProduce);
    bool remove(const FarmProduce& farmProduce);
    bool update(const FarmProduce& farmProduce);
    FarmProduce fetch(const FarmProduce& farmProduce);
    VectorOf<FarmProduce> fetch(const Offset& offset, const Limit& limit);
};

} // namespace persistence


} // AntiGhostWorker
} // namespace demystify

#endif // !FARMPRODUCE_CRUD_HPP_
