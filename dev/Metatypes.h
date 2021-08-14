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
    qRegisterMetaType<doublegis::parser::MostCommonWordsStorage>(
            "doublegis::parser::MostCommonWordsStorage");
    qmlRegisterUncreatableType<model::Domain>("Status", 1, 0, "Status", "");
}

}
