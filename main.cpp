#include "userdialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UserDialog w;
    w.show();
    return a.exec();
}
