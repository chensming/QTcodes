#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "circle.h"
#include "rectangle.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->aButton,&QPushButton::clicked,this,&MainWindow::switchPage);
    connect(ui->bButton,&QPushButton::clicked,this,&MainWindow::switchPage);
    connect(ui->cButton,&QPushButton::clicked,this,&MainWindow::switchPage);

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::switchPage(){
    QPushButton *button = qobject_cast<QPushButton*>(sender());//得到按下的按钮的指针
    if(button==ui->aButton)
    {
        ui->stack->setCurrentIndex(0);
        //根据按下的button按索引显示相应的页面
        //stackwidget要从0开始
//        qDebug()<<"1111111"<<endl;
    }

    else if(button==ui->bButton){
        ui->stack->setCurrentIndex(1);
//        qDebug()<<"2222222"<<endl;
    }

    else if(button==ui->cButton){
        ui->stack->setCurrentIndex(2);
//        qDebug()<<"33333333"<<endl;
    }


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

void MainWindow::on_exitButton2_clicked()
{
    this->close();
}

void MainWindow::on_calcButton2_clicked()
{
    QString lengthString = ui->lengthEdit->text();
    double length = lengthString.toDouble();

    QString widthString = ui->widthEdit->text();
    double width = widthString.toDouble();

    rectangle r1(length,width);
    double area = r1.RectangleArea();
    ui->areaEdit2->setText(QString::number(area,'f',2));
}
