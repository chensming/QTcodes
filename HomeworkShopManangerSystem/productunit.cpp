#include "productunit.h"
#include <iostream>
#include <fstream>
#include <QDebug>
#include <string>
#include <QObject>
#include <QFile>
#include <QDataStream>
using namespace std;

//last指向元素
productUnit::productUnit(int sz)
{
    if (sz < 0)
    {
        maxSize = defaultSize;
        qDebug() << "输入的商品数量为负数,已重置为默认大小" << endl;
    }
    last = -1;
    data = new productType[maxSize];
    if (data == nullptr)
    {
        maxSize = 0;
        last = -1;
        return;
    }
}

productUnit::~productUnit()
{
    maxSize = 0;
    last = -1;
    delete[] data;
}

//仓库满处理函数
void productUnit::overflowProcess()
{
    productType *newdata = new productType[maxSize + increase];
    if (nullptr == newdata)
    {
        qDebug() << "分配内存失败" << endl;
        exit(1);
    }
    maxSize = maxSize + increase;
    for (int i = 0; i <= last; i++)
    {
        newdata[i] = data[i];
    }
    qDebug() << "扩增到maxSize" << maxSize << "个!!!" << endl;
}




bool productUnit::productMakeEmpty()
{
    if (IsEmpty())
    {
        qDebug() << "仓库种类为空" << endl;
        return false;
    }
    last = -1;
    qDebug() << "清空成功" << endl;
    return true;
}




void productUnit::readFile()
{
    QFile infile("product.txt");
    infile.open(QIODevice::ReadOnly);
    QDataStream in(&infile);
    int i = 0;
    while(!in.atEnd())
    {
        in >> data[i].ISBnumber >> data[i].price >> data[i].name;
        i++;
        last++;
        qDebug() << "正在读取" << i << "条信息....." << endl;
    }
    infile.close();
    qDebug() << "读取 " << last + 1 << "条信息成功" << endl;


    //    ifstream infile("product.dat", ios::in | ios::out | ios::binary);
    //    if (!infile)
    //    {
    //        qDebug() << "product.dat文件打开错误" << endl;
    //        exit(1);
    //    }
    //    int i = 0;
    //    while (infile.read((char *)&data[i], sizeof(data[i])))
    //    {
    //        i++;
    //        last++;
    //    }
    //    qDebug() << "读取 " << last + 1 << "条信息成功" << endl;
    //    qDebug() << endl;
    //    qDebug() << endl;
}

void productUnit::writeFile()
{
    if (-1 == last)
    {
        qDebug() << "!!!继续将会导致数据被清空，是否继续?" << endl;
    }
    QFile outfile("product.txt");
    outfile.open(QIODevice::WriteOnly);
    QDataStream out(&outfile);
    for (int i = 0; i <= last; i++)
    {
        out << data[i].ISBnumber << data[i].price << data[i].name;
        qDebug() << "product.dat写入" << i + 1 << "条成功" << endl;
    }
    outfile.flush();
    outfile.close();
    if (-1 == last)
        qDebug() << "product.dat清空成功" << endl;
    else
        qDebug() << " write " << last + 1 << " information successfully!" << endl;
    qDebug() << endl;

    //    ofstream outfile("product.dat", ios::binary);
    //    if (!outfile)
    //    {
    //        qDebug() << "打开product.dat失败" << endl;
    //        exit(1);
    //    }
    //    for (int i = 0; i <= last; i++)
    //    {
    //        outfile.write((char *)&data[i], sizeof(data[i]));
    //        qDebug() << "product.dat写入" << i + 1 << "条成功" << endl;
    //    }
    //    outfile.close();
    //    qDebug() << endl;
    //    if (-1 == last)
    //        qDebug() << "product.dat清空成功" << endl;
    //    else
    //        qDebug() << " write " << last + 1 << " information successfully!" << endl;
    //    qDebug() << endl;
}





//修改商品的编号,价格,名称
bool productUnit::setShop(int number, double price,QString name)
{
    if(number > last + 1 || number < 1)
    {
        qDebug() << "修改失败,没有此编号的商品" << endl;
        return false;
    }
    if(price < 0.01 || name == "未输入名称")
    {
        qDebug() << "price < 0.01 || name == 未输入名称" << endl;
        return false;
    }
    data[number - 1].ISBnumber = number;
    data[number - 1].price = price;
    data[number - 1].name = name;
    qDebug() << "修改成功" << endl;
    return true;
}


//添加商品的编号,价格,名称
bool productUnit::addShop(int number, double price,QString name)
{
    if(number > maxSize)
    {
        overflowProcess();
        qDebug() << "!!!!!!!" << endl;
        qDebug() << "last" << last << endl;
    }
    if(number > last + 2)
    {
        qDebug() << "输入错误" << endl;
        return false;
    }
    if(price < 0.01 || name == "未输入名称")
    {
        qDebug() << "price < 0.01 || name == 未输入名称" << endl;
        return false;
    }
    data[number - 1].ISBnumber = number;
    data[number - 1].price = price;
    data[number - 1].name = name;
    qDebug() << "添加成功" << endl;
    last = last + 1;
    return true;
}







//返回商品种类数目
int productUnit::getShopNum()
{
    return last + 1;
}





//返回商品名称
QString productUnit::getName(int Isb)
{
    //编号从1开始而数组从零开始,故Isb应该减1
    if (Isb > last + 1)
        return  nullptr;
    return data[Isb - 1].name;
}


//返回商品编号为Isb的商品的价格
double productUnit::getSinglePrice(int Isb)
{
    if (Isb > last + 1)
        return  0.0;
    //编号从1开始而数组从零开始,故Isb应该减1
    return data[Isb - 1].price;
}


//商品数减一
void productUnit::ShopNumSubOne(int Isb)
{
    for(int j = Isb; j < last; j++)
        data[j] = data[j + 1];
    last--;
}
