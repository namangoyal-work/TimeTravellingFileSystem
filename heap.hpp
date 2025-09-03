#include <iostream>
using namespace std;
template<typename T , class C>
class custom_heap{
    private:
    vector<pair<T , C> >  ar;
    public  : 
    custom_heap (){
        vector<pair<T , C>> ar;
    }
    void insert(pair<T , C> p){
        ar.push_back(p);
        long long key = p.second;
        long long index = ar.size() - 1;
        long long parent = (ar.size() - 1) / 2;
        while(ar[parent].second <  key ){
            ar[index]= ar[parent];
            ar[parent] = p;
            index = parent;
            parent = (index - 1) / 2;
        }

    }



    //  Returns the largest k elements in the heap !!
    vector<pair<T, C > > search(long long k){
        vector<pair<T, C> > ans;
        if (k == 0){return ans; }
            while(k != 0 ){
        k --;
        ans.push_back(ar[0]);
        ar[0 ]=  ar[ar.size() - 1];
        ar[ar.size() - 1] = ans[ans.size() - 1];
        ar.pop_back(); 
        long long key = ar[0].second;
        long long index = 0;
        long long child1 = 2*index + 1 ;
        long long child2 = 2*index + 2;
        while(ar[child1].second >  key  || ar[child2].second  > key ){
            if (ar[child1].second > ar[child2].second) {
                pair<T,C> p2 = ar[child1];
                ar[child1] = ar[index]; 
                ar[index]= p2; 
                index = child1;
                

            }
            else{
                 pair<T,C> p2 = ar[child2];
                ar[child2] = ar[index]; 
                ar[index]= p2;
                index = child2;
            }
            child1 = 2*index + 1;
            child2 = 2*index + 2; 
            
            
        }        
        
     }
    for(long long i = 0 ; i  < ans.size() ; i ++ ){
        // inserting the ith pair back to the heap 
        pair<T , C>p  = ans[i]; 
        ar.push_back(p);
        long long key = p.second;
        long long index = ar.size() - 1;
        long long parent = (ar.size() - 1) / 2;
        while(ar[parent].second <  key ){
            ar[index]= ar[parent];
            ar[parent] = p;
            index = parent;
            parent = (index - 1) / 2;
        }

    }
    return ans;

        
    }
    vector<pair<T, C>> heapify(vector<pair<T , C>> ar){
        long long index = ar.size() - 1;
        while(index != 0){
            long long copy_index = index;
            long long child1 = 2*index + 1;
            long long child2 = 2*index + 2;
            while(child1 < ar.size()-  1 ){
                long long mx = ar[child1].second;
                if (child2 < ar.size() - 1) {
                    mx = max(mx ,ar[child2].second);

               }
               if (mx > ar[child1].second){
                // we are processing from child2 end ;
                pair<T  ,C> temp = ar[child2];
                ar[child2] = ar[index];
                ar[index] = temp;
                copy_index = child2;
               }
               else{
                // we are processing from chil1d end !! 
                pair<T  ,C> temp = ar[child1];
                ar[child1] = ar[index];
                ar[index] = temp;
                copy_index = child1;
               }
               child1 = 2 * copy_index   +1;
               child2 = 2 * copy_index  + 2;
               
               
           
               
            }
            index --;
        }
        return ar;

    }


};