#ifndef CUSTOM_HASHMAP_HPP
#define CUSTOM_HASHMAP_HPP

#include <iostream>
using namespace std;

// Node class for the linked list implementation in each bucket
template<typename K, typename V>
class HashNode {
private:
    K key;
    V value;
    HashNode* next;
public:
    HashNode(const K& k, const V& v) {
        key = k;
        value = v;
        next = nullptr;
    }
    K get_key() { return key; }
    V get_value() { return value; }
    void set_value(const V& v) { value = v; }
    HashNode* get_next() { return next; }
    void set_next(HashNode* n) { next = n; }
};

// Class to handle the hashing functions
class HashFunction {
public:
    static unsigned long long hash_string(const string& key, unsigned long long prime) {
        unsigned long long hash_value = 5381;
        for(char c : key) {
            hash_value = ((hash_value << 5) + hash_value) + c;
            hash_value %= prime;
        }
        return hash_value;
    }

    static unsigned long long hash_int(long long key, unsigned long long prime) {
        if(key < 0) key = -key;
        return key % prime;
    }
};

template<typename K, typename V>
class custom_map {
private:
    static const unsigned long long INITIAL_SIZE = 16;
    static const unsigned long long PRIME_MOD = 1000000007;
    HashNode<K,V>** buckets;
    unsigned long long size;
    unsigned long long capacity;

    unsigned long long get_hash(const K& key) {
        if constexpr (is_same<K, string>::value) {
            return HashFunction::hash_string(key, PRIME_MOD) % capacity;
        } 
        else {
            return HashFunction::hash_int(key, PRIME_MOD) % capacity;
        }
    }

    void resize_map() {
        unsigned long long old_capacity = capacity;
        capacity *= 2;
        HashNode<K,V>** new_buckets = new HashNode<K,V>*[capacity]();
        
        for(unsigned long long i = 0; i < old_capacity; i++) {
            HashNode<K,V>* current = buckets[i];
            while(current != nullptr) {
                HashNode<K,V>* next = current->get_next();
                unsigned long long new_index = get_hash(current->get_key());
                current->set_next(new_buckets[new_index]);
                new_buckets[new_index] = current;
                current = next;
            }
        }
        delete[] buckets;
        buckets = new_buckets;
    }

public:
    custom_map() {
        size = 0;
        capacity = INITIAL_SIZE;
        buckets = new HashNode<K,V>*[capacity]();
    }

    vector<pair<K,V>> get_all_pairs() {
        vector<pair<K,V>> result;
        for(unsigned long long i = 0; i < capacity; i++) {
            HashNode<K,V>* current = buckets[i];
            while(current != nullptr) {
                result.push_back({current->get_key(), current->get_value()});
                current = current->get_next();
            }
        }
        return result;
    }

    void insert_key(const pair<K,V>& pair) {
        if(exists(pair.first)) {
            HashNode<K,V>* current = buckets[get_hash(pair.first)];
            while(current != nullptr) {
                if(current->get_key() == pair.first) {
                    current->set_value(pair.second);
                    return;
                }
                current = current->get_next();
            }
        }

        if(size >= capacity * 0.75) {
            resize_map();
        }

        unsigned long long index = get_hash(pair.first);
        HashNode<K,V>* new_node = new HashNode<K,V>(pair.first, pair.second);
        new_node->set_next(buckets[index]);
        buckets[index] = new_node;
        size++;
    }

    bool exists(const K& key) {
        unsigned long long index = get_hash(key);
        HashNode<K,V>* current = buckets[index];
        while(current != nullptr) {
            if(current->get_key() == key) {
                return true;
            }
            current = current->get_next();
        }
        return false;
    }

    V get_value(const K& key) {
        unsigned long long index = get_hash(key);
        HashNode<K,V>* current = buckets[index];
        while(current != nullptr) {
            if(current->get_key() == key) {
                return current->get_value();
            }
            current = current->get_next();
        }
        throw runtime_error("Key not found in the map");
    }

    ~custom_map() {
        for(unsigned long long i = 0; i < capacity; i++) {
            HashNode<K,V>* current = buckets[i];
            while(current != nullptr) {
                HashNode<K,V>* next = current->get_next();
                delete current;
                current = next;
            }
        }
        delete[] buckets;
    }
};

#endif // CUSTOM_HASHMAP_HPP