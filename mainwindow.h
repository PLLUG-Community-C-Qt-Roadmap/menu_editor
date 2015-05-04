#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class Composite;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void slotPrintMenu();
    void slotAboutProgram();

private slots:

    void menuElementSelected();

    void slotUpdateMenu();
    void slotAddNewItem();

    void slotItemChanged();
    void slotSaveEditedItem();

    void on_action_Open_triggered();
    void on_action_Save_triggered();

private:
    void createMenu();
    QJsonArray writeToJSON(Composite *root);

private:
    Ui::MainWindow *ui;
    Composite *mRoot;
    void readFromJSON(const QJsonObject &json, Composite *pRoot);
};

#endif // MAINWINDOW_H
