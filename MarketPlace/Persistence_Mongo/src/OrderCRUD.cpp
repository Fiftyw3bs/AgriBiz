#include "OrderCRUD.hpp"

using namespace demystify;
using namespace AgriBiz;
using namespace AgriBiz::persistence;

OrderCRUD::OrderCRUD(mongocxx::client& client_, const MongoDBInfo dbInfo) : GenericCRUD{client_, dbInfo}
{
}

// VectorOf<Order> OrderCRUD::fetch(const Datable& startDate, const Datable& endDate, const Offset& offset, const Limit& limit)
// {

// }
// VectorOf<Order> OrderCRUD::fetch(const User& orderer, const Offset& offset, const Limit& limit)
// {
    
// }
// VectorOf<Order> OrderCRUD::fetch(const std::string& status, const Offset& offset, const Limit& limit)
// {
    
// }
