#ifndef DICIONARIO_H
#define DICIONARIO_H

#include <QtGui>
#include <QWidget>
#include <QTableWidget>
#include <QTabBar>
#include <QStringList>
#include <QTableWidgetItem>
#include <QFileDialog>
#include <QString>
#include "parser.h"
#include "findDialog.h"


class QLabel;
class QPushButton;
class QtableWidget;
class QStringList;
class QTableWidgetItem;
class QFileDialog;



class Dicionario : public QWidget
{
    Q_OBJECT

public:
    Dicionario(QWidget *parent = 0);
    QTableWidget *bookTable;
    QTableWidget *articTable;
    QTableWidget *inproTable;
    FindDialog::FindDialog *finddialog;

public slots:
    //Slot para trocar de tabela utilizando o sistema de abas
    void showTable(int tableIndex);
    //Slot que chama a janela de carregar arquivo
    void loadfromfile(void);
    //Slot que salva para um arquivo
    void saveToFile(void);
    //Slot para adição de mais um dado na tabela
    void addNovo(void);
    //Ativa botao de Remove
    void activateRemove(int row, int column);
    //Remove uma coluna especificada
    void removeRow(void);
    //Ativa o dialogo de procura
    void searchname(void);

    //void addTex();
    //void submitTex();
    //void cancel();

private:

    int book_select; //Variavel utilizada para apagar uma linha
    int artic_select;
    int inpro_select;

    QPushButton *loadButton;
    QPushButton *saveButton;
    QPushButton *helpButton;

    QPushButton *addButton;
    QPushButton *removeButton;
    QPushButton *findButton;
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
