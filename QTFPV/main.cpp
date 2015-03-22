#include "videodialog.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    videoDialog v;
    QGst::init(&argc, &argv);

    v.show();
    printf("Executed constructor\n");

    return a.exec();
}
