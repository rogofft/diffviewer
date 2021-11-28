#include "mainwindow.h"
#include <QCommandLineParser>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCommandLineParser parser;
    parser.process(app);
    const QStringList args = parser.positionalArguments();

    MainWindow w(args);
    w.readSettings();
    w.show();
    return app.exec();
}
