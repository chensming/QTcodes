#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "circle.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_exitButton_clicked()
{
    this->close();
}

void MainWindow::on_calcButton_clicked()
{
    QString radiusString = ui->radiusEdit->text();
    double radius = radiusString.toDouble();

    Circle c1(radius);
    double area = c1.CircleArea();
    ui->areaEdit->setText(QString::number(area,'f',2));
}
