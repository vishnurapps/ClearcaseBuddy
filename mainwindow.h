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

#ifdef linux
#include "libssh2_config.h"
#include <libssh2.h>
#endif

#ifdef HAVE_WINSOCK2_H
#include <winsock2.h>
#endif
#ifdef HAVE_SYS_SOCKET_H
#include <sys/socket.h>
#endif
#ifdef HAVE_NETINET_IN_H
#include <netinet/in.h>
#endif
#ifdef HAVE_SYS_SELECT_H
#include <sys/select.h>
#endif
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#ifdef HAVE_ARPA_INET_H
#include <arpa/inet.h>
#endif
#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#endif
#include <sys/types.h>
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <ctype.h>

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
    static int waitsocket(int socket_fd, LIBSSH2_SESSION *session);

private slots:
    void pbConnectclicked();
    void quit();
    void autoLoad();
    void about();
    void aboutQt();

private:
    void createActions();
    void createMenus();
    void showLoginScreen();
#ifdef linux
     int loginToServer(QString, QString, QString);
#endif
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
