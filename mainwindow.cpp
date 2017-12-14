#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mainwindow.h"
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    showLoginScreen();

}

void MainWindow :: showLoginScreen()
{
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

    QLineEdit *leMachineIP = new QLineEdit(this);
    gridLayout->addWidget(leMachineIP, 0, 1, 1, 1);

    QLineEdit *leUsername = new QLineEdit(this);
    gridLayout->addWidget(leUsername, 1, 1, 1, 1);

    QLineEdit *lePassword = new QLineEdit(this);
    lePassword->setEchoMode(QLineEdit::Password);
    gridLayout->addWidget(lePassword, 2, 1, 1, 1);

    QCheckBox *cbRemember = new QCheckBox(this);
    cbRemember->setChecked(false);
    cbRemember->setText("Save these credentials");
    gridLayout->addWidget(cbRemember, 3, 0, 1, 2);

    QPushButton *pbConnect = new QPushButton(this);
    pbConnect->setText("Connect");
    gridLayout->addWidget(pbConnect, 4, 0, 1, 1);

    QPushButton *pbCancel = new QPushButton(this);
    pbCancel->setText("Close");
    gridLayout->addWidget(pbCancel, 4, 1, 1, 1);

    if(cbRemember->isChecked())
    {
            writeToFile(leMachineIP->text(), leUsername->text(), lePassword->text());
    }

    wid->setLayout(gridLayout);
    setCentralWidget(wid);

    connect(pbCancel, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(pbConnect, SIGNAL(clicked(bool)), this, SLOT(on_pbConnect_clicked()));
}

void MainWindow::writeToFile()
{
    QString filename="Data.txt";
    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        stream << "something" << endl;
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbConnect_clicked()
{
    //qDebug()<<"test";
    QMessageBox::information(this, "Test Button clicked", "You clicked a button");
}
