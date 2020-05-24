/**
******************************************************************************
* @file	persistences\AntiGhostWorker\include\StampCRUD.hpp
* @author 	Fiftywebs
* @version
* @date 27.02.2020
* @brief
******************************************************************************
*/

#ifndef STAMP_CRUD_HPP_
#define STAMP_CRUD_HPP_

#include "AGW_Model.hpp"
#include "GenericCRUD.hpp"

namespace demystify
{
    
namespace subsystem
{

namespace AntiGhostWorker 
{
 
using namespace personal;
using StampID = uint32_t;

class StampCRUD : public GenericCRUD
{
private:
    static DBStatements crudStatements;
    static VectorOf<Stamp> processFetched(const result res);
    
public:
    StampCRUD(PGPoolPtr& pgPool);
    UserID add(const Stamp& stamp);
    bool remove(const StampID& stampId);
    bool update(const Stamp& stamp);
    bool removeAllByChip(const Chip& chip);
    VectorOf<Stamp> fetchByChip(const Chip& chip);
    Stamp fetchOne(const StampID& chip);
    VectorOf<Stamp> fetchByStampTime(const Chip& chip, const Datable& startDate, const Datable& endDate);
    VectorOf<Stamp> fetchAllByStampTime(const Datable& startDate, const Datable& endDate);


};

} // AntiGhostWorker
} // subsystem
    
} // namespace demystify

#endif // !STAMP_CRUD_HPP_
