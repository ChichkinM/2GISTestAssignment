/*
 * \file Metatypes.h
 * \author : Chichkin M.A.
 * \date : 11.08.2021
 */

#pragma once

#include "model/Domain.h"

namespace doublegis::metatypes {

void registerTypes() noexcept
{
    qRegisterMetaType<model::Domain *>();
    qRegisterMetaType<doublegis::StatisticUpdatePtr>("doublegis::StatisticUpdatePtr");
    qmlRegisterUncreatableType<model::Domain>("Status", 1, 0, "Status", "");
}

}
