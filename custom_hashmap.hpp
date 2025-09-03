#include<iostream>
#include <vector>
#include<string>
#include<type_traits>
#include<utility>
#include<stdexcept>
#include<cmath>
using namespace std;
unsigned long long list_of_primes[] = 
{187091ul, 202409ul, 218971ul, 236897ul,
    256279ul, 277261ul, 299951ul, 324503ul, 351061ul, 379787ul,
    410857ul, 444487ul, 480881ul, 520241ul, 562841ul, 608903ul,
    658753ul, 712697ul, 771049ul, 834181ul, 902483ul, 976369ul,
    1056323ul};



    // The above list of primes will be used to compute the compression if it gets too large we move on to the next prime in the list !! 

//implementing the node class for the linked list as it store (key,value) pairs;
template<typename T  , class C>
class node{
    private:
        T key;
        C val;
        node* ptr ;
    public :
    //constructor initliazes the values of the key and value from p and sets the next pointer to null intially!! 
    node(pair<T , C> p){
            tie(key ,val) = p;
            ptr = nullptr;
        }
    node(){
        ptr = nullptr;
    }
    T get_key(){
        return key;
    }
    C get_val(){
        return val;
    }
    void set_key(T key){
        this->key = key;
    }
    void set_val(C val){
        this->val = val;
    }
    node* get_ptr(){
        return ptr;
    }
    void set_ptr(node* ptr){
        this->ptr = ptr;
    }

};

template<typename T , class C>
class linked_list{
    private:
    node<T , C>* head ;
    int length;
    public:
    linked_list(){
        head = nullptr;
        length = 0;
    }
    int get_length(){return length;}
    node<T ,C>* get_head(){return head;}
    void set_length(int length){this->length = length;}
    void set_head(node<T , C>* head){this->head = head;}
    void insert(pair<T , C>p ){
        node<T , C>* curr = head; 
        while(curr->ptr != nullptr){
            curr = curr->ptr;
        }
        node<T  ,C>* temp = new node<T , C>(p);
        curr->ptr = temp;
        

    }
    


};







//Implementing the custom hash function currently only on string and int 
template<typename T>

   unsigned long long  custom_hash(unsigned long long prime ,T key){
        // custom hash for integral keys  
        if constexpr (std :: is_integral<T> :: value){
            return key % prime; 
        }
        // custom hash for string keys
        else if constexpr (std :: is_same<T , string> :: value ){
            // implementing the encoder logic so checking if size is greater or less than 8  
            if (key.length() >= 9){
                
                int idx = 0;
                long long initial_prod = 1;
                unsigned long long total = 0;
                while(idx < key.length() ){
                    int temp_counter = 0;
                    unsigned long  long temp_total = 0;
                    if (key.length() - idx -1 >=8 ){
                        while(temp_counter <= 8){
                            temp_counter ++ ;
                            temp_total += key[idx];
                            idx ++ ;
                        }
                        total +=   ((initial_prod )* temp_total ) % prime ;
                        initial_prod *= 33 ;
                        initial_prod %= prime;
                    }
                    else{
                            while(idx < key.length()){
                            temp_counter ++ ;
                            temp_total += key[idx];
                            idx ++ ;
                        }
                        total +=  ( initial_prod * temp_total ) % prime ;
                        total %= prime;
                        initial_prod *= 33 ;
                        initial_prod %= prime;
                    }
                }
                return total  % prime;
            }
            else{
                long long initial_prod = 1;
                int idx = 0;
                unsigned long long total = 0;
                while(idx < key.length()){
                    total += initial_prod  * key[idx];
                    idx ++ ;
                    total %= prime;
                    initial_prod *= 33;
                    initial_prod %= prime;
                }
                return total % prime;
            }
        }
    }

template<typename T , class C>
class custom_map {
    private :
    int idx_list_of_primes ;
    vector<node<T , C>*> arr;
    vector<long long > filled;
  
    public :
         custom_map(){
        idx_list_of_primes = 0;
        arr.resize(200000 , nullptr);

    }
    void insert_key(pair<T , C> p){
        unsigned long long key = custom_hash(list_of_primes[idx_list_of_primes] , p.first);
        {
            
            if (arr[key] == nullptr){  node<T , C>* temp = new node<T , C>(p);
            arr[key] = temp;return ;} 
            node<T , C>* curr = arr[key];
            while(curr->get_ptr() != nullptr ){
                curr = curr->get_ptr();
            } 
            node<T  ,C>* temp = new node<T , C>(p);
            curr->set_ptr(temp);
            filled.push_back(key);
            return ; 

        }
       
    }
    bool exists(T val){
        unsigned long long key = custom_hash(list_of_primes[idx_list_of_primes] , val);
        bool flag = 0;
            node<T  , C>* curr = arr[key];
            if (curr == nullptr){return flag;}
          while(curr->get_key() != val ){
                curr = curr->get_ptr();
            flag =0;
            if (curr->get_key()  ==val){flag = 1;break;}
            } 
            return flag;
            

             

        }
    
    C get_value(T val){
          unsigned long long key = custom_hash(list_of_primes[idx_list_of_primes],val);
        bool flag = 0;
            node<T , C>* curr = arr[key];
            if (curr == nullptr){throw runtime_error("The given key does not have an associated value");}
          while(curr->get_key() != val ){
                curr = curr->get_ptr();
            flag =0;
            if (curr->get_key()  ==val){flag = 1;break;}
            } 
        if (flag != 0){
            return curr->get_val();
        }
            
       
    }
    vector<long long > * begin(){return filled.begin();}
    vector<long long >* end(){return filled.end();}
    
    


    //map with vector of size (2 * 10^ 5 ) with 6 nodes in the linked list provides constant time look up 


    
};
    

























