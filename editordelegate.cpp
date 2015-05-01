#include "editordelegate.h"
#include "ui_editordelegate.h"

#include "menu.h"
#include "menuitem.h"

EditorDelegate::EditorDelegate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditorDelegate)
{
    ui->setupUi(this);
    connect(ui->menuItemNameLineEdit, SIGNAL(textChanged(QString)), this, SLOT(slotEdited()), Qt::UniqueConnection);
    connect(ui->menuItemDescriptionLineEdit, SIGNAL(textChanged(QString)), this, SLOT(slotEdited()), Qt::UniqueConnection);
    connect(ui->menuItemPriceSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slotEdited()), Qt::UniqueConnection);
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(slotSave()), Qt::UniqueConnection);
    ui->pushButton->setEnabled(false);
}

EditorDelegate::~EditorDelegate()
{
    delete ui;
}

void EditorDelegate::visit(MenuItem *item)
{
    clear();

    ui->stackedWidget->setCurrentWidget(ui->pageMenuItem);
    ui->menuItemNameLineEdit->setText(item->title().c_str());
    ui->menuItemDescriptionLineEdit->setText(item->description().c_str());
    ui->menuItemPriceSpinBox->setValue(item->price());

    mEditedMenuItem = item;
}

void EditorDelegate::visit(Menu *menu)
{
    clear();

    ui->stackedWidget->setCurrentWidget(ui->pageMenu);

    mEditedMenu = menu;
}

void EditorDelegate::clear()
{
    mEditedMenu = nullptr;
    mEditedMenuItem = nullptr;
    ui->pushButton->setEnabled(false);
}

void EditorDelegate::slotSave()
{
    if (mEditedMenuItem)
    {
        mEditedMenuItem->setTitle(ui->menuItemNameLineEdit->text().toStdString());
        mEditedMenuItem->setDescription(ui->menuItemDescriptionLineEdit->text().toStdString());
        mEditedMenuItem->setPrice(ui->menuItemPriceSpinBox->value());
        ui->pushButton->setEnabled(false);
        emit itemChanged();
    }
}

void EditorDelegate::slotEdited()
{
    ui->pushButton->setEnabled(true);
}
