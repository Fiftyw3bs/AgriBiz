/**
******************************************************************************
* @file	persistences\AntiGhostWorker\include\BidCRUD.hpp
* @author 	Fiftywebs
* @version
* @date 27.02.2020
* @brief
******************************************************************************
*/

#ifndef BID_CRUD_HPP_
#define BID_CRUD_HPP_

#include "Bid.hpp"
#include "User.hpp"
#include "GenericCRUD.hpp"

namespace demystify
{
    
namespace AgriBiz
{

namespace persistence 
{
   
using namespace personal;
using BidID = uint32_t;
using Limit = uint32_t;
using Offset = uint32_t;

class BidCRUD : public GenericCRUD
{
private:
    static DBStatements crudStatements;
    static VectorOf<Bid> processFetched(const result res);
  
public:
    BidCRUD(PGPoolPtr& pgPool);
    BidID add(const Bid& Bid);
    bool remove(const Bid& user);
    bool update(const Bid& user);
    Bid fetch(const Bid& bid);    
};
 
} // AntiGhostWorker

} // persistence
    
} // namespace demystify

#endif // !BID_CRUD_HPP_
