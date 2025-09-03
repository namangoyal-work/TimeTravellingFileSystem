#include <iostream>
#include<string>
#include<vector>
#include<ctime>
#include<map>
#include"custom_hashmap.hpp"

using namespace std;
class TreeNode{
private:
int version_id;
string content;
string message;
time_t created_timestamp;
time_t snapshot_timestamp;
TreeNode* parent;
bool is_snapshot;
vector<TreeNode*> children ; 
public : 
void set_version_id(int version_id){this->version_id = version_id;}
int get_version_id(){return version_id;}
string get_content(){return content;}
void set_content(string content){this->content = content;}
string get_message(){return message;}
void set_created_timestamp(time_t created_timestamp){this->created_timestamp = created_timestamp;}
time_t get_created_timestamp(){return created_timestamp;}
void set_snapshot_timestamp(time_t snapshot_timestamp){this->snapshot_timestamp = snapshot_timestamp;}
time_t get_snapshot_timestamp(){return snapshot_timestamp;}
void set_parent(TreeNode* parent){this->parent = parent;}
TreeNode* get_parent(){return parent;}
void set_children(vector<TreeNode* > children){this->children = children;}
vector<TreeNode*> get_children(){return children;}
TreeNode(){
    this->version_id = 0;
    this->content = "";
    this->message = "First version of the file (not currently marked as a snapshot)";
   this->is_snapshot = false;

}
void insert_content(string additional_content){content += additional_content;}
void update_content(string new_content ) {content = new_content;}
void set_snapshot(string message , time_t snapshot_timestamp){
    this->message = message;
    this->snapshot_timestamp = snapshot_timestamp;
    this->is_snapshot = true;
}
bool snapshot_status(){return is_snapshot;}

};

class Tree{
   private : 
   TreeNode* root;
   TreeNode* active_version;
   map<int , TreeNode*> version_map;
   int total_versions;
   public :
   Tree(){
    total_versions = 0;
    root = new TreeNode();
    active_version = root;
    version_map[1] = root;
    time_t current_time = time(NULL);
    root->set_created_timestamp(current_time);
   }
   TreeNode* get_root(){return root;}
   long long get_total_versions(){return total_versions;}
   string read(){
    return active_version->get_content();
   }
   time_t insert(string content){
    if (active_version->snapshot_status()){
        vector<TreeNode* > child = active_version->get_children();
        TreeNode* new_child = new TreeNode();
        new_child->set_version_id(total_versions +1 );
        new_child->set_content(content);
        new_child->set_parent(active_version) ;
        time_t current_time = time(NULL);
    new_child->set_created_timestamp(current_time);
        child.push_back(new_child);
        active_version->set_children(child);
        total_versions ++ ;
        version_map[total_versions] = new_child; 
        active_version = new_child;
        return current_time;
    }
    else{
        time_t current_time = time(NULL);
        active_version->insert_content(content);
        return current_time;
    }
    
    
   }
   time_t update(string content){
        if (active_version->snapshot_status()){
        vector<TreeNode* > child = active_version->get_children();
        TreeNode* new_child = new TreeNode();
        new_child->set_version_id(total_versions +1 );
        new_child->set_content(content);
        new_child->set_parent(active_version) ;
        time_t current_time = time(NULL);
    new_child->set_created_timestamp(current_time);
        child.push_back(new_child);
        active_version->set_children(child);
        total_versions++;
        version_map[total_versions] = new_child;
        active_version= new_child;
        return current_time;
    }
    else{
        active_version->update_content(content);
        time_t current_time = time(NULL);
        return current_time;
    } 
   }
   time_t set_snapshot(string message){
    time_t current_time = time(NULL);
    
    active_version->set_snapshot( message , current_time );
    return current_time;
   }
   void rollback(int version_id  = -1){
    if (version_id == -1){
        active_version = active_version->get_parent();
    }
    else{
        active_version = version_map[version_id];
    }
   }
   vector<tuple<int , time_t , string>> history(){
    vector<tuple<int , time_t , string>> his; 
    for(auto x : version_map){
        if (x.second->snapshot_status()){
            his.push_back({x.first , x.second->get_created_timestamp() , x.second->get_message()});
            
        }
        
    }
    return his;    
   } 
   ~Tree(){
    for(auto x : version_map){
        delete x.second;
    }
   }



};