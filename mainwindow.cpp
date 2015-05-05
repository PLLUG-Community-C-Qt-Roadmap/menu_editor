#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "texteditprintmenuvisitor.h"
#include "menuiterator.h"
#include "menu.h"
#include "menuitem.h"
#include "discountmenuitem.h"
#include "adddialog.h"
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QString>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mRoot{nullptr}
{
    ui->setupUi(this);
    resize(800, 600);

    connect(ui->menuComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(menuElementSelected()), Qt::UniqueConnection);
    connect(ui->action_Add, SIGNAL(triggered(bool)),
            this, SLOT(slotAddNewItem()), Qt::UniqueConnection);
    connect(ui->savePushButton, SIGNAL(clicked(bool)),
            this, SLOT(slotSaveEditedItem()), Qt::UniqueConnection);
    connect(ui->menuEditorDelegate, SIGNAL(itemChanged()),
            this, SLOT(slotItemChanged()), Qt::UniqueConnection);
    connect(ui->actionAbout_Menu_Editor, SIGNAL(triggered(bool)), this, SLOT(slotAboutProgram()));
    connect(ui->actionAbout_Qt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mRoot;
}

void MainWindow::slotPrintMenu()
{
    ui->menuTextEdit->clear();
    TextEditPrintMenuVisitor visitor (ui->menuTextEdit);
    MenuIterator iterator(mRoot);
    while(iterator.hasNext())
    {
        auto item =  iterator.next();
        item->accept(&visitor);
    }
}

void MainWindow::menuElementSelected()
{
    ui->savePushButton->setEnabled(false);
    Composite * item = ui->menuComboBox->currentMenuItem();
    MenuVisitor *visitor = ui->menuEditorDelegate;
    item->accept(visitor);
}

void MainWindow::slotUpdateMenu()
{
    int index = ui->menuComboBox->currentIndex();
    ui->menuComboBox->setMenu(mRoot);
    slotPrintMenu();
    ui->menuComboBox->setCurrentIndex(index);
}

void MainWindow::slotAddNewItem()
{
    AddDialog addDialog;
    addDialog.setMenu(mRoot);

    if (addDialog.exec())
    {
        Composite *newItem = addDialog.newMenuItem();

        if (newItem)
        {
            slotUpdateMenu();
        }
    }
}

void MainWindow::slotItemChanged()
{
    ui->savePushButton->setEnabled(true);
}

void MainWindow::slotSaveEditedItem()
{
    ui->savePushButton->setEnabled(false);
    ui->menuEditorDelegate->slotSave();
    slotUpdateMenu();
}

void MainWindow::readFromJSON(const QJsonObject &json, Composite *pRoot)
{
    Composite *newMenu;

    // If pRoot isn't first element
    if(pRoot)
    {
        newMenu = new Menu(json["title"].toString().toStdString());
    }
    else
    {
        mRoot = new Menu(json["title"].toString().toStdString());
        newMenu = mRoot;
    }

    QJsonArray subitemsArray = json["children"].toArray();
    for (int index = 0;index < subitemsArray.size(); ++index)
    {
        if(!subitemsArray[index].toObject()["type"].toString().compare("Menu"))
        {
            // Filling newMenu recursively with items
            readFromJSON(subitemsArray[index].toObject(), newMenu);

        }
        else if(!subitemsArray[index].toObject()["type"].toString().compare("MenuItem"))
        {

            double lPrice = subitemsArray[index].toObject()["price"].toDouble();
            std::string lDescription = subitemsArray[index].toObject()["description"].toString().toStdString();
            std::string lTitle = subitemsArray[index].toObject()["title"].toString().toStdString();

            newMenu->addSubitem( new MenuItem(lTitle, lPrice, lDescription));
        }

    }

    if(pRoot)
    {
        // Adding newMenu as subitem to pRoot
        pRoot->addSubitem(newMenu);
    }

}

void MainWindow::on_action_Open_triggered()
{
    QString lFileName = QFileDialog::getOpenFileName(this, tr("Open file.."),
                        QDir::currentPath(), tr("JSON files (*.json)"));
    if(lFileName.isEmpty())
    {
        return;
    }

    QFile lFile(lFileName);

    if(lFile.open(QIODevice::ReadOnly))
    {

        QByteArray loadedData = lFile.readAll();
        lFile.close();

        QJsonDocument loadedJSON = QJsonDocument::fromJson(loadedData);

        delete mRoot;

        readFromJSON(loadedJSON.object(), nullptr);

        slotUpdateMenu();
    }
    else
    {
        QMessageBox::warning(this, tr("Error"),
              QString(tr("Could not open file %1 for reading")).arg(lFile.fileName()),
              QMessageBox::Ok);
    }
}
QJsonArray MainWindow::writeToJSON(Composite *root)
{
    QJsonObject obj;
    QJsonArray arr;
    for(int i = 0; i < root->subitemsCount(); i++)
    {


        if(root->child(i)->type() == "Menu")
        {
            Menu *temp = dynamic_cast<Menu*>(root->child(i));
            obj["type"] = "Menu";
            obj["title"] = temp->title().c_str();
            obj["children"] = writeToJSON(root->child(i));
        }
        else
        {
            MenuItem *temp = dynamic_cast<MenuItem*>(root->child(i));
            obj["type"] = "MenuItem";
            obj["title"] = temp->title().c_str();
            obj["price"] = temp->price();
            obj["description"] = temp->description().c_str();

        }
        arr.append(obj);
    }
    return arr;
}

void MainWindow::on_action_Save_triggered()
{
    QString lFileName = QFileDialog::getSaveFileName(this, tr("Save file.."), "Menu",
                                             tr("JSON files (*.json)"));
    if(lFileName.isEmpty())
        return;
    QJsonObject mainJSONObj;

    mainJSONObj["type"] = "Menu";
    mainJSONObj["title"] = "MAIN MENU";
    mainJSONObj["children"] = writeToJSON(mRoot);


    QJsonDocument mainDoc(mainJSONObj);

    QFile jsonFile(lFileName);
        jsonFile.open(QFile::WriteOnly);
        jsonFile.write(mainDoc.toJson());
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
    lAlcoDrinksMenu->addSubitem(new DiscountMenuItem("Whiskey", 5, 0.15));
    lBeveragesMenu->addSubitem(lAlcoDrinksMenu);

    mRoot->addSubitem(lBeveragesMenu);
}

void MainWindow::slotAboutProgram()
{
    QMessageBox::about(this,tr("About"), QString("%1 v. %2").arg(qApp->applicationName()).arg(qApp->applicationVersion()));
}

void MainWindow::on_actionView_Example_Menu_triggered()
{
    ui->menuComboBox->clear();
    ui->savePushButton->setEnabled(false);
    ui->menuTextEdit->clear();
    createMenu();
    slotPrintMenu();
}
