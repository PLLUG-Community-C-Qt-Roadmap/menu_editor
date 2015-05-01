#include "editordelegate.h"
#include "ui_editordelegate.h"

#include "menu.h"
#include "menuitem.h"

EditorDelegate::EditorDelegate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditorDelegate)
{
    ui->setupUi(this);
}

EditorDelegate::~EditorDelegate()
{
    delete ui;
}

void EditorDelegate::visit(MenuItem *item)
{
    ui->stackedWidget->setCurrentWidget(ui->pageMenuItem);
    ui->menuItemNameLineEdit->setText(item->title().c_str());
    ui->menuItemDescriptionLineEdit->setText(item->description().c_str());
    ui->menuItemPriceSpinBox->setValue(item->price());

    clear();
    mEditedMenuItem = item;
}

void EditorDelegate::visit(Menu *menu)
{
    ui->stackedWidget->setCurrentWidget(ui->pageMenu);


    clear();
    mEditedMenu = menu;
}

void EditorDelegate::clear()
{
    mEditedMenu = nullptr;
    mEditedMenuItem = nullptr;
}

void EditorDelegate::slotMenuItemTitleChanged(const QString &title)
{
    mEditedMenuItem->setTitle(title.toStdString());
}

void EditorDelegate::slotMenuItemDescriptionChanged(const QString &description)
{
    mEditedMenuItem->setDescription(description.toStdString());
}

void EditorDelegate::slotMenuItemPriceCahnged(double price)
{
    mEditedMenuItem->setPrice(price);
}
