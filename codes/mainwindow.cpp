#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QtDebug>
void MainWindow::createPoly(Poly &P,int swit)
{
    P = (Poly)malloc(sizeof(PolyNode));
    P->next = NULL;
    Poly p1, p2;
    p2 = (Poly)malloc(sizeof(PolyNode));
    double x;
    int y;
    QString str;
    if(swit==0)
        str = ui->firstEdit->text();
    else
        str = ui->secondEdit->text();
    qDebug()<<str;
    QString substr=str;
    int i=0;
    int len = str.length();
    while (!substr.isEmpty())
    {
        p1 = (Poly)malloc(sizeof(PolyNode));
        if (!P->next)
            P->next = p1;
        else
            p2->next = p1;
        p1->next = NULL;
        if(len==1)
        {
            p1->coef=p1->expn=0;
            qDebug()<<p1->coef<<" "<<p1->expn;
            p2=p1;
            break;
        }
        else
        {
            substr=str.section(' ',i,i);
            x=substr.toFloat();
            p1->coef = x;
            i++;
            substr=str.section(' ',i,i);
            y=substr.toInt();
            p1->expn = y;
            qDebug()<<p1->coef<<" "<<p1->expn;
            i++;
            p2 = p1;
            if(p1->coef==0&&p1->expn==0)
                break;
        }
    }
}
void MainWindow::sortPoly(Poly &P)
{
    Poly p, q, pre;
    p = P->next->next;
    P->next->next = NULL;
    while (p)
    {
        q = p->next;
        pre = P;
        while (pre->next != NULL && pre->next->expn > p->expn)
            pre = pre->next;
        p->next = pre->next;
        pre->next = p;
        p = q;
    }
}
void MainWindow::samePoly(Poly &P)
{
    Poly temp = P->next;
    while (temp)
    {
        if (temp->next)
        {
            Poly search = temp->next;
            while (search->expn == temp->expn)
            {
                temp->coef += search->coef;
                search->coef = 0;
                if (!search->next)
                    break;
                else
                    search = search->next;
            }
        }
        temp = temp->next;
    }
}
void MainWindow::funPoly(Poly P1, Poly P2, Poly &P3, int k) // 原来P1 P2 有引用
{
    Poly pa, pb, pc;
    pa = P1->next;
    pb = P2->next;
    P3 = pc = P1;
//	P3 = pc = (Poly)malloc(sizeof(PolyNode));
    Poly temp = P2->next;
    if (k)
    {
        while (temp)
        {
            temp->coef = -temp->coef;
            if (temp->next)
                temp = temp->next;
            else
                temp = NULL;
        }
    }
    while (pa&&pb)
    {
        if (pa->expn > pb->expn)
        {
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        }
        else if (pa->expn == pb->expn)
        {
            pa->coef = pa->coef + pb->coef;
            pc->next = pa;
            pc = pa;
            pa = pa->next;
            pb = pb->next;
        }
        else if (pa->expn < pb->expn)
        {
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
    }
    pc->next = pa ? pa : pb;
}
void MainWindow::showPoly(Poly P)
{
    Poly temp = P->next;
    int flag = 1;
    string display="";
    while (temp)
    {
        if (!temp->coef && !temp->next && flag)
            display = "0";
        if (temp->coef)
        {
//            display += to_string(temp->coef)+" "+to_string(temp->expn)+" ";
            if(temp->coef==1)
                display += "+x^"+to_string(temp->expn);
            else if (temp->coef==-1)
                display += "-x^"+to_string(temp->expn);
            else if (temp->coef>0)
                display += "+"+to_string(temp->coef)+"x^"+to_string(temp->expn);
            else
                display += to_string(temp->coef)+"x^"+to_string(temp->expn);
            flag = 0;
        }
        if (temp->next)
            temp = temp->next;
        else
            temp = NULL;
    }
    QString show = QString::fromStdString(display);
    if(show.startsWith("+"))
        show=show.mid(1);
    ui->textBrowser->setText(show);
}
double MainWindow::calPoly(Poly &P, double x)
{
    double sum = 0;
    Poly temp = P->next;
    while (temp)
    {
        sum += temp->coef*pow(x, temp->expn);
        if (temp->next)
            temp = temp->next;
        else
            temp = NULL;
    }
    return sum;
}
void MainWindow::deriPoly(Poly &P)
{
    Poly temp = P->next;
    while (temp)
    {
        temp->coef *= temp->expn;
        temp->expn--;
        if (temp->next)
            temp = temp->next;
        else
            temp = NULL;
    }
}
void MainWindow::multiPoly(Poly P1, Poly P2,Poly & multi)
{
    Poly p1, p2, p3, p4;
    p1 = P1->next;
    p2 = P2->next;
    multi = (Poly)malloc(sizeof(PolyNode));
    multi->next = NULL;
    p4 = (Poly)malloc(sizeof(PolyNode));
    while (p1)
    {
        while (p2)
        {
            p3 = (Poly)malloc(sizeof(PolyNode));
            if (multi->next == NULL)
                multi->next = p3;
            else
                p4->next = p3;
            p3->next = NULL;
            p3->coef = p1->coef*p2->coef;
            p3->expn = p1->expn + p2->expn;
            p4 = p3;
            if (p2->next)
                p2 = p2->next;
            else
                p2 = NULL;
        }
        if (p1->next)
            p1 = p1->next;
        else
            p1 = NULL;
        p2 = P2->next;
    }
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->firstEdit->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_calBtn_clicked()
{
    Poly P=(Poly)malloc(sizeof(PolyNode));
    createPoly(P,0);
    sortPoly(P);
    samePoly(P);
    double x;
    x=ui->xEdit->text().toFloat();
    QString display = QString("%1").arg(calPoly(P,x));
    ui->textBrowser->setText(display);
}

void MainWindow::on_deriBtn_clicked()
{
    Poly P=(Poly)malloc(sizeof(PolyNode));
    createPoly(P,0);
    sortPoly(P);
    samePoly(P);
    deriPoly(P);
    showPoly(P);
}


void MainWindow::on_addBtn_clicked()
{
    Poly P1=(Poly)malloc(sizeof(PolyNode));
    Poly P2=(Poly)malloc(sizeof(PolyNode));
    Poly ans=(Poly)malloc(sizeof(PolyNode));
    createPoly(P1,0);
    createPoly(P2,1);
    sortPoly(P1);
    sortPoly(P2);
    samePoly(P1);
    samePoly(P2);
    funPoly(P1,P2,ans,0);
    showPoly(ans);
}


void MainWindow::on_subBtn_clicked()
{
    Poly P1=(Poly)malloc(sizeof(PolyNode));
    Poly P2=(Poly)malloc(sizeof(PolyNode));
    Poly ans=(Poly)malloc(sizeof(PolyNode));
    createPoly(P1,0);
    createPoly(P2,1);
    sortPoly(P1);
    sortPoly(P2);
    samePoly(P1);
    samePoly(P2);
    funPoly(P1,P2,ans,1);
    showPoly(ans);
}


void MainWindow::on_multiBtn_clicked()
{
    Poly P1=(Poly)malloc(sizeof(PolyNode));
    Poly P2=(Poly)malloc(sizeof(PolyNode));
    Poly ans=(Poly)malloc(sizeof(PolyNode));
    createPoly(P1,0);
    createPoly(P2,1);
    sortPoly(P1);
    sortPoly(P2);
    samePoly(P1);
    samePoly(P2);
    multiPoly(P1,P2,ans);
    sortPoly(ans);
    samePoly(ans);
    showPoly(ans);
}


void MainWindow::on_clearBtn_clicked()
{
    ui->firstEdit->clear();
    ui->secondEdit->clear();
    ui->xEdit->clear();
    ui->textBrowser->clear();
    ui->firstEdit->setFocus();
}

