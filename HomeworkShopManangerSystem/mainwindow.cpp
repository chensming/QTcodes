#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineEditShopType->setDisabled(true);
    this->setWindowTitle("超市综合管理系统");
    PU.readFile();
    ui->stackedWidget->setCurrentIndex(2);


    // 1. 添加菜单栏
    QMenuBar *mBar = menuBar();//返回主窗口的菜单栏。如果菜单栏不存在，此函数将创建并返回一个空菜单栏。

    // 2. 菜单栏上添加一个 "文件" 的菜单
    QMenu *pVersion = mBar->addMenu("help");

    // 3. 在文件的菜单上添加添加菜单项
    QAction *pNew = pVersion->addAction("version");//添加 "新建" 菜单项动作
    QString str = "超市管理系统 \n 版本: 1.0  \n 作者: 陈烁明 \t 2019.10";

    // 4. 新建菜单选项的触发动作信号和槽 使用Lambda表达式的匿名槽函数
    connect(pNew,&QAction::triggered,// "新建" 按下后的动作打印信息
            [=] ()
            {
                QMessageBox::information(nullptr, "系统信息通知", str, QMessageBox::Yes);
            }
            );
}

MainWindow::~MainWindow()
{
    PU.writeFile();
    delete ui;
}

//前台管理按钮
void MainWindow::on_pushButtonfrontend_clicked()
{
    ui->listWidget->clear();//把输出商品的一页清空
    //前台管理页面为2
    ui->stackedWidget->setCurrentIndex(2);
}

//密码页面为1  ui->stackedWidget->setCurrentIndex(1);


//后台管理按钮
void MainWindow::on_pushButtonbackend_clicked()
{
    ui->listWidget->clear();//把输出商品的一页清空
    //后台管理页面为0
//    ui->stackedWidget->setCurrentIndex(0);
    //跳转到后台管理的 登陆 页面 Login
    ui->stackedWidget->setCurrentIndex(1);
    ui->lineEditPasswork->setEchoMode(QLineEdit::Password);
}




//退出按钮
void MainWindow::on_pushButtonexit_clicked()
{
    this->close();
}




//添加此商品到清算区按钮
void MainWindow::on_pushButtonAdd_clicked()
{
    QString StrPrice = ui->lineEditSinglePrice->text();
    double SingleShopPrice = StrPrice.toDouble();
    QString StrNum = ui->lineEditNum->text();
    int SingleShopNum = StrNum.toInt();
    totalPrice = totalPrice + SingleShopPrice * SingleShopNum;
    qDebug() << "totalPrice = " << totalPrice <<endl;
    shopNumber = shopNumber + SingleShopNum;
    ui->lineEditHaveNumber->setText( tr("%1 份").arg(shopNumber));
    ui->lineEditTotalPrice->setText( tr("%1 元").arg(totalPrice));

    QString StrIsbNum = ui->lineEditIsbNum->text();
    int IsbNum = StrIsbNum.toInt();
    shoppingCart.enqueue(IsbNum);
    fenshu.enqueue(SingleShopNum);
}



//会员9折按钮 按一次和多次效果一样，因为用了totalPrice变量
void MainWindow::on_pushButtonVIP_clicked()
{
    double ShopPrice = totalPrice * 0.9;
    qDebug() << "VIPShopPrice: " << ShopPrice << endl;
    ui->lineEditTotalPrice->setText(QString::number(ShopPrice,'f',2));
}




//取消结算按钮
void MainWindow::on_pushButtonCancel_clicked()
{
    ui->lineEditIsbNum->setText(QString::number(0,'f',0));
    ui->lineEditNum->setText(QString::number(0,'f',0));
    ui->lineEditSinglePrice->setText(QString::number(0,'f',0));
    ui->lineEditHaveNumber->setText(QString::number(0,'f',0));
    ui->lineEditTotalPrice->setText(QString::number(0,'f',2));
    shopNumber = 0;
    totalPrice = 0;
    QMessageBox::information(nullptr, "操作通知", "取消此次结算成功", QMessageBox::Yes);
    //将两个队列清空
    while(!shoppingCart.isEmpty())
    {
        shoppingCart.dequeue();
    }
    while(!fenshu.isEmpty())
    {
        fenshu.dequeue();
    }

}

