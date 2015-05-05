#include "discountmenuitem.h"
#include "menuvisitor.h"

DiscountMenuItem::DiscountMenuItem(const std::string &pTitle, double pPrice, double pDiscont, std::string pDescription)
    : MenuItem(pTitle, pPrice, pDescription),
      mDiscount(pDiscont)
{
    setType("DiscountMenuItem");
}

double DiscountMenuItem::discount() const
{
    return mDiscount;
}

void DiscountMenuItem::setDiscount(double discount)
{
    mDiscount = discount;
}

void DiscountMenuItem::accept(MenuVisitor *visitor)
{
    visitor->visit(this);
}
