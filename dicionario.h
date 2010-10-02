#ifndef DICIONARIO_H
#define DICIONARIO_H

#include <QtGui>
#include <QWidget>
#include <QTableWidget>
#include <QTabBar>
#include <QStringList>
#include <QTableWidgetItem>

class QLabel;
class QPushButton;
class QtableWidget;
class QStringList;
class QTableWidgetItem;



class Dicionario : public QWidget
{
    Q_OBJECT

public:
    Dicionario(QWidget *parent = 0);
    QTableWidget *bookTable;
    QTableWidget *articTable;
    QTableWidget *inproTable;

public slots:
    //Slot para trocar de tabela utilizando o sistema de abas
    void showTable(int tableIndex);

    //void addTex();
    //void submitTex();
    //void cancel();

private:
    QPushButton *loadButton;
    QPushButton *saveButton;
    QPushButton *helpButton;

    QPushButton *addButton;
    QPushButton *removeButton;
    QTabBar *tabBar;

    //Header para as tabelas
    QStringList *bookHeader;
    QStringList *articHeader;
    QStringList *inproHeader;

    //Função para o povoamento inicial da tabela de "book"s 
    void populateBook(void);
    void populateArtic(void);
    void populateInpro(void);
};


#endif // DICIONARIO_H
