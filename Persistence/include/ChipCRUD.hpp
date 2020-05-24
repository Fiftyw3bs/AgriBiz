/**
******************************************************************************
* @file	persistences\AntiGhostWorker\include\ChipCRUD.hpp
* @author 	Fiftywebs
* @version
* @date 27.02.2020
* @brief
******************************************************************************
*/

#ifndef CHIP_CRUD_HPP_
#define CHIP_CRUD_HPP_

#include "Chip.hpp"
#include "User.hpp"
#include "GenericCRUD.hpp"

namespace demystify
{
    
namespace subsystem
{

namespace AntiGhostWorker 
{
   
using namespace personal;
using ChipToken = uint32_t;
using ChipID = uint32_t;
using FetchLimit = uint32_t;

class ChipCRUD : public GenericCRUD
{
private:
    static DBStatements crudStatements;
    static VectorOf<Chip> processFetched(const result& res);

public:
    ChipCRUD(PGPoolPtr& pgPool);
    ChipID add(const Chip& chip);
    bool remove(const Chip& chipId);
    bool update(const Chip& chip);
    Chip fetchOne(const UserID& userId);
    VectorOf<Chip> fetchAll(const FetchLimit& limit);    
    
    bool assign(const UserID& userId, const ChipID& chipId);
    bool revoke(const UserID& userId, const ChipID& chipId);
};
 
} // AntiGhostWorker

} // persistence
    
} // namespace demystify

#endif // !CHIP_CRUD_HPP_
