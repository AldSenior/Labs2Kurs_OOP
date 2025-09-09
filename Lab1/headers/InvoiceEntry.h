#ifndef INVOICEENTRY_H
#define INVOICEENTRY_H

#include "Product.h"

class InvoiceEntry {
private:
    int quanity;
    int weidth;
    double price;
    double amount;
    Product* product;
};

#endif
