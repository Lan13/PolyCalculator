#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


typedef struct PolyNode
{
    double coef;
    int expn;
    struct PolyNode *next;
}PolyNode, *Poly;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void createPoly(Poly &P,int swit);
    void sortPoly(Poly &P);
    void samePoly(Poly &P);
    void funPoly(Poly P1, Poly P2, Poly &P3, int k);
    void showPoly(Poly P);
    double calPoly(Poly &P, double x);
    void deriPoly(Poly &P);
    void multiPoly(Poly P1, Poly P2,Poly & multi);
private slots:

    void on_calBtn_clicked();

    void on_deriBtn_clicked();

    void on_addBtn_clicked();

    void on_subBtn_clicked();

    void on_multiBtn_clicked();

    void on_clearBtn_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
