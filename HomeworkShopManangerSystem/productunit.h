#ifndef PRODUCTUNIT_H
#define PRODUCTUNIT_H
#include <QString>


//默认仓库储存种类大小
const int defaultSize = 100;
//默认仓库种类扩充大小
const int increase = 20;


struct productType{
    //实际应用应该是一件商品一个特定编号，下面的整型商品编号只是为了简化
    int ISBnumber; // 商品编号
    double price; //商品价格
    QString name; //商品名称
};

//顺序表存储
class productUnit
{
public:
    //新建仓库
    productUnit(int sz = 50);
    //删除仓库
    ~productUnit();
//    备用！！！！删除商品种类
//    bool productDelete();
    //6.清空商品
    bool productMakeEmpty();
    //判断仓库是否已满
    bool IsFull() {return (last + 1 == maxSize) ? true : false;}
    //判断商品是否为空
    bool IsEmpty() {return (-1 == last) ? true : false;}
    //~~~~~从文件中写入商品信息到数组
    void readFile();
    //~~~~~将数组中的信息写入到文件中去
    void writeFile();
    //返回商品编号为Isb的商品的价格
    double getSinglePrice(int Isb);
    //返回商品名称
    QString getName(int Isb);
    //修改商品的编号,价格,名称
    bool setShop(int number, double price,QString name);
    //添加商品的编号,价格,名称
    bool addShop(int number, double price,QString name);
    //返回商品种类数目
    int getShopNum();
    void ShopNumSubOne(int Isb);


private:
    void overflowProcess();
    productType *data;
    int maxSize;
    int last; //初始值为-1
};


#endif // PRODUCTUNIT_H
