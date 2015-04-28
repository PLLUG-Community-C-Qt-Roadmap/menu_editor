#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class Menu;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void slotPrintMenu();

private:
    void createMenu();

private:
    Ui::MainWindow *ui;
    Menu *mRoot;
};

#endif // MAINWINDOW_H
