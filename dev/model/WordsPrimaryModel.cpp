/*
 * \file WordsPrimaryModel.cpp
 * \author : Chichkin M.A.
 * \date : 14.08.2021
 */

#include "WordsPrimaryModel.h"
#include "parser/Types.h"

namespace doublegis {
namespace model {

WordsPrimaryModel::WordsPrimaryModel(QObject *parent) noexcept
        : QAbstractListModel(parent),
          maxCount(0)
{
}

void WordsPrimaryModel::update(
        parser::MostCommonWordsStorage newStorage) noexcept
{
    if (storage.size() < newStorage.size()) {
        storage.reserve(newStorage.size());
    }

    for (auto &&word : newStorage) {
        auto found = std::find_if(
                storage.begin(), storage.end(),
                [&word](const Entry &e) {
                    return e.word == word.second;
                });
        if (found != storage.end()) {
            if (found->count != word.first) {
                found->count = word.first;
                const auto index = std::distance(storage.begin(), found);
                auto currentIndex = createIndex(index, 0);
                emit dataChanged(currentIndex, currentIndex, {Role::Count});
                setMaxCount(word.first);
            }
            continue;
        }

        auto bound = std::lower_bound(
                storage.begin(), storage.end(), word,
                [](const Entry &e, const auto &word) {
                    if (e.count == word.first) {
                        return e.word < word.second;
                    }
                    return e.count > word.first;
                });

        const auto insertIndex = std::distance(storage.begin(), bound);
        beginInsertRows({}, insertIndex, insertIndex);
        storage.emplace(bound, Entry{std::move(word.second), word.first});
        endInsertRows();
        setMaxCount(word.first);

    }

    if(storage.size() > parser::constants::mostCommonWordsLimit) {
        beginRemoveRows({}, parser::constants::mostCommonWordsLimit, storage.size() );
        storage.resize(parser::constants::mostCommonWordsLimit);
        endRemoveRows();
    }
}

void WordsPrimaryModel::setMaxCount(quint64 newMaxCount) noexcept
{
    if(newMaxCount > maxCount) {
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
}

}
}
