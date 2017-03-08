#include "five_chess.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    five_chess w;
    w.show();

    return a.exec();
}
