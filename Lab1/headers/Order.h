#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include "Document.h"
#include "Enums.h"
#include "Employee.h"
#include "OrderLine.h"

class Invoice;

class Order : public Document {
private:
    OrderStatus status;
    Employee* manager;
    vector<OrderLine> orderLine;
    int dateOfShipment;
    int datePayment;
    int price;
    Invoice* derivedInvoice; // опережающее объявление чтоб ошибки небыло

    void cancel();
};

#endif
