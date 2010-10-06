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
    helpButton->hide();
    addButton = new QPushButton("Add");
    addButton->show();
    removeButton = new QPushButton("Remove");
    removeButton->show();
    removeButton->setEnabled(false);
    findButton = new QPushButton("Search");
    findButton->show();

    finddialog = new FindDialog::FindDialog;

    tabBar = new QTabBar(this);
    tabBar->addTab("Book");
    tabBar->addTab("Article");
    tabBar->addTab("Inproceedings");


    //Definição e povoamento inicial das tabelas
    bookTable = new QTableWidget(0,12,this);
    populateBook();
    bookTable->setHorizontalHeaderLabels(*bookHeader);
    bookTable->show();

    articTable = new QTableWidget(0,11,this);
    populateArtic();
    articTable->setHorizontalHeaderLabels(*articHeader);
    articTable->hide();

    inproTable = new QTableWidget(0,14,this);
    populateInpro();
    inproTable->setHorizontalHeaderLabels(*inproHeader);
    inproTable->hide();

    //Sinais Utilizados nas Abas
    connect(tabBar, SIGNAL(currentChanged(int)), this, SLOT(showTable(int)));
    connect(loadButton, SIGNAL(clicked()), this, SLOT(loadfromfile()));
    connect(saveButton, SIGNAL(clicked()),this, SLOT(saveToFile()));
    connect(addButton, SIGNAL(clicked()), this, SLOT(addNovo()));
    connect(findButton, SIGNAL(clicked()), this, SLOT(searchname()));
    connect(bookTable, SIGNAL(cellClicked(int,int)), this, SLOT(activateRemove(int, int)));
    connect(articTable, SIGNAL(cellClicked(int,int)), this, SLOT(activateRemove(int, int)));
    connect(inproTable, SIGNAL(cellClicked(int,int)), this, SLOT(activateRemove(int, int)));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeRow()));



    //connect(addButton, SIGNAL(clicked()), this, SLOT(addTex()));
    //connect(submitButton, SIGNAL(clicked()), this, SLOT(submitTex()));
    //connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));

    tabBar->setCurrentIndex(0);
    finddialog->setTable(bookTable);

    //Definição do Layout
    QVBoxLayout *menuDireito = new QVBoxLayout;
    menuDireito->addWidget(addButton);
    menuDireito->addWidget(removeButton);
    menuDireito->addWidget(findButton);

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

        finddialog->setTable(bookTable);
    }
    else if (tableIndex == 1)
    {
        bookTable->hide();
        articTable->show();
        inproTable->hide();

        finddialog->setTable(articTable);
    }
    else if (tableIndex == 2)
    {
        bookTable->hide();
        articTable->hide();
        inproTable->show();

        finddialog->setTable(inproTable);
    }
    removeButton->setEnabled(false); //Desativa botao para evitar erros

}

void Dicionario::populateBook(void)
{
    bookHeader = new QStringList();
    bookHeader->insert(0,"index");
    bookHeader->insert(1,"author");
    bookHeader->insert(2,"title");
    bookHeader->insert(3,"publisher");
    bookHeader->insert(4,"year");
    bookHeader->insert(5,"volume");
    bookHeader->insert(6,"series");
    bookHeader->insert(7,"address");
    bookHeader->insert(8,"edition");
    bookHeader->insert(9,"month");
    bookHeader->insert(10,"note");
    bookHeader->insert(11,"key");
}

void Dicionario::populateArtic(void)
{
    articHeader = new QStringList();
    articHeader->insert(0,"index");
    articHeader->insert(1,"author");
    articHeader->insert(2,"title");
    articHeader->insert(3,"journal");
    articHeader->insert(4,"year");
    articHeader->insert(5,"volume");
    articHeader->insert(6,"number");
    articHeader->insert(7,"pages");
    articHeader->insert(8,"month");
    articHeader->insert(9,"note");
    articHeader->insert(10,"key");

}

void Dicionario::populateInpro(void)
{
    inproHeader = new QStringList();
    inproHeader->insert(0,"index");
    inproHeader->insert(1,"author");
    inproHeader->insert(2,"title");
    inproHeader->insert(3,"booktitle");
    inproHeader->insert(4,"year");
    inproHeader->insert(5,"editor");
    inproHeader->insert(6,"series");
    inproHeader->insert(7,"pages");
    inproHeader->insert(8,"organization");
    inproHeader->insert(9,"publisher");
    inproHeader->insert(10,"address");
    inproHeader->insert(11,"month");
    inproHeader->insert(12,"note");
    inproHeader->insert(13,"key");

}

