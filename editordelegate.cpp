#include "editordelegate.h"
#include "ui_editordelegate.h"

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
