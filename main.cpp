#include<iostream>
#include<string>
#include<vector>
#include<ctime>
#include"tree.hpp"
#include"heap.hpp"
#include<cctype>
using namespace std;
// Function to read a full line of input including spaces as a string
// Filenames are not allowed to have spaces in them 
string read_string_input() {
    string input;
    cin.ignore(); 
    getline(cin, input);
    return input;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    custom_map<string , time_t> time_tracker;  // Heap for getting the files sorted in the descending order on the basis of the last modification time !!  
    string inp;
    cout << "Welcome to the Time Travelling File System !! \n";
    cout << "The valid commands are : CREATE , READ , INSERT , UPDATE , SNAPSHOT , ROLLBACK , HISTORY , RECENT_FILES , BIGGEST_TREES \n";   
    cout << "Please enter your commands below : \n";
    cout << "Please enter 'exit' to exit the program !! \n";
    cout << "Please enter your command : ";
    cin >>inp;
    int last_ele = 0;
    custom_map<string , Tree*> mp;
    bool flag = 0;
    while(inp!= "exit" && inp != "EXIT" && inp!= "break" && inp!= "BREAK"){
        flag =0;
        // 10 to maintain constant time complexity for converting the input command to uppercase !!

        for(int i = 0 ; i < min(inp.size() , 10ul )  ; i++){
            inp[i] = toupper(inp[i]);
            
        }
        // Handling the inputs which demand creation of a new fiile with the given filename !! 
        if (inp == "CREATE"){
            // The command is a recognized as create command and hence flag = 1;
            flag = 1;
            // accepting the inputs in the format CREATE <filename>
            string filename;
            cin >> filename;
            // Checking if the input format is correct : 
        
            // Checking if the file with the same name already exists or not !! 
            if (mp.exists(filename)){
                cout << "File with the same name already exists !! Please try again with a different filename \n";
                cout << 
                "If you want to create a new file please use the CREATE command again with a new filename !! \n";
                cout << "Please enter your command : ";
                cin >> inp;
                continue;
            }
            // If the file with the same name does not exist , we create a new file with the given filename !!
            // We create a new tree for the file and insert it into the hashmap !!      
            Tree* last_ele = new Tree;
            // Inserting the new file into the hashmap with the filename as the key and the tree as the value !!
            mp.insert_key({filename , last_ele});
            TreeNode* temp = last_ele->get_root();
            time_tracker.insert_key({filename , temp->get_created_timestamp()});
            
            
        }
        else if (inp == "READ"){
           // The command is a recognized as read command and hence flag = 1; 
            flag = 1;

            //Getting the filename whose content is to be read  assumed without spaces !!
            string filename;
            cin >> filename;
            // Checking if the input format is correct : 
            /** 
             * We keep the loop and then we do not expect the user to write the CREATE in the command again but if they want to create a new file only the above format is accepted !! 
             **/

            // Checking if the file with the same name already exists or not !! 
            if (!mp.exists(filename)){
                cout << "File with the given name doesn't exist !! Please try again with a different filename \n";
                cout << 
                "If you want to read a file please use the READ command again with a correct filename !! \n";
                cout << "Please enter your command : ";
                cin >> inp;
                continue;
            }
            cout << mp.get_value(filename)->read() << '\n';
        }
        else if (inp == "INSERT"){
            // The command is a recognized as insert command and hence flag = 1;
            flag = 1;
            string filename , content;
            cin >> filename;
            content = read_string_input();
            // Checking if the input format is correct :
            if (!mp.exists(filename)){
                cout << "File with the given name doesn't exist !! Please try again with a different filename \n";
                cout << 
                "If you want to insert content into a file please use the INSERT command again with a correct filename !! \n";
                cout << "Please enter your command : ";
                cin >> inp;
                continue;
            }

            time_t modification = mp.get_value(filename)->insert(content);
            time_tracker.insert_key({filename , modification});
        }
        else if (inp == "UPDATE"){
            // The command is a recognized as update command and hence flag = 1;    
            flag = 1;
            string filename ,content;
            cin >> filename;
            content = read_string_input();
            // Checking if the input format is correct :
            if (!mp.exists(filename)){
                cout << "File with the given name doesn't exist !! Please try again with a different filename \n";
                cout << 
                "If you want to update content of a file please use the UPDATE command again with a correct filename !! \n";
                cout << "Please enter your command : ";
                cin >> inp;
                continue;
            }
                       
            time_t modification = mp.get_value(filename)->update(content);
            time_tracker.insert_key({filename , modification});
        }
        else if (inp == "SNAPSHOT"){
            // The command is a recognized as snapshot command and hence flag = 1;
            flag = 1;
            string filename , message;
            cin >> filename;
            message = read_string_input();
            // Checking if the input format is correct :
            if (!mp.exists(filename)){
                cout << "File with the given name doesn't exist !! Please try again with a different filename \n";
                cout << 
                "If you want to take a snapshot of a file please use the SNAPSHOT command again with a correct filename !! \n";
                cout << "Please enter your command : ";
                cin >> inp;
                continue;
            }
            // Assuming Snapshotting a file does not modify the file and hence we do not update the time_tracker heap !!
            time_t modification  =  mp.get_value(filename)->set_snapshot(message);
            //time_tracker.insert({filename , modification});
        }
        else if (inp == "ROLLBACK") {
    flag = 1;
    string filename;
    cin >> filename;
    if (!mp.exists(filename)){
        cout << "File with the given name doesn't exist !! Please try again with a different filename \n";
        cout << 
        "If you want to rollback a file please use the ROLLBACK command again with a correct filename !! \n";
        cout << "Please enter your command: ";
        cin >> inp;
        continue;
    }
    if (cin.peek() != '\n') { // Check if there's more input on the line
        string version_str;
        cin >> version_str;
        
        // Check if version_str contains only digits
        bool is_valid = true;
        for (char c : version_str) {
            if (!isdigit(c)) {
                is_valid = false;
                break;
            }
        }
        
        if (!is_valid) {
            cout << "Invalid version ID. Version ID must be a positive number.\n";
            cout << "Please enter your command: ";
            cin >> inp;
            continue;
        }
        
        long long version_id = stoi(version_str);
        if (version_id < 0 || version_id > mp.get_value(filename)->get_total_versions()) {
            cout << "Version ID out of range. Please enter a valid version ID.\n";
            cout << "Please enter your command: ";
            cin >> inp;
            continue;
        }
        mp.get_value(filename)->rollback(version_id);
    } else {
        // No version provided, rollback to previous version
        mp.get_value(filename)->rollback();
     }
     }
        else if (inp == "HISTORY"){
            // The command is a recognized as history command and hence flag = 1;
            flag = 1;
            string filename;
            cin >> filename;
            // Checking if the input format is correct :
            if (!mp.exists(filename)){
                cout << "File with the given name doesn't exist !! Please try again with a different filename \n";
                cout << 
                "If you want to see the history of a file please use the HISTORY command again with a correct filename !! \n";
                cout << "Please enter your command : ";
                cin >> inp;
                continue;
            }
                        
            vector<tuple<int , time_t , string>> history = mp.get_value(filename)->history();
            cout << "Version_id" << " " << "Snapshot_time"   << " "<< "message" << "\n"; 

            for(long long i = 0; i < history.size() ; i ++ ){
                char* dt_string  = ctime(&get<1>(history[i]));
                
                cout << get<0>(history[i]) << " " << dt_string <<" " <<get<2>(history[i]);
            
            cout << "\n";}
       
        }
        else if (inp == "RECENT_FILES"){
            // The command is a recognized as recent_files command and hence flag = 1;
            flag = 1;
            if (cin.peek() != '\n') { // Check if there's more input on the line
        string version_str;
        cin >> version_str;
            bool is_valid = true;
        for (char c : version_str) {
            if (!isdigit(c)) {
                is_valid = false;
                break;
            }
        }
                
        // Check if version_str contains only digits

        
        if (!is_valid ) {
            cout << "Invalid number of files. Number of files must be a positive integer.\n";
            cout << "Please enter your command: ";
            cin >> inp;
            continue;
        }

        long long number_of_files = stoi(version_str);
        if (number_of_files <= 0){
                cout << "Please enter a valid positive integer for the number of files !! \n";
                cout << "Please enter your command : ";
                cin >> inp;
                continue;
            }
            custom_heap<string , time_t> time_tracker2; 
            time_tracker2.build_heap(time_tracker) ;
            vector<pair<string , time_t>> recent_modifications = time_tracker2.search(number_of_files);
            if (recent_modifications.size() == 0){
                cout << "No files have been created yet !! Please create a file first using the CREATE command !! \n";
                cout << "Please enter your command : ";
                cin >> inp;
                continue;
            }
            // Printing the recent modifications
            cout << "The " << number_of_files << " most recently modified files are : \n";
            cout << "Filename" << " " << "Last Modified Time" << "\n";
            for(auto x : recent_modifications){
                char* dt_string  = ctime(&(x.second));cout << x.first << " " << dt_string << "\n";}
            if (recent_modifications.size() < number_of_files){
                cout << "Only " << recent_modifications.size() << " modifications are made so far !! \n";
            }

    
    }
        else{
            custom_heap<string , time_t> time_tracker2; 
            time_tracker2.build_heap(time_tracker) ;
            vector<pair<string , time_t>> recent_modifications = time_tracker2.search(-1);
            if (recent_modifications.size() == 0){
                cout << "No files have been created yet !! Please create a file first using the CREATE command !! \n";
                cout << "Please enter your command : ";
                cin >> inp;
                continue;
            }
            // Printing the recent modifications
        
            cout << "Filename" << " " << "Last Modified Time" << "\n";
            for(auto x : recent_modifications){
                char* dt_string  = ctime(&(x.second));cout << x.first << " " << dt_string << "\n";}
        }
         

        }
        else if (inp == "BIGGEST_TREES"){
            // The command is a recognized as biggest_trees command and hence flag = 1;
            flag = 1;
                        if (cin.peek() != '\n') { // Check if there's more input on the line
        string version_str;
        cin >> version_str;
            bool is_valid = true;
        for (char c : version_str) {
            if (!isdigit(c)) {
                is_valid = false;
                break;
            }
        }
                
        // Check if version_str contains only digits

        
        if (!is_valid ) {
            cout << "Invalid number of files. Number of files must be a positive integer.\n";
            cout << "Please enter your command: ";
            cin >> inp;
            continue;
        }
        
        long long number_of_files = stoi(version_str);  
            if (number_of_files <= 0){
                cout << "Please enter a valid positive integer for the number of files !! \n";
                cout << "Please enter your command : ";
                cin >> inp;
                continue;
            }
            custom_heap<string , long long  > biggest_trees;
            vector<pair<string , long long>> biggest_trees2;
           for(auto x : mp.get_all_pairs()){
               string filename = x.first;
               long long number_of_nodes = x.second->get_total_versions();
               biggest_trees2.push_back({filename , number_of_nodes});
           }
           biggest_trees.build_heap(biggest_trees2);
           vector<pair<string , long long>> largest_files = biggest_trees.search(number_of_files);
           if (largest_files.size() == 0){
                cout << "No files have been created yet !! Please create a file first using the CREATE command !! \n";
                cout << "Please enter your command : ";
                cin >> inp;
                continue;   }
              cout << "The " << number_of_files << " biggest trees are : \n";
              cout << "Filename" << " " << "Number of versions" << "\n";
              for(auto x : largest_files){
                  cout << x.first << " " << x.second + 1 << "\n";
              }
              if (largest_files.size() < number_of_files){
                cout << "Only " << largest_files.size() << " files have been created so far !! \n";
            } }
            else{
                custom_heap<string , long long  > biggest_trees;
            vector<pair<string , long long>> biggest_trees2;
           for(auto x : mp.get_all_pairs()){
               string filename = x.first;
               long long number_of_nodes = x.second->get_total_versions();
               biggest_trees2.push_back({filename , number_of_nodes});
           }
           biggest_trees.build_heap(biggest_trees2);
           vector<pair<string , long long>> largest_files = biggest_trees.search(-1);
           if (largest_files.size() == 0){
                cout << "No files have been created yet !! Please create a file first using the CREATE command !! \n";
                cout << "Please enter your command : ";
                cin >> inp;
                continue;   }
            
              cout << "Filename" << " " << "Number of versions" << "\n";
              for(auto x : largest_files){
                  cout << x.first << " " << x.second + 1 << "\n";
              } 
        }


        }
        if (flag == 0){
            cout << "Please enter a valid command !! \n";
            cout << "The valid commands are : CREATE , READ , INSERT , UPDATE , SNAPSHOT , ROLLBACK , HISTORY , RECENT_FILES , BIGGEST_TREES \n";
            }
            cout << "Please enter your command : ";
        cin >> inp;
    }
    return 0;
}