/*
 * \file WordsProxyModel.cpp
 * \author : Chichkin M.A.
 * \date : 14.08.2021
 */

#include "WordsProxyModel.h"
#include <optional>
#include <cassert>

namespace doublegis {
namespace model {

namespace {
template<typename T>
std::optional<T> convert(const QAbstractItemModel & model,
                         const QModelIndex & index, int role) noexcept
{
    auto data = model.data(index, role);
    if (!data.isValid() || !data.canConvert<T>()) {
        assert(false && "data is not valid");
        return {};
    }
    return data.value<T>();
}
}

WordsProxyModel::WordsProxyModel(
        WordsPrimaryModel *model, QObject *parent) noexcept
        : QSortFilterProxyModel(parent)
{
    setSourceModel(model);
    sort(0, Qt::AscendingOrder);
}

bool WordsProxyModel::lessThan(
        const QModelIndex & left, const QModelIndex & right ) const noexcept
{
    auto lExpectedWord = convert<QString>( *sourceModel(), left, WordsPrimaryModel::Word);
    auto rExpectedWord = convert<QString>( *sourceModel(), right, WordsPrimaryModel::Word);
    if(!lExpectedWord || !rExpectedWord) {
        return false;
    }

    return *lExpectedWord < *rExpectedWord;
}

}
}
