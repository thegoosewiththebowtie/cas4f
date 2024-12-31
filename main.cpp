#include "mainwindow.h"
#include <QStyleFactory>
#include <QApplication>
#include <QFontDatabase>
#include <QResource>
int main(int argc, char *argv[])
{
    srand (time (0));
    QApplication a(argc, argv);
    QSettings settings(QApplication::applicationDirPath() + "/config.ini", QSettings::IniFormat);
    if(settings.value("Mode").toString() == ""){
        settings.setValue("Mode", 2);
    }if(settings.value("Game").toString() == ""){
        settings.setValue("Game", 1);
    }if(settings.value("Balance").toString() == ""){
        settings.setValue("Balance", 0);
    }
    a.setStyle(QStyleFactory::create("WindowsVista"));
    QFontDatabase::addApplicationFont("qrc:/res/fnt/DSEG14Classic-Regular.ttf");
    MainWindow w;
    w.show();
    w.OpenGame();
    return a.exec();
}
