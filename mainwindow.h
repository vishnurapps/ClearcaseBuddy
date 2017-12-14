#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QActionGroup>

class QAction;
class QActionGroup;
class QLabel;
class QMenu;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void writeToFile(QString serverName, QString username, QString password);
    void ReadFromFile();

private slots:
    void on_pbConnect_clicked();
    void quit();
    void autoLoad();
    void about();
    void aboutQt();

private:
    void createActions();
    void createMenus();
    void showLoginScreen();
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *formatMenu;
    QMenu *helpMenu;
    QLineEdit *leMachineIP;
    QLineEdit *leUsername;
    QLineEdit *lePassword;
    QPushButton *pbConnect;
    QPushButton *pbCancel;
    QCheckBox *cbRemember;
    QActionGroup *alignmentGroup;
    Ui::MainWindow *ui;
    QAction *quitAct;
    QAction *loadAct;
    QAction *aboutAct;
    QAction *aboutQtAct;

};

#endif // MAINWINDOW_H
