#ifndef INVOICE_H
#define INVOICE_H

#include <vector>
#include <string>
#include "Document.h"
#include "Enums.h"
#include "Employee.h"
#include "InvoiceEntry.h"

// опережающее объявление вместо Order
class Order;

class Invoice : public Document {
private:
    InvoiceStatus status;
    Employee* ResponsiblePerson;
    int dateOfShipmentTime;
    int amount;
    int weigth;
    string notes;
    vector<InvoiceEntry> invoiceEntry;
    string fullNameRecipient;
    Order* order; // Используем опережающее объявление
};

#endif
