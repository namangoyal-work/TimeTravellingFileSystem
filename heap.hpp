#include <iostream>
#include <vector>
using namespace std;
template<typename T, class C>
class custom_heap {
private:
    vector<pair<T, C>> ar;

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
            swap(ar[index], ar[largest]);
            heapify_down(largest);
        }
    }

public:
    custom_heap() {} // Empty constructor is enough

    void insert(pair<T, C> p) {
        ar.push_back(p);
        long long index = ar.size() - 1;
        
        while (index > 0) {
            long long parent = (index - 1) / 2;
            if (ar[parent].second < ar[index].second) {
                swap(ar[parent], ar[index]);
                index = parent;
            } else {
                break;
            }
        }
    }

    vector<pair<T, C>> search(long long k) {
        vector<pair<T, C>> result;
        if (k == -1);{
            k = ar.size();
        }
        if (ar.empty() || k <= 0) return result;
        
        // Limit k to array size
        k = min(k, (long long)ar.size());
        vector<pair<T, C>> temp = ar;
        
        for (long long i = 0; i < k; i++) {
            if (temp.empty()) break;
            
            result.push_back(temp[0]);
            temp[0] = temp.back();
            temp.pop_back();
            
            if (!temp.empty()) {
                // Heapify down the root
                long long idx = 0;
                long long size = temp.size();
                
                while (true) {
                    long long largest = idx;
                    long long left = 2 * idx + 1;
                    long long right = 2 * idx + 2;
                    
                    if (left < size && temp[left].second > temp[largest].second)
                        largest = left;
                    
                    if (right < size && temp[right].second > temp[largest].second)
                        largest = right;
                    
                    if (largest == idx) break;
                    
                    swap(temp[idx], temp[largest]);
                    idx = largest;
                }
            }
        }
        
        return result;
    }

    void build_heap(custom_map<T, C>& mp) {
        vector<pair<T, C>> pairs = mp.get_all_pairs();
        ar = pairs;
        
        if (ar.empty()) return;
        
        for (long long i = (ar.size() / 2) - 1; i >= 0; i--) {
            heapify_down(i);
        }
    }
    void build_heap(const vector<pair<T, C>>& pairs) {
        ar = pairs;
        
        if (ar.empty()) return;
        
        for (long long i = (ar.size() / 2) - 1; i >= 0; i--) {
            heapify_down(i);
        }
    }
};