void Dicionario::loadfromfile(void)
{
    QString fileName = QFileDialog::getOpenFileName(this,
        "Open Bibtex File", "",
        "Bibtex (*.bib);;All Files (*)");

    if (fileName.isEmpty())
        return;
    else
    {
        //parse file
        bib_parser(fileName.toStdString(), bookTable, articTable, inproTable );

    }

}

void Dicionario::addNovo(void)
{
    int i=0;
    if (tabBar->currentIndex() == 0) //book
    {
        bookTable->setRowCount(bookTable->rowCount()+1);
        for (i=0; i<bookTable->columnCount(); i++)
        {
            QTableWidgetItem *newItem = new QTableWidgetItem("");
            bookTable->setItem(bookTable->rowCount()-1, i, newItem);
        }

    }
    if (tabBar->currentIndex() == 1) //article
    {
        articTable->setRowCount(articTable->rowCount()+1);
        for (i=0; i<articTable->columnCount(); i++)
        {
            QTableWidgetItem *newItem = new QTableWidgetItem("");
            articTable->setItem(articTable->rowCount()-1, i, newItem);
        }
    }
    if (tabBar->currentIndex() == 2) //inproceedings
    {
        inproTable->setRowCount(inproTable->rowCount()+1);
        for (i=0; i<inproTable->columnCount(); i++)
        {
            QTableWidgetItem *newItem = new QTableWidgetItem("");
            inproTable->setItem(inproTable->rowCount()-1, i, newItem);
        }
    }
}

void Dicionario::activateRemove(int row, int column)
{
    if (tabBar->currentIndex() == 0) //book
        book_select = row;
    if (tabBar->currentIndex() == 1) //article
        artic_select = row;
    if (tabBar->currentIndex() == 2) //inproceedings
        inpro_select = row;
    removeButton->setEnabled(true);

}

void Dicionario::removeRow(void)
{
    if (tabBar->currentIndex() == 0) //book
        bookTable->removeRow(book_select);
    if (tabBar->currentIndex() == 1) //article
        articTable->removeRow(artic_select);
    if (tabBar->currentIndex() == 2) //inproceedings
        inproTable->removeRow(inpro_select);
}

void Dicionario::searchname(void)
{
    finddialog->show();
}

void Dicionario::saveToFile()
{
    int row = 0, column = 0;
    QString fileName = QFileDialog::getSaveFileName(this,
        "Save Bibtex", "",
        "Bibtex (*.bib);;All Files (*)");

    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }

        QTextStream out(&file);
        //Books
        for (row = 0; row < bookTable->rowCount(); row++)
        {
            out << "@book{" << bookTable->item(row,column)->text() << ",\n";
            for (column =1; column < bookTable->columnCount(); column++)
            {
                if (bookTable->item(row,column)->text() != "")
                {
                    out << bookTable->horizontalHeaderItem(column)->text()<<"\t\t= "<<bookTable->item(row,column)->text()<<",\n";
                }
            }
            out <<"}\n\n";
            column = 0;
        }
        //Articles
        for (row = 0; row < articTable->rowCount(); row++)
        {
            out << "@article{" << articTable->item(row,column)->text() << ",\n";
            for (column =1; column < articTable->columnCount(); column++)
            {
                if (articTable->item(row,column)->text() != "")
                {
                    out << articTable->horizontalHeaderItem(column)->text()<<"\t\t= "<<articTable->item(row,column)->text()<<",\n";
                }
            }
            out <<"}\n\n";
            column = 0;
        }
        //Inproceedings
        for (row = 0; row < inproTable->rowCount(); row++)
        {
            out << "@inproceedings{" << inproTable->item(row,column)->text() << ",\n";
            for (column =1; column < inproTable->columnCount(); column++)
            {
                if (inproTable->item(row,column)->text() != "")
                {
                    out << inproTable->horizontalHeaderItem(column)->text()<<"\t\t= "<<inproTable->item(row,column)->text()<<",\n";
                }
            }
            out <<"}\n\n";
            column = 0;
        }
    file.close();
    }


}
