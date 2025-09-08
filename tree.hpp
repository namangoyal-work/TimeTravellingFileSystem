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
void set_snapshot_status(bool is_snapshot){this->is_snapshot = is_snapshot;}
void set_message(string message){this->message = message;}
bool snapshot_status(){return is_snapshot;}

};

class Tree {
private:
    TreeNode* root;
    TreeNode* active_version;
    custom_map<int, TreeNode*> version_map;  // Changed from map to custom_map
    int total_versions;

public:
    // Constructor of Tree class initializing root and active_version , runs whenever a new file is created 
    /**
     * Constructor to initialize the Tree with a root node.
     * The root node is created with version_id 0, current timestamp,
     * and is marked as a snapshot by default.
     * The root node is also added to the version_map.
     */
    Tree() {
        total_versions = 0;
        root = new TreeNode();
        active_version = root;
        version_map.insert_key({0, root});  // Changed from [] to insert_key
        time_t current_time = time(NULL);
        root->set_created_timestamp(current_time);
        root->set_version_id(0);
        root->set_snapshot_status(true);
        root->set_message("First version of the file (marked as a snapshot by default)");
        root->set_snapshot_timestamp(current_time); 
    }

    TreeNode* get_root() { return root; }
    long long get_total_versions() { return total_versions; }
    string read() { return active_version->get_content(); }

    // ...existing insert() and update() methods remain the same...
    time_t set_snapshot(string message) {
        time_t current_time = time(NULL);
        active_version->set_snapshot(message, current_time);
        return current_time;
    }
    void rollback(int version_id = -1) {
        if (version_id == -1) {
            active_version = active_version->get_parent();
        }
        else {
            // Changed to use get_value instead of []
            if (version_map.exists(version_id)) {
                active_version = version_map.get_value(version_id);
            }
        }
    }

vector<tuple<int, time_t, string>> history() {
       vector<tuple<int, time_t, string>> his;
    TreeNode* current = active_version;
    
    // Traverse up from active_version to root
    while(current != nullptr) {
        if(current->snapshot_status()) {
            his.push_back({
                current->get_version_id(),
                current->get_snapshot_timestamp(),
                current->get_message()
            });
        }
        current = current->get_parent();
    }
    
    return his;
}
    // Inserts the given content into the active version of the file according to the rules specified -:
    /**
     *  If the given version is not a snapshot we just append the content to the current active version
     *  If the given version is a snapshot we create a new child node of the current active version and make that the active version
     *  We also update the total_versions and add the new version to the version_map
     *  We return the timestamp of the modification made as this is used in our heap to keep track of the most recently modified files  
     **/ 
    
    
    time_t insert(string content) {
        // Checks if the active version is a snapshot or not 
        if (active_version->snapshot_status()) {
            // If it is a snapshot we create a new child node and make that the active version
            vector<TreeNode*> child = active_version->get_children();
            TreeNode* new_child = new TreeNode();
            new_child->set_version_id(total_versions + 1);
            new_child->set_content(active_version->get_content() + content);
            new_child->set_parent(active_version);
            time_t current_time = time(NULL);
            new_child->set_created_timestamp(current_time);
            child.push_back(new_child);
            active_version->set_children(child);
            total_versions++;
            version_map.insert_key({total_versions, new_child});  
            active_version = new_child;
            return current_time;
        }
        else {
            // If it is not a snapshot we just append the content to the current active version !!
            time_t current_time = time(NULL);
            active_version->insert_content(content);
            return current_time;
        }
    }

    time_t update(string content) {
        if (active_version->snapshot_status()) {
            vector<TreeNode*> child = active_version->get_children();
            TreeNode* new_child = new TreeNode();
            new_child->set_version_id(total_versions + 1);
            new_child->set_content(content);
            new_child->set_parent(active_version);
            time_t current_time = time(NULL);
            new_child->set_created_timestamp(current_time);
            child.push_back(new_child);
            active_version->set_children(child);
            total_versions++;
            version_map.insert_key({total_versions, new_child});  // Changed from [] to insert_key
            active_version = new_child;
            return current_time;
        }
        else {
            active_version->update_content(content);
            time_t current_time = time(NULL);
            return current_time;
        }
    }

    ~Tree() {
        // Since custom_map doesn't support range-based for loop,
        // we'll iterate through version numbers we know exist
        for (int i = 1; i <= total_versions + 1; i++) {
            if (version_map.exists(i)) {
                delete version_map.get_value(i);
            }
        }
    }
};