#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <vector>
#include "Employee.h"
#include "Product.h"


class WarehouseItem {
private:
    Product* product;
    int quantity;
};

class Warehouse {
private:
    int number;
    Employee* storekeeper;
    vector<WarehouseItem> products;
    int addres;
};

#endif
