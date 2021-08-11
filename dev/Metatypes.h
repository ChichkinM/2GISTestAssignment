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
    qRegisterMetaType<model::Domain*>();
}

}
