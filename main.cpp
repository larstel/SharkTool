#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/res/icons/res/icons/testIcon.ico"));

    //Splashscreen
    QSplashScreen *splash = new QSplashScreen();
    splash->setPixmap(QPixmap(":/res/res/shark_splash.png"));
    splash->show();
    MainWindow w;

    // splashscreen time
    QTimer::singleShot(3000,splash,SLOT(close()));
    QTimer::singleShot(3000,&w,SLOT(show()));

    //w.show();

    return a.exec();
}
