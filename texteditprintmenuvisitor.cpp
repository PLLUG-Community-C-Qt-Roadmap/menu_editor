#include "texteditprintmenuvisitor.h"
#include <QPlainTextEdit>

#include "menuitem.h"
#include "menu.h"
#include <QString>
#include <iostream>
TextEditPrintMenuVisitor::TextEditPrintMenuVisitor(QPlainTextEdit *textEdit):mTextEdit{textEdit}
{

}


/*!
 * \brief TextEditPrintMenuVisitor::indent
 * \param item
 * \return
 */
std::string TextEditPrintMenuVisitor::indent(Composite *item) const
{
    std::string rIndentString;

    std::string lIndentStep = "    ";
    Composite *lMenuItem = item->parent();
    while (lMenuItem)
    {
        lMenuItem = lMenuItem->parent();
        rIndentString.append(lIndentStep);
    }

    return rIndentString;
}

/*!
 * \brief TextEditPrintMenuVisitor::visit
 * \param item
 */
void TextEditPrintMenuVisitor::visit(MenuItem *item)
{
    std::string lIndentString = indent(item);

    std::cout << lIndentString << "> " << item->title() << "    :        " << item->price() << "$" << std::endl;

    if (!item->description().empty())
    {
        std::cout << lIndentString << "    ::::" << item->description() << "::::" << std::endl;
    }
}

/*!
 * \brief TextEditPrintMenuVisitor::visit
 * \param menu
 */
void TextEditPrintMenuVisitor::visit(Menu *menu)
{
//    std::cout << indent(menu) << "[" << menu->title() << "]" << std::endl;
    QString outString;
    outString = QString("[%1]").arg(menu->title().c_str());
    mTextEdit->appendPlainText(outString);
}
