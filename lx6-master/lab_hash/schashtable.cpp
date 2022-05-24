/**
 * @file schashtable.cpp
 * Implementation of the SCHashTable class.
 */

#include "schashtable.h"
#include <iostream>
using hashes::hash;
using std::list;
using std::pair;


template <class K, class V>
SCHashTable<K, V>::SCHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new std::list<std::pair<K, V>>[size];
    elems = 0;
}

template <class K, class V>
SCHashTable<K, V>::~SCHashTable()
{
    delete[] table;
}

template <class K, class V>
SCHashTable<K, V> const& SCHashTable<K, V>::
operator=(SCHashTable<K, V> const& rhs)
{
    if (this != &rhs) {
        delete[] table;
        table = new std::list<std::pair<K, V>>[rhs.size];
        for (size_t i = 0; i < rhs.size; i++)
            table[i] = rhs.table[i];
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template <class K, class V>
SCHashTable<K, V>::SCHashTable(SCHashTable<K, V> const& other)
{
    table = new std::list<std::pair<K, V>>[other.size];
    for (size_t i = 0; i < other.size; i++)
        table[i] = other.table[i];
    size = other.size;
    elems = other.elems;
}

/**
 * @todo Implement this function.
 *
 */
template <class K, class V>
void SCHashTable<K, V>::insert(K const& key, V const& value)
{
    size_t idx = hash(key, size);
    table[idx].push_front(pair<K, V>(key, value));
    elems++;
    if (shouldResize()) {
        resizeTable();
    }
}
/**
 * @todo Implement this function.
 *
 * Please read the note in the lab spec about list iterators and the
 * erase() function on std::list!
 */
template <class K, class V>
void SCHashTable<K, V>::remove(K const& key)
{
    typename std::list<std::pair<K, V>>::iterator it;
    size_t idx = hash(key, size);
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key) {
            table[idx].erase(it);
            break;
        }
    }
}
/**
 * @todo: Implement this function.
 */
template <class K, class V>
V SCHashTable<K, V>::find(K const& key) const
{
    size_t idx = hash(key, size);
    typename list<pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key) {
            return it->second;
        }
    }
    return V();
}

template <class K, class V>
V& SCHashTable<K, V>::operator[](K const& key)
{
    size_t idx = hashes::hash(key, size);
    typename std::list<std::pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return it->second;
    }

    // was not found, insert a default-constructed version and return it
    ++elems;
    if (shouldResize())
        resizeTable();

    idx = hashes::hash(key, size);
    std::pair<K, V> p(key, V());
    table[idx].push_front(p);
    return table[idx].front().second;
}

template <class K, class V>
bool SCHashTable<K, V>::keyExists(K const& key) const
{
    size_t idx = hashes::hash(key, size);
    typename std::list<std::pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return true;
    }
    return false;
}

template <class K, class V>
void SCHashTable<K, V>::clear()
{
    delete[] table;
    table = new std::list<std::pair<K, V>>[17];
    size = 17;
    elems = 0;
}
/**
 * @todo Implement this function.
 *
 * Please read the note in the spec about list iterators!
 * The size of the table should be the closest prime to size * 2.
 *
 * @hint Use findPrime()!
 */
template <class K, class V>
void SCHashTable<K, V>::resizeTable()
{
    typename std::list<std::pair<K, V>>::iterator it;
    size_t new_size = findPrime(size * 2);
    list<pair<K, V>>* new_table = new list<pair<K, V>>[new_size];
    for (size_t i = 0; i < size; i++) {
        for(it = table[i].begin(); it != table[i].end(); it++) {
            size_t idx = hash(it->first, new_size);
            pair<K, V> p(it->first, it->second);
            new_table[idx].push_front(p);
        }
    }
    size = new_size;
    delete[] table;
    table = new_table;
}
