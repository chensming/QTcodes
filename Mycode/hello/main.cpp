#include<QApplication>
#include<QWidget>  //窗口控件基类
#include<QPushButton>

int main(int argc,char **argv)
{
    QApplication app(argc,argv);

    QWidget w;
    w.setWindowTitle("计算器");//设置标题


    QPushButton b;
    b.setText("点我");//给按钮设置内容
    b.setParent(&w);//指定父对象
    b.move(100,100);//移动坐标

    /*
        如果不指定父对象，对象和对象（窗口与窗口）没有关系
        它们相互独立
        a指定b为它的父对象，a放在b的上面

    */


    QPushButton b1(&w);//通过构造函数传参
    b1.setText("abc");



    w.show();
    app.exec();
    return 0;
}