//完成结算按钮
void MainWindow::on_pushButtonFinish_clicked()
{
    ui->lineEditIsbNum->setText(QString::number(0,'f',0));
    ui->lineEditNum->setText(QString::number(0,'f',0));
    ui->lineEditSinglePrice->setText(QString::number(0,'f',0));
    ui->lineEditHaveNumber->setText(QString::number(0,'f',0));
    ui->lineEditTotalPrice->setText(QString::number(0,'f',2));

    QString strTotalPrice = QString::number(totalPrice,10,2);

    shopNumber = 0;
    totalPrice = 0;
    QMessageBox::information(nullptr, "操作通知", "完成结算", QMessageBox::Yes);

    int temp1,temp2;
    QString str = "---------购物清单---------\n";
    str += "商品名称\t商品价格\t份数\n";
    QString str1, str2, str3;
    while(!shoppingCart.isEmpty())
    {
        temp1 = shoppingCart.dequeue();
        temp2 = fenshu.dequeue();
        str1 = PU.getName(temp1);
        str2 = QString::number(PU.getSinglePrice(temp1),10,2);
        str3 = QString::number(temp2,10,0);
        //        qDebug() << "商品编号: " << temp1 << " , ";
        qDebug() << "商品名称: " << str1 << " , ";
        qDebug() << "商品价格: " << str2 << " , ";
        qDebug() << "份数: " << str3 << " , ";
        str += str1 + '\t' + str2 + '\t' + str3 + '\n';
    }
    str += "总价:    " + strTotalPrice;
    str += "\n感谢您的光临,期待您下次的到来";

    // QString str = "abc \nabc\tfsdffsd";
    QMessageBox::information(nullptr, "操作通知", str, QMessageBox::Yes);
}

//查找商品按钮
void MainWindow::on_pushButtonSearch_clicked()
{
    //    QString StrIsbNum = ui->lineEditIsbNum->text();
    //    int IsbNum = StrIsbNum.toInt();
    //    qDebug() << "商品编号: " << IsbNum << endl;
    //    double price = PU.getSinglePrice(IsbNum);
    //    if (price < 0.01)
    //        qDebug() << "价格: " << 0.00 << endl;
    //    else
    //        qDebug() << "价格: " << price << endl;
    QString StrIsbNum = ui->lineEditIsbNum->text();
    int IsbNum = StrIsbNum.toInt();
    double price = PU.getSinglePrice(IsbNum);
    QString name = PU.getName((IsbNum));

    ui->lineEditSinglePrice->setText(QString::number(price,'f',2));
    ui->lineEditName->setText(name);
}




void MainWindow::on_pushButtonShopType_clicked()
{
    int number = PU.getShopNum();
    ui->lineEditShopType->setText(QString::number(number,'f',0));
}





bool MainWindow::on_pushButtonHAdd_clicked()
{
    QString StrIsbNumber = ui->lineEditHIsb->text();
    int IsbNumber = StrIsbNumber.toInt();
    QString StrPrice = ui->lineEditHPrice->text();
    double price = StrPrice.toDouble();
    QString StrName = ui->lineEditHName->text();
    int num = PU.getShopNum(); //返回last,初始时last指向-1
    if(IsbNumber != num + 1)
    {
        QMessageBox::information(nullptr, "warning", "添加商品失败", QMessageBox::Yes);
        return false;
    }
    if(!PU.addShop(IsbNumber, price, StrName))
    {
        QMessageBox::information(nullptr, "warning", "添加商品失败", QMessageBox::Yes);
        return false;
    }
    //更新商品编号
    num = num + 1;
    ui->lineEditHIsb->setText(QString::number(num,'f',0));
    QMessageBox::information(nullptr, "操作通知", "添加商品成功", QMessageBox::Yes);
    ui->lineEditHPrice->setText(QString::number(0,'f',2));
    ui->lineEditHName->setText("未输入名称");
    IsbNumber++;
    ui->lineEditHIsb->setText(QString::number(IsbNumber,'f',0));
    return true;
}

