#include <dicionario.h>

Dicionario::Dicionario(QWidget *parent)
    : QWidget(parent)
{
    //Definição dos Widgets Utilizados
    loadButton = new QPushButton("Load");
    loadButton->show();
    saveButton = new QPushButton("Save");
    saveButton->show();
    helpButton = new QPushButton("Help");
    helpButton->show();
    addButton = new QPushButton("Add");
    addButton->show();
    removeButton = new QPushButton("Remove");
    removeButton->show();
    tabBar = new QTabBar(this);
    tabBar->addTab("Book");
    tabBar->addTab("Article");
    tabBar->addTab("Inproceedings");

    //Definição e povoamento inicial das tabelas
    bookTable = new QTableWidget(1,11,this);
    populateBook();
    bookTable->setHorizontalHeaderLabels(*bookHeader);
    bookTable->show();

    articTable = new QTableWidget(1,10,this);
    populateArtic();
    articTable->setHorizontalHeaderLabels(*articHeader);
    articTable->hide();

    inproTable = new QTableWidget(1,13,this);
    populateInpro();
    inproTable->setHorizontalHeaderLabels(*inproHeader);
    inproTable->hide();

    //Sinais Utilizados nas Abas
    connect(tabBar, SIGNAL(currentChanged(int)), this, SLOT(showTable(int)));



    //connect(addButton, SIGNAL(clicked()), this, SLOT(addTex()));
    //connect(submitButton, SIGNAL(clicked()), this, SLOT(submitTex()));
    //connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));

    tabBar->setCurrentIndex(0);

    //Definição do Layout
    QVBoxLayout *menuDireito = new QVBoxLayout;
    menuDireito->addWidget(addButton);
    menuDireito->addWidget(removeButton);

    QHBoxLayout *menuSuperior = new QHBoxLayout;
    menuSuperior->addWidget(loadButton);
    menuSuperior->addWidget(saveButton);
    menuSuperior->addWidget(helpButton);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addLayout(menuSuperior, 0, 0);
    mainLayout->addWidget(tabBar,1,0);
    mainLayout->addWidget(bookTable, 2, 0);              //Apenas uma tabela aparecerá por vez
    mainLayout->addWidget(articTable, 2, 0);
    mainLayout->addWidget(inproTable, 2, 0);
    mainLayout->addLayout(menuDireito, 1, 1);

    setLayout(mainLayout);
    setWindowTitle("BibTex Dictionary");
}

void Dicionario::showTable(int tableIndex)
{
    if (tableIndex == 0)
    {
        bookTable->show();
        articTable->hide();
        inproTable->hide();
    }
    else if (tableIndex == 1)
    {
        bookTable->hide();
        articTable->show();
        inproTable->hide();
    }
    else if (tableIndex == 2)
    {
        bookTable->hide();
        articTable->hide();
        inproTable->show();
    }

}

void Dicionario::populateBook(void)
{
    bookHeader = new QStringList();
    bookHeader->insert(0,"Author/Editor");
    bookHeader->insert(1,"Title");
    bookHeader->insert(2,"Publisher");
    bookHeader->insert(3,"Year");
    bookHeader->insert(4,"Volume");
    bookHeader->insert(5,"Series");
    bookHeader->insert(6,"Address");
    bookHeader->insert(7,"Edition");
    bookHeader->insert(8,"Month");
    bookHeader->insert(9,"Note");
    bookHeader->insert(10,"Key");


    //QTableWidgetItem *newitem = new QTableWidgetItem("abba");
    //bookTable->setItem(0,0,newitem);
}

void Dicionario::populateArtic(void)
{
    articHeader = new QStringList();
    articHeader->insert(0,"Author");
    articHeader->insert(1,"Title");
    articHeader->insert(2,"Journal");
    articHeader->insert(3,"Year");
    articHeader->insert(4,"Volume");
    articHeader->insert(5,"Number");
    articHeader->insert(6,"Pages");
    articHeader->insert(7,"Month");
    articHeader->insert(8,"Note");
    articHeader->insert(9,"Key");

}

void Dicionario::populateInpro(void)
{
    inproHeader = new QStringList();
    inproHeader->insert(0,"Author");
    inproHeader->insert(1,"Title");
    inproHeader->insert(2,"Booktitle");
    inproHeader->insert(3,"Year");
    inproHeader->insert(4,"Editor");
    inproHeader->insert(5,"Series");
    inproHeader->insert(6,"Pages");
    inproHeader->insert(7,"Organization");
    inproHeader->insert(8,"Publisher");
    inproHeader->insert(9,"Address");
    inproHeader->insert(10,"Month");
    inproHeader->insert(11,"Note");
    inproHeader->insert(12,"Key");

}
