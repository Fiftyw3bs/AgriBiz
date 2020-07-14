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

bool OrderCRUD::assignBid(const Bid& bid, const Order& order)
{
    auto bidJson = JsonConversion::BidAsJSON(bid);
    auto val = document{} << "$addToSet" << open_document << "bids" << bidJson << close_document << finalize;
    return this->update_single(this->dbInfo, order.getId(), bsoncxx::to_json(val));
}
