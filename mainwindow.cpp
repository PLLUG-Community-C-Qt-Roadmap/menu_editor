#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "texteditprintmenuvisitor.h"
#include "menuiterator.h"
#include "menu.h"
#include "menuitem.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mRoot{nullptr}
{
    ui->setupUi(this);

    createMenu();
    slotPrintMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mRoot;
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

void MainWindow::createMenu()
{
    mRoot = new Menu("MAIN MENU");

    Menu *lPizzaMenu = new Menu("Pizza Menu");
    lPizzaMenu->addSubitem(new MenuItem("hawaiian pizza", 2.4, "cheese and tomato base with toppings of ham and pineapple"));
    lPizzaMenu->addSubitem(new MenuItem("vegetarian pizza", 4.2, "cheese and tomato ... "));
    mRoot->addSubitem(lPizzaMenu);

    Menu *lBeveragesMenu = new Menu("Beverages");
    lBeveragesMenu->addSubitem(new MenuItem("Coca-Cola", 2));

    Menu *lCoffeMenu = new Menu("Coffe");
    lCoffeMenu->addSubitem(new MenuItem("Late", 1, "             "));
    lCoffeMenu->addSubitem(new MenuItem("Capucino", 2, "             "));
    lBeveragesMenu->addSubitem(lCoffeMenu);

    lBeveragesMenu->addSubitem(new MenuItem("Pepsi-Cola", 3));

    Menu *lMineralWatersMenu = new Menu("Mineral waters");
    lMineralWatersMenu->addSubitem(new MenuItem("Borjomi", 2.43, "   nice thing  "));
    lMineralWatersMenu->addSubitem(new MenuItem("Morshynska", 1.4, "         "));
    lBeveragesMenu->addSubitem(lMineralWatersMenu);

    Menu *lAlcoDrinksMenu = new Menu("Alco drinks");
    Menu *lWinesMenu = new Menu("Wines");
    Menu *lDryWines = new Menu("Dry Wines");
    lDryWines->addSubitem(new MenuItem("Bordeaux", 20));
    lWinesMenu->addSubitem(lDryWines);
    lWinesMenu->addSubitem(new MenuItem("Champagne", 16.5));
    lAlcoDrinksMenu->addSubitem(lWinesMenu);
    lAlcoDrinksMenu->addSubitem(new MenuItem("Beer", 5));
    lBeveragesMenu->addSubitem(lAlcoDrinksMenu);

    mRoot->addSubitem(lBeveragesMenu);
}
