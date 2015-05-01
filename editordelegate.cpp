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

void EditorDelegate::visit(MenuItem *)
{
    ui->stackedWidget->setCurrentWidget(ui->pageMenuItem);
}

void EditorDelegate::visit(Menu *)
{
    ui->stackedWidget->setCurrentWidget(ui->pageMenu);
}
