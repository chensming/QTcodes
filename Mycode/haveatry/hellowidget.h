#ifndef HELLOWIDGET_H
#define HELLOWIDGET_H
//hellowidget.h
//#include <QtWidgets/QWidget>
//#include <QtWidgets/QLabel>
#include <QWidget>
#include <QLabel>


class HelloWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HelloWidget(QWidget *parent = nullptr);
    ~HelloWidget();
    //label
    QLabel *m_labelInfo;
};

#endif
