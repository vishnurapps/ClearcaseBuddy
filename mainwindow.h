#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

namespace Ui {
   class MainWindow;
}

class MainWindow : public QMainWindow
{
   Q_OBJECT
public:
   explicit MainWindow(QWidget *parent = 0);
private slots:
   void handleButton();
private:
   QPushButton *m_button;
   QLabel *lbl_username;
   QLineEdit *le_username;

};

#endif // MAINWINDOW_H
