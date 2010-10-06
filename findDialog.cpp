#include <QtGui>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "findDialog.h"
#include <QList>

FindDialog::FindDialog(QWidget *parent)
    : QDialog(parent)
{
    //foundList = new QList<QTableWidgetItem *>(;
    QLabel *findLabel = new QLabel(tr("Enter the name of a contact:"));
    lineEdit = new QLineEdit;

    foundTable = new QTableWidget(0, 3, this);
    foundHeader = new QStringList();
    foundHeader->insert(0,"Campo");
    foundHeader->insert(1,"Dado");
    foundHeader->insert(2,"Localizacao");
    foundTable->setHorizontalHeaderLabels(*foundHeader);


    findButton = new QPushButton("Find");
    findText = "";

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(findLabel);
    layout->addWidget(lineEdit);
    layout->addWidget(findButton);
    layout->addWidget(foundTable);

    setLayout(layout);
    setWindowTitle(tr("Find a Contact"));
    connect(findButton, SIGNAL(clicked()), this, SLOT(findClicked()));
    //connect(foundTable, SIGNAL(cellDoubleClicked()), this, SLOT(accept()));
}
void FindDialog::findClicked()
{
    int aux, col;
    QString text = lineEdit->text();
    QString number = "";

    if (text.isEmpty()) {
        QMessageBox::information(this, "Empty Field","Please insert data to find");
    } else {
        foundList = extable->findItems(text, Qt::MatchContains);
        foundTable->setRowCount(foundList.size());
        if (foundList.size() <= 0)
        {
            QMessageBox::information(this, "Not Found","Please insert other data to find");
        }
        else {
            for (aux=0; aux<foundList.size(); aux++)
            {
                QTableWidgetItem *newItem = new QTableWidgetItem(foundList[aux]->text());
                newItem->setFlags(newItem->flags() & (~Qt::ItemIsEditable));
                foundTable->setItem(aux,1,newItem);
                QTableWidgetItem *newItem2 = new QTableWidgetItem(extable->horizontalHeaderItem(foundList[aux]->column())->text());
                newItem2->setFlags(newItem2->flags() & (~Qt::ItemIsEditable));
                foundTable->setItem(aux,0,newItem2);
                number.setNum(foundList[aux]->row()+1, 10);
                QTableWidgetItem *newItem3 = new QTableWidgetItem(number);
                newItem3->setFlags(newItem3->flags() & (~Qt::ItemIsEditable));
                foundTable->setItem(aux,2,newItem3);
            }
        }
    }
}
QString FindDialog::getFindText()
{
    return findText;
}

void FindDialog::setTable(QTableWidget *extable)
{
    this->extable = extable;
}
