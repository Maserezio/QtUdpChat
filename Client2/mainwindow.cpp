#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    udpsocket =new QUdpSocket(this);
    udpsocket->bind(QHostAddress::LocalHost, 4444);
    connect(udpsocket, &QUdpSocket::readyRead, this, &MainWindow::ReadingData);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow :: ReadingData()
{
    QHostAddress sender;
    quint16 senderPort;

    QByteArray datagram;
    datagram.resize(udpsocket->pendingDatagramSize());
    udpsocket->readDatagram(datagram.data(),datagram.size(),&sender, &senderPort);
    ui->textBrowser->insertPlainText("[Client1]:" + QString(datagram) + "\n");

}

void MainWindow::on_pushButton_clicked()
{
    if(ui->textEdit->toPlainText()!="")
    {
        ui->textBrowser->insertPlainText("[Client2]: " + ui->textEdit->toPlainText() + "\n");
        udpsocket->writeDatagram(ui->textEdit->toPlainText().toUtf8(), QHostAddress::LocalHost, 3333);
    }

}
