#include "showvoid.h"
#include <QMessageBox>

ShowVoid::ShowVoid(QObject *parent) : QObject(parent)
{

}

ShowVoid::~ShowVoid()
{

}

//槽函数，弹窗
void ShowVoid::RecvVoid()
{
    QMessageBox::information(nullptr,tr("show"),tr("Just for void "));
}
