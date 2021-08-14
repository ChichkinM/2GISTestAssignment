/*
 * \file WordsProxyModel.h
 * \author : Chichkin M.A.
 * \date : 14.08.2021
 */

#pragma once

#include <QSortFilterProxyModel>
#include "WordsPrimaryModel.h"

namespace doublegis {
namespace model {

class WordsProxyModel : public QSortFilterProxyModel
{
Q_OBJECT
public:
    WordsProxyModel(WordsPrimaryModel *model, QObject *parent) noexcept;

protected:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const noexcept override;

};

}
}
