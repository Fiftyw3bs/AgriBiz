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
#include "MongoPark.hpp"
#include "AgriBiz_JsonConversion.hpp"

namespace demystify
{
    
namespace AgriBiz 
{

namespace persistence
{

using namespace persistence;
    
using FarmProduceCRUD = GenericCRUD<FarmProduce, JsonConversion::FarmProduceAsJSON, JsonConversion::FarmProduceFromJSON>;

} // namespace persistence


} // AntiGhostWorker
} // namespace demystify

#endif // !FARMPRODUCE_CRUD_HPP_
