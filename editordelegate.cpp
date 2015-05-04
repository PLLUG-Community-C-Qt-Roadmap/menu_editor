#include "editordelegate.h"
#include "ui_editordelegate.h"

#include "menu.h"
#include "menuitem.h"
#include "discountmenuitem.h"

EditorDelegate::EditorDelegate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditorDelegate)
{
    ui->setupUi(this);
    ui->discountLabel->setVisible(false);
    ui->DiscountSpinBox->setVisible(false);

    connect(ui->menuItemNameLineEdit, SIGNAL(textChanged(QString)), this, SIGNAL(itemChanged()), Qt::UniqueConnection);
    connect(ui->menuItemDescriptionLineEdit, SIGNAL(textChanged(QString)), this, SIGNAL(itemChanged()), Qt::UniqueConnection);
    connect(ui->menuItemPriceSpinBox, SIGNAL(valueChanged(double)), this, SIGNAL(itemChanged()), Qt::UniqueConnection);

    connect(ui->DiscountSpinBox, SIGNAL(valueChanged(double)), this, SIGNAL(itemChanged()), Qt::UniqueConnection);
    connect(ui->discountCheckBox, SIGNAL(stateChanged(int)), this, SIGNAL(itemChanged()), Qt::UniqueConnection);
    connect(ui->discountCheckBox, SIGNAL(stateChanged(int)), this, SLOT(slotDiscountCheckboxStateChanged(int)), Qt::UniqueConnection);
}

EditorDelegate::~EditorDelegate()
{
    delete ui;
}

void EditorDelegate::visit(MenuItem *item)
{
    blockSignals(true);

    clear();

    ui->stackedWidget->setCurrentWidget(ui->pageMenuItem);
    ui->menuItemNameLineEdit->setText(item->title().c_str());
    ui->menuItemDescriptionLineEdit->setText(item->description().c_str());
    ui->menuItemPriceSpinBox->setValue(item->price());

    mEditedMenuItem = item;

    blockSignals(false);
}

void EditorDelegate::visit(Menu *menu)
{
    blockSignals(true);

    clear();

    ui->stackedWidget->setCurrentWidget(ui->pageMenu);

    mEditedMenu = menu;

    blockSignals(false);
}

void EditorDelegate::visit(DiscountMenuItem * discountItem)
{
    blockSignals(true);

    clear();
    ui->discountCheckBox->setChecked(true);

    ui->stackedWidget->setCurrentWidget(ui->pageMenuItem);
    ui->menuItemNameLineEdit->setText(discountItem->title().c_str());
    ui->menuItemDescriptionLineEdit->setText(discountItem->description().c_str());
    ui->menuItemPriceSpinBox->setValue(discountItem->price());
    ui->DiscountSpinBox->setValue(discountItem->discount());

    mEditedMenuItem = discountItem;

    blockSignals(false);
}

void EditorDelegate::clear()
{
    mEditedMenu = nullptr;
    mEditedMenuItem = nullptr;

    ui->discountCheckBox->setChecked(false);
    ui->DiscountSpinBox->setValue(0);
}

void EditorDelegate::slotSave()
{
    if (mEditedMenuItem)
    {

        mEditedMenuItem->setTitle(ui->menuItemNameLineEdit->text().toStdString());
        mEditedMenuItem->setDescription(ui->menuItemDescriptionLineEdit->text().toStdString());
        mEditedMenuItem->setPrice(ui->menuItemPriceSpinBox->value());

        if(mEditedMenuItem->type() == "DiscountMenuItem")
        {
            if(ui->discountCheckBox->isChecked())
            {
                (dynamic_cast<DiscountMenuItem*>(mEditedMenuItem))->setDiscount(ui->DiscountSpinBox->value());
            }
            else
            {
                //Change pointer on DiscountMenuItem to pointer on new MenuItem

            }

        }
        else if(mEditedMenuItem->type() == "MenuItem")
        {
            if(ui->discountCheckBox->isChecked())
            {
                //Change pointer on MenuItem to pointer on new DiscountMenuItem

//                mEditedMenuItem = new DiscountMenuItem(mEditedMenuItem->title(),
//                                                       mEditedMenuItem->price(),
//                                                       ui->DiscountSpinBox->value(),

            }
        }

    }
}

void EditorDelegate::slotDiscountCheckboxStateChanged(int state)
{
    if(state)
    {
        ui->discountLabel->setVisible(true);
        ui->DiscountSpinBox->setVisible(true);
    }
    else
    {
        ui->discountLabel->setVisible(false);
        ui->DiscountSpinBox->setVisible(false);
    }
}
