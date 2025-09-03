#include<iostream>
#include<string>
#include<vector>
#include<ctime>
#include"tree.hpp"
#include"heap.hpp"
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    custom_heap<string , time_t> time_tracker;  // Heap for getting the files sorted in the descending order on the basis of the last modification time !!  
    custom_map<string  , long long >number_of_nodes_tracker; 

    string inp;
    cin >>inp;
    int last_ele = 0;
    custom_map<string , Tree*> mp;
    while(inp!= "exit"){
        if (inp == "CREATE"){
            string filename;
            cin >> filename;
            filename.erase(0 ,1);
            filename.erase(filename.size() - 1 , 1);
            Tree* last_ele = new Tree;
            mp.insert_key({filename , last_ele});
            TreeNode* temp = last_ele->get_root();
            time_tracker.insert({filename , temp->get_created_timestamp()});
            
            
        }
        else if (inp == "READ"){
            string filename;
            cin >> filename;
                                    filename.erase(0 ,1);
            filename.erase(filename.size() - 1 , 1);
            cout << mp.get_value(filename)->read() << '\n';
        }
        else if (inp == "INSERT"){
            string filename , content;
            cin >> filename >> content;
                        filename.erase(0 ,1);
            filename.erase(filename.size() - 1 , 1);
                        content.erase(0 ,1);
            content.erase(content.size() - 1 , 1);
            time_t modification = mp.get_value(filename)->insert(content);
            time_tracker.insert({filename , modification});
        }
        else if (inp == "UPDATE"){
            string filename ,content;
            cin >> filename >> content;
                                    filename.erase(0 ,1);
            filename.erase(filename.size() - 1 , 1);
                        content.erase(0 ,1);
            content.erase(content.size() - 1 , 1);
            time_t modification = mp.get_value(filename)->update(content);
            time_tracker.insert({filename , modification});
        }
        else if (inp == "SNAPSHOT"){
            string filename , message;
            cin >> filename >>message;
                                    filename.erase(0 ,1);
            filename.erase(filename.size() - 1 , 1);
                        message.erase(0 ,1);
            message.erase(message.size() - 1 , 1);
            time_t modification  =  mp.get_value(filename)->set_snapshot(message);
            time_tracker.insert({filename , modification});
        }
        else if (inp == "ROLLBACK"){
            string filename;
            int version_id = -1;
            string version_id_str;
            cin >> filename >> version_id_str  ;
                                    filename.erase(0 ,1);
            filename.erase(filename.size() - 1 , 1);
            version_id_str.erase(0 , 1);
            version_id_str.erase(version_id_str.size() - 1  , 1);
            version_id = stoi(version_id_str); 
                       
            mp.get_value(filename)->rollback(version_id);

        }
        else if (inp == "HISTORY"){
            string filename;
            cin >> filename;
                                    filename.erase(0 ,1);
            filename.erase(filename.size() - 1 , 1);
                        
            vector<tuple<int , time_t , string>> history = mp.get_value(filename)->history();
            for(long long i = 0; i < history.size() ; i ++ ){
                char* dt_string  = ctime(&get<1>(history[i]));
                cout << get<0>(history[i]) << " " << dt_string <<" " <<get<2>(history[i]);
            
            cout << "\n";}

       
        }
        else if (inp == "RECENT_FILES"){
            string nums ;
            cin >> nums;
            nums.erase( 0 ,1);
            nums.erase(nums.size()- 1  , 1);
            long long number_of_files = stoi(nums);
            vector<pair<string , time_t>> recent_modifications = time_tracker.search(number_of_files);
            for(auto x : recent_modifications){cout << x.first << " " << x.second << "\n";}

        }
        else if (inp == "BIGGEST_TREES"){
                string nums ;
            cin >> nums;
            nums.erase( 0 ,1);
            nums.erase(nums.size()- 1  , 1);
            long long number_of_fiiles = stoi(nums);    
            custom_heap<string , long long  > biggest_trees;
            


        }
        cin >> inp;
    }
    return 0;
}