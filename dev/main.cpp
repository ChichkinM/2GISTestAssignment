#include <iostream>

#include "App.h"
#include "Metatypes.h"

int main(int argc, char *argv[])
{
    std::setlocale( LC_ALL, "en_US.UTF-8" );
    QCoreApplication::setAttribute( Qt::AA_EnableHighDpiScaling );
    doublegis::metatypes::registerTypes();

    doublegis::App app(argc, argv);
    app.run();
    return app.exec();
}
