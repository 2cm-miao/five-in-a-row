#ifndef FIVE_CHESS_H
#define FIVE_CHESS_H

#include <QMainWindow>

namespace Ui {
class five_chess;
}

class five_chess : public QMainWindow
{
    Q_OBJECT

public:
    explicit five_chess(QWidget *parent = 0);
    ~five_chess();

    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void timerUpDate();

private:
    Ui::five_chess *ui;

    int a[16][16];
    int isWin(int,int);
    int judge_1(int,int);
    int judge_2(int,int);
    int judge_3(int,int);
    int judge_4(int,int);
    int player;
    int flag;
    int ans;
    int nut;

};

#endif // FIVE_CHESS_H
