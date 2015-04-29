#ifndef MENUCOMBOBOX_H
#define MENUCOMBOBOX_H

#include <QComboBox>

class Composite;

class MenuComboBox : public QComboBox
{
    Q_OBJECT
public:
    MenuComboBox(QWidget *parent = 0);

    void setMenu(Composite *menu);

private:
    void populateComboBox();

private:
    Composite *mRoot;
};

#endif // MENUCOMBOBOX_H
