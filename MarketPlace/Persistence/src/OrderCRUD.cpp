#include "OrderCRUD.hpp"

using namespace demystify;
using namespace AgriBiz;
using namespace AgriBiz::persistence;

OrderCRUD::OrderCRUD(PGPoolPtr& pgPool) : 
    GenericCRUD(OrderCRUD::crudStatements, pgPool)
{
}

OrderID OrderCRUD::add(const Order& order)
{
    OrderID orderId = 0;

    auto mm = this->performDBOperation(
        "Order_CREATE",
        order.orderer().getId(),
        order.costPerKg(),
        order.quantity(),
        order.location().getId(),
        order.harvestDate().getTimeString(),
        order.getTimeString(), // Date of order
        order.description(),
        order.completionDate().getTimeString(),
        order.type(StringOutput()),
        order.status(StringOutput())
    );
    
    if (!mm[0]["order_id"].is_null())
    {
        orderId = mm[0]["order_id"].as<OrderID>();
    }

    return orderId;
}

bool OrderCRUD::remove(const Order& order)
{
    return this->performDBOperation(
        "Order_REMOVE_ONE_BY_ID",
        order.getId()
    ).empty();
}

bool OrderCRUD::update(const Order& order)
{
    return this->performDBOperation(
        "Order_MODIFY",
        order.costPerKg(),
        order.quantity(),
        order.location().getId(),
        order.harvestDate().getTimeString(),
        order.description(),
        order.completionDate().getTimeString(),
        order.type(StringOutput()),
        order.status(StringOutput()),
        order.getTimeString(), // Date of order
        order.getId()
    ).empty();    
}
VectorOf<Order> OrderCRUD::fetch(const Datable& startDate, const Datable& endDate, const Offset& offset, const Limit& limit)
{
    auto retVal = this->performDBOperation("ORDER_FETCH_ALL_BY_DATE", startDate.getTimeString(), endDate.getTimeString(), offset, limit);

    return this->processFetched(retVal);

}
VectorOf<Order> OrderCRUD::fetch(const User& orderer, const Offset& offset, const Limit& limit)
{
    auto retVal = this->performDBOperation("ORDER_FETCH_ALL_BY_ORDERER", orderer.getId(), offset, limit);
    return this->processFetched(retVal);
}
VectorOf<Order> OrderCRUD::fetch(const std::string& status, const Offset& offset, const Limit& limit)
{
    auto retVal = this->performDBOperation("ORDER_FETCH_ALL_BY_STATUS", status, offset, limit);
    return this->processFetched(retVal);
}
VectorOf<Order> OrderCRUD::processFetched(const result& res)
{

    VectorOf<Order> tmpOrders;
    Order tmpOrder;

    if (!res.empty() && res.size() > 0)
    {
        for (auto row : res)
        {
            tmpOrder.setId(row["order_id"].as<OrderID>());

            User tUser;
            tUser.setId(row["orderer_id"].as<UserID>());
            tmpOrder.orderer(tUser);

            tmpOrder.costPerKg(row["cost_per_kg"].as<float>());
            tmpOrder.quantity(row["quantity"].as<float>());

            Location tLocation;
            tLocation.setId(row["location_id"].as<uint32_t>());
            tmpOrder.location(tLocation);

            Datable hDate;
            hDate.setDate(row["harvest_date"].as<std::string>());
            tmpOrder.harvestDate(hDate);

            Datable pDate;
            pDate.setDate(row["date_posted"].as<std::string>());
            tmpOrder.harvestDate(pDate);

            tmpOrder.description(row["description"].as<std::string>());

            Datable cDate;
            cDate.setDate(row["date_complete"].as<std::string>());
            tmpOrder.harvestDate(cDate);

            tmpOrder.type(row["order_type"].as<std::string>());
            tmpOrder.status(row["order_status"].as<std::string>());

            tmpOrders.push_back(tmpOrder);
        }
    }
    else
    {
        tmpOrders.push_back(tmpOrder);
    }
    

    return tmpOrders;
}

bool OrderCRUD::assignBid(const Bid& bid, const Order& order)
{
    return this->performDBOperation(
        "Order_ASSIGN_BID",
        bid.getId(),
        order.getId()
    ).empty();
}

Order OrderCRUD::fetch(const Order& order)
{
    auto retVal = this->performDBOperation("ORDER_FETCH_ALL_BY_ORDER_ID", order.getId(), 0, 1);
    return this->processFetched(retVal)[0];
}

DBStatements OrderCRUD::crudStatements{
    {"ORDER_FETCH_ALL_BY_ORDERER", 
        "SELECT \
            order_id, \
            orderer_id, \
            cost_per_kg, \
            quantity, \
            location_id, \
            harvest_date, \
            date_posted, \
            description, \
            date_complete, \
            order_type::text, \
            order_status::text \
         FROM Orders \
         WHERE orderer_id=$1\
         ORDER BY date_posted DESC \
         OFFSET $2 ROWS \
         FETCH NEXT $3 ROWS ONLY"
    },
    {"ORDER_FETCH_ALL_BY_DATE", 
        "SELECT \
            order_id, \
            orderer_id, \
            cost_per_kg, \
            quantity, \
            location_id, \
            harvest_date, \
            date_posted, \
            description, \
            date_complete, \
            order_type::text, \
            order_status::text \
         FROM Orders \
         WHERE date_posted BETWEEN $1 AND $2 \
         ORDER BY date_posted DESC \
         OFFSET $3 ROWS \
         FETCH NEXT $4 ROWS ONLY"
    },
    {"ORDER_FETCH_ALL_BY_STATUS", 
        "SELECT \
            order_id, \
            orderer_id, \
            cost_per_kg, \
            quantity, \
            location_id, \
            harvest_date, \
            date_posted, \
            description, \
            date_complete, \
            order_type::text, \
            order_status::text \
         FROM Orders \
         WHERE order_status=$1\
         ORDER BY date_posted DESC \
         OFFSET $2 ROWS \
         FETCH NEXT $3 ROWS ONLY"
    },
    {"ORDER_FETCH_ALL_BY_ORDER_ID", 
        "SELECT \
            order_id, \
            orderer_id, \
            cost_per_kg, \
            quantity, \
            location_id, \
            harvest_date, \
            date_posted, \
            description, \
            date_complete, \
            order_type::text, \
            order_status::text \
         FROM Orders \
         WHERE order_id=$1\
         ORDER BY date_posted DESC \
         OFFSET $2 ROWS \
         FETCH NEXT $3 ROWS ONLY"
    },
    {"Order_CREATE", "INSERT INTO Orders (order_id, orderer_id, cost_per_kg, quantity, location_id, harvest_date, date_posted, description, date_complete, order_type, order_status) VALUES (DEFAULT, $1, $2, $3, $4, $5, $6, $7, $8, $9, $10) RETURNING order_id"},
    {"Order_REMOVE_ONE_BY_ID", "DELETE FROM Orders WHERE order_id = $1"},
    {"Order_ASSIGN_BID", "INSERT INTO Bid_Order (bid_id, order_id) VALUES ($1, $2)"},
    {"Order_MODIFY", "UPDATE Orders SET cost_per_kg=$1, quantity=$2, location_id=$3, harvest_date=$4, description=$5, date_complete=$6, order_type=$7, order_status=$8, date_posted=$9 WHERE order_id=$10"}
};