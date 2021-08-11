/*
 * \file Domain.cpp
 * \author : Chichkin M.A.
 * \date : 11.08.2021
 */

#include "Domain.h"

#include <QDebug>

namespace doublegis::model {

Domain::Domain(parser::Domain &parser, QObject *parent) noexcept
        : QObject(parent),
          parser(parser)
{
}

void Domain::run() noexcept
{
    parser.run(url);
}

}