/*
 * \file App.cpp
 * \author : Chichkin M.A.
 * \date : 11.08.2021
 */

#include "App.h"

#include <QDebug>
#include <QQmlContext>
#include <QQuickStyle>
#include <QQmlComponent>

namespace doublegis {

App::App(int &argc, char **argv) noexcept
        : QGuiApplication(argc, argv),
          qmlEngine(new QQmlApplicationEngine(this)),
          parser(new parser::Domain(this)),
          model(new model::Domain(*parser, this))
{
    qmlEngine->rootContext()->setContextProperty("doublegis", this);

    QQuickStyle::setStyle("Material");
    QQmlComponent component(qmlEngine, QUrl("qrc:/MainWindow.qml"));
    component.create();
    if (component.isError()) {
        qDebug() << component.errorString();
    }
}

}
