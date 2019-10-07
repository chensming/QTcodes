#ifndef SHOWVOID_H
#define SHOWVOID_H
#include <QObject>

class ShowVoid: public QObject
{
public:
    ShowVoid(QObject *parent = nullptr);
    ~ShowVoid();

signals:

public slots:
    //接收 SendVoid() 信号的槽函数
    void RecvVoid();


};

#endif // SHOWVOID_H
