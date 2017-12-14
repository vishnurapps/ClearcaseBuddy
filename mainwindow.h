#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QCheckBox>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void writeToFile();

private slots:
    void on_pbConnect_clicked();

private:
    Ui::MainWindow *ui;
    void showLoginScreen();
};

#endif // MAINWINDOW_H

