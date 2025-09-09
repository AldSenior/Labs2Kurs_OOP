#ifndef ENUMS_H
#define ENUMS_H

enum OrderStatus {
    NewOrder,
    Payed,
    Cancelled
};

enum InvoiceStatus {
    NewInvoice,
    Discharged,
    Suspended,
    Ready,
    Shipped
};

#endif
