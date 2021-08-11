/*
 * \file App.h
 * \author : Chichkin M.A.
 * \date : 11.08.2021
 */

#pragma once

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "model/Domain.h"
#include "parser/Domain.h"

namespace doublegis {

class App : public QGuiApplication
{
Q_OBJECT
    Q_PROPERTY(doublegis::model::Domain *model MEMBER model CONSTANT)

public:
    App(int &argc, char **argv) noexcept;

private:
    QQmlApplicationEngine *const qmlEngine;
    parser::Domain *const parser;
    model::Domain *const model;
};

}
