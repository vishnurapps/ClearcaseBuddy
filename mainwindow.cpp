#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mainwindow.h"
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setWindowTitle("Clear Case Buddy");
    setWindowIcon(QIcon(":/resource/ClearCase.jpg"));

    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    QWidget *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QWidget *wid = new QWidget(this);
    QGridLayout *gridLayout = new QGridLayout;

    QLabel *lblMachineIP = new QLabel(this);
    lblMachineIP->setText("Machine IP");
    gridLayout->addWidget(lblMachineIP, 0, 0, 1, 1);

    QLabel *lblUsername = new QLabel(this);
    lblUsername->setText("Username");

    gridLayout->addWidget(lblUsername, 1, 0, 1, 1);

    QLabel *lblPassword = new QLabel(this);
    lblPassword->setText("Password");
    gridLayout->addWidget(lblPassword, 2, 0, 1, 1);

    leMachineIP = new QLineEdit(this);
    gridLayout->addWidget(leMachineIP, 0, 1, 1, 1);

    leUsername = new QLineEdit(this);
    gridLayout->addWidget(leUsername, 1, 1, 1, 1);

    lePassword = new QLineEdit(this);
    lePassword->setEchoMode(QLineEdit::Password);
    gridLayout->addWidget(lePassword, 2, 1, 1, 1);

    cbRemember = new QCheckBox(this);
    cbRemember->setChecked(false);
    cbRemember->setText("Save these credentials");
    gridLayout->addWidget(cbRemember, 3, 0, 1, 2);

    pbConnect = new QPushButton(this);
    pbConnect->setText("Connect");
    gridLayout->addWidget(pbConnect, 4, 0, 1, 1);

    pbCancel = new QPushButton(this);
    pbCancel->setText("Close");
    gridLayout->addWidget(pbCancel, 4, 1, 1, 1);

    wid->setLayout(gridLayout);
    //setCentralWidget(wid);

    connect(pbCancel, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(pbConnect, SIGNAL(clicked(bool)), this, SLOT(pbConnectclicked()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(5);
    layout->addWidget(topFiller);
    layout->addWidget(wid);
    layout->addWidget(bottomFiller);
    widget->setLayout(layout);

    createActions();
    createMenus();
}


void MainWindow::writeToFile(QString serverName, QString username, QString password)
{
    qDebug() << "Inside void MainWindow::writeToFile()";
    QString filename="Data.txt";
    QFile mFile(filename);
    if(!mFile.open(QFile::WriteOnly|QFile::Text))
    {
        qDebug() << "Couldnt open file for writing";
        return;
    }

    QTextStream out(&mFile);
    out << serverName << "\n" << username << "\n" << password;
    mFile.flush();
    mFile.close();
}

void MainWindow::ReadFromFile()
{
    qDebug() << "Inside void MainWindow::ReadFromFile()";
    QString filename="Data.txt";
    QFile mFile(filename);
    QFileInfo check_file(filename);

    if (!(check_file.exists() && check_file.isFile()))
    {
        QMessageBox::information(this, "No Saved Credentials", "Couldn't find any saved credentials. Please save credentials to use this functionality");
        return;
    }
    if(!mFile.open(QFile::ReadOnly|QFile::Text))
    {

        qDebug() << "Couldnt open file for reading";
        return;
    }

    QTextStream in(&mFile);
    QString line = in.readLine();
    leMachineIP->setText(line);
    line = in.readLine();
    leUsername->setText(line);
    line = in.readLine();
    lePassword->setText(line);
    mFile.flush();
    mFile.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pbConnectclicked()
{
    if(cbRemember->isChecked())
    {
        if(leMachineIP->text().isEmpty() ||
                    leUsername->text().isEmpty() ||
                    lePassword->text().isEmpty())
            {
                QMessageBox::information(this, "Incomplete Information", "All fields are mandatory. Please fill all the fields and retry");
                return;
            }
        writeToFile(leMachineIP->text(), leUsername->text(), lePassword->text());
        QMessageBox::information(this, "Credentials Saved", "Your login credentials have been saved successfully");
#ifdef linux
        loginToServer(leMachineIP->text(), leUsername->text(), lePassword->text());
#endif
    }
    else
    {
#ifdef linux
        loginToServer(leMachineIP->text(), leUsername->text(), lePassword->text());
#endif
    }

}

void MainWindow::createActions()
{
    quitAct = new QAction(tr("&Quit"), this);
    quitAct->setStatusTip(tr("Exit the Application"));
    connect(quitAct, &QAction::triggered, this, &MainWindow::quit);

    loadAct = new QAction(tr("&Autosave"), this);
    loadAct->setStatusTip(tr("Enable Autosave"));
    loadAct->setCheckable(true);
    connect(loadAct, &QAction::triggered, this, &MainWindow::autoLoad);

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, &QAction::triggered, qApp, &QApplication::aboutQt);
    connect(aboutQtAct, &QAction::triggered, this, &MainWindow::aboutQt);

    loadAct->setChecked(false);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(quitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(loadAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void MainWindow::quit()
{
    QWidget::close();
}

void MainWindow::autoLoad()
{
    if(loadAct->isChecked())
    {
        ReadFromFile();
    }
    qDebug() << " Inside void MainWindow::autoSave()";
}

void MainWindow::about()
{
    qDebug() << " Inside void MainWindow::about()";
    QMessageBox::information(this, "Clear Case Buddy", "This is a opensource project aimed to make the clear case usage simple and easy.");
}

void MainWindow::aboutQt()
{
    qDebug() << " Inside void MainWindow::aboutQt()";
}

int MainWindow::waitsocket(int socket_fd, LIBSSH2_SESSION *session)
{
    struct timeval timeout;
    int rc;
    fd_set fd;
    fd_set *writefd = NULL;
    fd_set *readfd = NULL;
    int dir;

    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    FD_ZERO(&fd);

    FD_SET(socket_fd, &fd);

    /* now make sure we wait in the correct direction */
    dir = libssh2_session_block_directions(session);


    if(dir & LIBSSH2_SESSION_BLOCK_INBOUND)
        readfd = &fd;

    if(dir & LIBSSH2_SESSION_BLOCK_OUTBOUND)
        writefd = &fd;

    rc = select(socket_fd + 1, readfd, writefd, NULL, &timeout);

    return rc;
}

#ifdef linux
    int MainWindow::loginToServer(QString machineIP, QString userName, QString password);
#endif
