#ifndef FINDDIALOGUE_H
#define FINDDIALOGUE_H

#include <QDialog>
#include <QTableWidget>
#include <QStringList>


 class QLineEdit;
 class QPushButton;

 class FindDialog : public QDialog
 {
     Q_OBJECT

 public:
     FindDialog(QWidget *parent = 0);
     QString getFindText();
     QTableWidget *extable;
     QTableWidget *foundTable;
     QStringList *foundHeader;
     QList<QTableWidgetItem *> foundList;
     void setTable(QTableWidget *extable);

 public slots:
     void findClicked();

 private:
     QPushButton *findButton;
     QLineEdit *lineEdit;
     QString findText;

 };


#endif // FINDDIALOGUE_H
