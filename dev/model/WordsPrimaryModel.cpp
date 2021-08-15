/*
 * \file WordsPrimaryModel.cpp
 * \author : Chichkin M.A.
 * \date : 14.08.2021
 */

#include "WordsPrimaryModel.h"
#include <QDebug>

namespace doublegis {
namespace model {

WordsPrimaryModel::WordsPrimaryModel(QObject *parent) noexcept
        : QAbstractListModel(parent),
          maxCount(0)
{
}

void WordsPrimaryModel::update( parser::MostCommonWordsStorage newStorage) noexcept
{
    if (storage.size() < newStorage.size()) {
        storage.reserve(newStorage.size());
    }

    for (auto it = storage.begin(); it != storage.end();) {
        const auto &entry = *it;
        auto found = std::find_if(newStorage.begin(), newStorage.end(),
                                  [&entry](const parser::WordAndCount &word) {
                                      return word.word == entry.word;
                                  });
        if (found == newStorage.end()) {
            const auto index = std::distance(storage.begin(), it);
            beginRemoveRows({}, index, index);
            it = storage.erase(it);
            endRemoveRows();
        } else {
            ++it;
        }
    }

    for (auto &&word : newStorage) {
        auto found = std::find_if(
                storage.begin(), storage.end(),
                [&word](const auto &e) {
                    return e.word == word.word;
                });
        if (found != storage.end()) {
            if (found->count != word.count) {
                found->count = word.count;
                const auto index = std::distance(storage.begin(), found);
                auto currentIndex = createIndex(index, 0);
                emit dataChanged(currentIndex, currentIndex, {Role::Count});
                setMaxCount(word.count);
            }
            continue;
        }

        setMaxCount(word.count);
        auto bound = std::lower_bound(storage.begin(), storage.end(), word);
        const auto insertIndex = std::distance(storage.begin(), bound);
        beginInsertRows({}, insertIndex, insertIndex);
        storage.emplace(bound, std::move(word));
        endInsertRows();
    }
}

void WordsPrimaryModel::setMaxCount(quint64 newMaxCount) noexcept
{
    if (newMaxCount > maxCount) {
        maxCount = newMaxCount;
        emit maxCountChanged();
    }
}

int WordsPrimaryModel::rowCount(const QModelIndex &) const noexcept
{
    return static_cast< int >( storage.size());
}

QVariant WordsPrimaryModel::data(const QModelIndex &index, int role) const noexcept
{
    if (index.row() < 0 || index.row() >= storage.size()) {
        return {};
    }

    const auto &entry = storage.at(index.row());
    switch (role) {
        case Role::Word:
            return entry.word;
        case Role::Count:
            return entry.count;
        default: {
            assert(false && "unknown role");
            return {};
        }
    }
}

QHash<int, QByteArray> WordsPrimaryModel::roleNames() const noexcept
{
    return {{Role::Word,  "word"},
            {Role::Count, "count"}};
}

quint64 WordsPrimaryModel::getMaxCount() const noexcept
{
    return maxCount;
}

void WordsPrimaryModel::clear() noexcept
{
    beginResetModel();
    storage.clear();
    endResetModel();

    maxCount = 0;
    emit maxCountChanged();
}

}
}
