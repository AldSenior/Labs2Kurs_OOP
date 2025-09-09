#ifndef ORDERLINE_H
#define ORDERLINE_H

#include "Product.h"

class OrderLine {
private:
    int quanity;
    double priceWithTaxes;
    double amount;
    Product* product;
};

#endif
