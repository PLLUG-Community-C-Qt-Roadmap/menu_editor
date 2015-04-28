#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "texteditprintmenuvisitor.h"
#include "menuiterator.h"
#include "menu.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mRoot{nullptr}
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotPrintMenu()
{
    TextEditPrintMenuVisitor visitor (ui->plainTextEdit);
    MenuIterator iterator(mRoot);
    while(iterator.hasNext())
    {
        auto item =  iterator.next();
        item->accept(&visitor);
    }
}
