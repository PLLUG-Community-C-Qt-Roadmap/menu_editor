#ifndef DISCOUNTMENUITEM_H
#define DISCOUNTMENUITEM_H

#include "menuitem.h"


class DiscountMenuItem : public MenuItem
{
public:
    DiscountMenuItem(const std::string &pTitle, double pPrice = 0.0, double pDiscont = 0.0
            ,std::string pDescription = std::string());

    double discount() const;
    void setDiscount(double discount);

    void accept(MenuVisitor *visitor);

private:
    double mDiscount;
};

#endif // DISCOUNTMENUITEM_H
