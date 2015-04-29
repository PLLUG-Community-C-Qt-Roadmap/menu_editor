#include "menucombobox.h"

#include "composite.h"
#include "menuiterator.h"

MenuComboBox::MenuComboBox(QWidget *parent)
    : QComboBox(parent),
      mRoot{nullptr}
{
}

void MenuComboBox::setMenu(Composite *menu)
{
    mRoot = menu;
    clear();
    populateComboBox();
}

void MenuComboBox::populateComboBox()
{
    if (mRoot)
    {
        MenuIterator iterator(mRoot);
        while (iterator.hasNext())
        {
            Composite * item = iterator.next();
            addItem(item->title().c_str());
        }
    }
}

