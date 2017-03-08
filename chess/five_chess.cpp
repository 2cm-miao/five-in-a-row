#include "five_chess.h"
#include "ui_five_chess.h"

#include <QPainter>
#include <QHoverEvent>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QtCore>

five_chess::five_chess(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::five_chess)
{
    ui->setupUi(this);

    resize(640,640);  //设置窗口大小
    memset(a,0,16*16*sizeof(int));
    player=0;
    ans=0;
    nut=0;
    flag=0;

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpDate()));
    timer->start(1000);
}

five_chess::~five_chess()
{
    delete ui;
}

void five_chess::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing,true);
    p.fillRect(rect(),Qt::white);  //背景颜色
    for(int i=0;i<16;i++)  //画16条横线
    {
        p.drawLine(20,20+i*40,460,20+i*40);
    }
    for(int i=0;i<12;i++)   //画12条竖线
    {
        p.drawLine(20+i*40,20,20+i*40,620);
    }



    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    for(int i=0;i<11;i++)  //竖行
    {
        for(int j=0;j<15;j++)  //横行
        {
            if(a[i][j]==1)    //如果是1就是黑棋
            {
                brush.setColor(Qt::black);
                p.setBrush(brush);
                p.drawEllipse(QPoint((i+1)*40,(j+1)*40),15,15);
            }
            else if(a[i][j]==2)   //如果是2就是白棋
            {
                brush.setColor(Qt::white);
                p.setBrush(brush);
                p.drawEllipse(QPoint((i+1)*40,(j+1)*40),15,15);
            }
        }
    }
}

void five_chess::mouseReleaseEvent(QMouseEvent *e)
{

    int x,y;
    if(e->x()>=20&&e->x()<620&&e->y()>=20&&e->y()<620)
    {
        x=(e->x()-20)/40;
        y=(e->y()-20)/40;
        if(!a[x][y])
        {
            a[x][y]=player++%2+1;
            if(flag==1)   //悔棋
            {
                a[x][y]=player++%2+1;
                flag=0;
            }
            ans=x;
            nut=y;
        }
        if(isWin(x,y))    //判断输赢
        {
            update();
            if(a[x][y]%2==0)  QMessageBox::information(this,tr("Win"),tr("White Win!"),QMessageBox::Ok);
            else  QMessageBox::information(this,tr("Win"),tr("Black Win!"),QMessageBox::Ok);
            on_pushButton_clicked();
        }
    }
    update();
}

int five_chess::isWin(int x,int y)
{
    return judge_1(x,y)||judge_2(x,y)||judge_3(x,y)||judge_4(x,y);
}


//判断棋子是否连成了五个
int five_chess::judge_1(int x,int y)    //判断纵向是否连成五个
{
    for(int i=0;i<5;i++)
    {
        if(y-i>=0&&
                y+4-i<=0xF&&
                a[x][y-i]==a[x][y+1-i]&&
                a[x][y-i]==a[x][y+2-i]&&
                a[x][y-i]==a[x][y+3-i]&&
                a[x][y-i]==a[x][y+4-i])
            return 1;
    }
    return 0;
}

int five_chess::judge_2(int x,int y)   //判断横向是否连成五个
{
    for(int i=0;i<5;i++)
    {
        if(x-i>=0&&
                x+4-i<=0xF&&
                a[x-i][y]==a[x+1-i][y]&&
                a[x-i][y]==a[x+2-i][y]&&
                a[x-i][y]==a[x+3-i][y]&&
                a[x-i][y]==a[x+4-i][y])
            return 1;
    }
    return 0;
}

int five_chess::judge_3(int x,int y)     //判断向右斜向是否连成五个
{
    for(int i=0;i<5;i++)
    {
        if(x-i>=0&&
                y-i>=0&&
                x+4-i<=0xF&&
                y+4-i<=0xF&&
                a[x-i][y-i]==a[x+1-i][y+1-i]&&
                a[x-i][y-i]==a[x+2-i][y+2-i]&&
                a[x-i][y-i]==a[x+3-i][y+3-i]&&
                a[x-i][y-i]==a[x+4-i][y+4-i])
            return 1;
    }
    return 0;
}

int five_chess::judge_4(int x,int y)    //判断向左斜向是否连成五个
{
    for(int i=0;i<5;i++)
    {
        if(x+i<=0xF&&
                y-i>=0&&
                x-4+i<=0xF&&
                a[x+i][y-i]==a[x-1+i][y+1-i]&&
                a[x+i][y-i]==a[x-2+i][y+2-i]&&
                a[x+i][y-i]==a[x-3+i][y+3-i]&&
                a[x+i][y-i]==a[x-4+i][y+4-i])
            return 1;
    }
    return 0;
}

void five_chess::on_pushButton_clicked()   //重新开始
{
    memset(a,0,16*16*sizeof(int));
    player=0;
    ans=0;
    nut=0;
    update();
}

void five_chess::on_pushButton_2_clicked()   //悔棋
{
    flag=1;
    a[ans][nut]=0;
    update();
}

void five_chess::timerUpDate()
{
    QDateTime time =QDateTime::currentDateTime();  //获取系统现在的时间
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");   //设置系统时间显示格式
    ui->label->setText(str);   //在标签上显示时间
}
