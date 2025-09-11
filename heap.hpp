#ifndef CUSTOM_HEAP_HPP
#define CUSTOM_HEAP_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

template<typename T, class C>
class custom_heap {
private:
    vector<pair<T, C>> ar;
    unordered_map<T, long long> position_map; // Tracks position of each key in the heap

    void heapify_down(long long index) {
        long long size = ar.size();
        long long largest = index;
        long long left = 2 * index + 1;
        long long right = 2 * index + 2;
        
        if (left < size && ar[left].second > ar[largest].second) {
            largest = left;
        }
        
        if (right < size && ar[right].second > ar[largest].second) {
            largest = right;
        }
        
        if (largest != index) {
            swap_nodes(index, largest);
            heapify_down(largest);
        }
    }

    void heapify_up(long long index) {
        while (index > 0) {
            long long parent = (index - 1) / 2;
            if (ar[parent].second < ar[index].second) {
                swap_nodes(parent, index);
                index = parent;
            } else {
                break;
            }
        }
    }

    void swap_nodes(long long i, long long j) {
        // Update position map
        position_map[ar[i].first] = j;
        position_map[ar[j].first] = i;
        // Swap elements
        swap(ar[i], ar[j]);
    }

public:
    custom_heap() {}
    
    // Fix copy constructor to properly copy position_map
    custom_heap(const custom_heap& other) {
        ar = other.ar;
        position_map = other.position_map;
    }
    
    // Add assignment operator
    custom_heap& operator=(const custom_heap& other) {
        if (this != &other) {
            ar = other.ar;
            position_map = other.position_map;
        }
        return *this;
    }

    void insert(pair<T, C> p) {
        // Check if key already exists
        if (position_map.find(p.first) != position_map.end()) {
            // Update existing element
            long long pos = position_map[p.first];
            C old_value = ar[pos].second;
            ar[pos].second = p.second;
            
            // Reheapify based on whether value increased or decreased
            if (p.second > old_value) {
                heapify_up(pos);
            } else if (p.second < old_value) {
                heapify_down(pos);
            }
        } else {
            // Insert new element
            ar.push_back(p);
            position_map[p.first] = ar.size() - 1;
            heapify_up(ar.size() - 1);
        }
    }

    vector<pair<T, C>> search(long long k) {
        vector<pair<T, C>> result;
        if (ar.empty() || k == 0) return result;
        if (k == -1 || k > ar.size()) k = ar.size();        
        // Create a copy of the current heap's data
        vector<pair<T, C>> temp_ar = ar;
        unordered_map<T, long long> temp_map = position_map;
        
        // Extract k largest elements
        for (long long i = 0; i < k && !temp_ar.empty(); i++) {
            result.push_back(temp_ar[0]);
            temp_ar[0] = temp_ar.back();
            temp_ar.pop_back();
            if (!temp_ar.empty()) {
                long long idx = 0;
                while (true) {
                    long long largest = idx;
                    long long left = 2 * idx + 1;
                    long long right = 2 * idx + 2;
                    
                    if (left < temp_ar.size() && temp_ar[left].second > temp_ar[largest].second)
                        largest = left;
                    if (right < temp_ar.size() && temp_ar[right].second > temp_ar[largest].second)
                        largest = right;
                    
                    if (largest == idx) break;
                    
                    swap(temp_ar[idx], temp_ar[largest]);
                    idx = largest;
                }
            }
        }
        return result;
    }

    pair<T, C> extract_max() {
        if (ar.empty()) {
            throw runtime_error("Heap is empty");
        }

        pair<T, C> max_element = ar[0];
        position_map.erase(max_element.first);

        if (ar.size() > 1) {
            ar[0] = ar.back();
            position_map[ar[0].first] = 0;
        }
        
        ar.pop_back();
        
        if (!ar.empty()) {
            heapify_down(0);
        }

        return max_element;
    }


    bool empty() const {
        return ar.empty();
    }

    long long size() const {
        return ar.size();
    }
};

#endif // CUSTOM_HEAP_HPP