void MainWindow::on_pushButtonHGet_clicked()
{
    int num = PU.getShopNum(); //返回last,初始时last指向-1
    num = num + 1;
    ui->lineEditHIsb->setText(QString::number(num,'f',0));
    ui->lineEditHPrice->setText(QString::number(0,'f',2));
    ui->lineEditHName->setText("未输入名称");
}

void MainWindow::on_pushButtonHEdit_clicked()
{
    QString StrIsbNumber = ui->lineEditHIsb->text();
    int IsbNumber = StrIsbNumber.toInt();
    QString StrPrice = ui->lineEditHPrice->text();
    double price = StrPrice.toDouble();
    QString StrName = ui->lineEditHName->text();
    if(PU.setShop(IsbNumber, price, StrName))
        QMessageBox::information(nullptr, "操作通知", "修改商品信息成功", QMessageBox::Yes);
    else
        QMessageBox::information(nullptr, "warning", "修改商品信息失败", QMessageBox::Yes);

}

void MainWindow::on_pushButtonLook_clicked()
{
    QString StrIsbNumber = ui->lineEditHIsb->text();
    int IsbNumber = StrIsbNumber.toInt();
    double price = PU.getSinglePrice(IsbNumber);

    QString name = PU.getName(IsbNumber);
    qDebug() << "name: " << name <<endl;
    ui->lineEditHPrice->setText(QString::number(price,'f',2));
    ui->lineEditHName->setText(name);
}


bool MainWindow::on_pushButtonHDelete_clicked()
{
    if(PU.IsEmpty())
    {
        QMessageBox::information(nullptr, "warning", "仓库已经为空", QMessageBox::Yes);
        return false;
    }
    QString StrIsb = ui->lineEditHIsb->text();
    int Isb = StrIsb.toInt();
    if(1 > Isb || Isb > PU.getShopNum())
    {
        QMessageBox::information(nullptr, "warning", "输入的商品编号不存在", QMessageBox::Yes);
        return false;
    }
    Isb = Isb - 1; //数组从0开始
    PU.ShopNumSubOne(Isb);
    QMessageBox::information(nullptr, "successfully", "删除成功", QMessageBox::Yes);
    ui->lineEditHPrice->setText(QString::number(0,'f',2));
    ui->lineEditHName->setText("未输入名称");
    return true;
}

void MainWindow::on_pushButtonReadFile_clicked()
{
    PU.readFile();
}

void MainWindow::on_pushButtonWriteFile_clicked()
{
    PU.writeFile();
}

void MainWindow::on_pushButtonMakeEmtpy_clicked()
{
    PU.productMakeEmpty();
    ui->lineEditHIsb->setText(QString::number(1,'f',0));
    qDebug() << "PU.getShopNum: 商品数目" << PU.getShopNum() <<endl;
}

void MainWindow::on_pushButton_clicked()
{
    //listWidget页面在3
    ui->stackedWidget->setCurrentIndex(3);
    for(int i = 1; i <= PU.getShopNum(); i++)
    {
        QString str =QString("%7").arg(i) + "                     " + PU.getName(i) + "                 " + QString::number(PU.getSinglePrice(i),5,2);
        QListWidgetItem* item = new QListWidgetItem;
        item->setText(str);
        ui->listWidget->addItem(item);
    }
}

void MainWindow::on_pushButtonBackToFront_clicked()
{
    ui->listWidget->clear();
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButtonLogin_clicked()
{
    QString userName = ui->lineEditUserName->text();
    QString passwork = ui->lineEditPasswork->text();
    if(userName == "root" && passwork == "123456")
    {
        //跳转到后台管理页面0
        ui->stackedWidget->setCurrentIndex(0);
    }
    else {
        QMessageBox::information(nullptr, "warning", "用户名或密码输入错误", QMessageBox::Yes);
    }

    ui->lineEditUserName->clear();
    ui->lineEditPasswork->clear();
}

void MainWindow::on_pushButtonLoginCancel_clicked()
{

    ui->lineEditUserName->clear();
    ui->lineEditPasswork->clear();
}
