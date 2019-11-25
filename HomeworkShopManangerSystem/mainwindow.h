#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "productunit.h"
#include <QQueue>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_pushButtonfrontend_clicked();

    void on_pushButtonbackend_clicked();

    void on_pushButtonexit_clicked();

    void on_pushButtonAdd_clicked();

    void on_pushButtonVIP_clicked();

    void on_pushButtonCancel_clicked();

    void on_pushButtonFinish_clicked();

    void on_pushButtonSearch_clicked();

    void on_pushButtonShopType_clicked();

    bool on_pushButtonHAdd_clicked();

    void on_pushButtonHGet_clicked();

    void on_pushButtonHEdit_clicked();

    void on_pushButtonLook_clicked();

    bool on_pushButtonHDelete_clicked();

    void on_pushButtonReadFile_clicked();

    void on_pushButtonWriteFile_clicked();

    void on_pushButtonMakeEmtpy_clicked();

    void on_pushButton_clicked();

    void on_pushButtonBackToFront_clicked();

    void on_pushButtonLogin_clicked();

    void on_pushButtonLoginCancel_clicked();

private:
    Ui::MainWindow *ui;
    double totalPrice = 0;
    int shopNumber = 0;
    productUnit PU;
    QQueue<int> shoppingCart;
    QQueue<int> fenshu;
};

#endif // MAINWINDOW_H
