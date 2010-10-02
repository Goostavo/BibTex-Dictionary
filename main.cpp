#include <QtGui>
#include <dicionario.h>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    Dicionario *dicionario = new Dicionario;
    dicionario->show();


    return app.exec();
}

