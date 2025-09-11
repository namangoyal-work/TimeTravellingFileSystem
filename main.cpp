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
// Helper function to convert string to uppercase
string to_upper(const string& str) {
    string upper = str;
    transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
    return upper;
}

// Helper function to trim leading spaces
string trim_leading_spaces(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos) return "";
    return str.substr(first);
}

// Modify read_string_input to handle leading spaces
string read_string_input() {
    string input;
    cin.ignore(); 
    getline(cin, input);
    return trim_leading_spaces(input);
}

int main() {
    custom_heap<string, time_t> recent_files_heap;
    custom_heap<string, long long> biggest_trees_heap;
    
    custom_map<string, Tree*> mp;
    
    string inp;
    bool flag = 0;
    
    cout << "Welcome to the Time Travelling File System !! \n";
    cout << "The valid commands are : CREATE , READ , INSERT , UPDATE , SNAPSHOT , ROLLBACK , HISTORY , RECENT_FILES , BIGGEST_TREES \n";   
    cout << "Please enter your commands below : \n";
    cout << "Please enter 'exit' to exit the program !! \n";
    cout << "Please enter your command : ";
    cin >>inp;
    int last_ele = 0;

    while(inp != "exit" && inp != "EXIT" && inp != "break" && inp != "BREAK") {
        flag = 0;
        
        // Convert input to uppercase for comparison
        string upper_inp = to_upper(inp);

        if (upper_inp == "CREATE"){
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
            mp.insert_key({filename, last_ele});
            TreeNode* temp = last_ele->get_root();
            time_t creation_time = temp->get_created_timestamp();
            
            // Update both heaps
           
            recent_files_heap.insert({filename, creation_time});
            biggest_trees_heap.insert({filename, 0}); // New file has 1 version (0 additional versions)
        }
        else if (upper_inp == "READ"){
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
        else if (upper_inp == "INSERT"){
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
            if (mp.get_value(filename)->read().size() > 0) {
               content = " " + content; 
            }
            time_t modification = mp.get_value(filename)->insert(content);
            
            
            // Update both heaps
            recent_files_heap.insert({filename, modification});
            biggest_trees_heap.insert({filename, mp.get_value(filename)->get_total_versions()});
        }
        else if (upper_inp == "UPDATE"){
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
                       
            // Update both heaps
            recent_files_heap.insert({filename, modification});
            biggest_trees_heap.insert({filename, mp.get_value(filename)->get_total_versions()});
        }
        else if (upper_inp == "SNAPSHOT"){
            // The command is a recognized as snapshot command and hence flag = 1;
            flag = 1;
            string filename;
            cin >> filename;
            string message = read_string_input();
    
            if (!mp.exists(filename)) {
                cout << "File with the given name doesn't exist!\n";
                cout << "If you want to take a snapshot of a file please use the SNAPSHOT command again with a correct filename!\n";
                cout << "Please enter your command: ";
                cin >> inp;
                continue;
            }
            time_t modification = mp.get_value(filename)->set_snapshot(message);
        }
        else if (upper_inp == "ROLLBACK") {
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
        else if (upper_inp == "HISTORY"){
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
        else if (to_upper(inp) == "RECENT_FILES") {
            // The command is a recognized as recent_files command and hence flag = 1;
            flag = 1;
            string rest_of_line;
            getline(cin, rest_of_line);
            rest_of_line = trim_leading_spaces(rest_of_line);

            // Always get all modifications first
            vector<pair<string, time_t>> recent_modifications = recent_files_heap.search(-1);
            
            if (recent_modifications.empty()) {
                cout << "No files have been created yet!\n";
                cout << "Please enter your command: ";
                cin >> inp;
                continue;
            }

            if (!rest_of_line.empty()) {
                // If a number was provided, only show that many entries
                bool is_valid = all_of(rest_of_line.begin(), rest_of_line.end(), ::isdigit);
                if (!is_valid) {
                    cout << "Invalid number of files. Number of files must be a positive integer.\n";
                    cout << "Please enter your command: ";
                    cin >> inp;
                    continue;
                }

                long long number_of_files = stoll(rest_of_line);
                if (number_of_files <= 0) {
                    cout << "Please enter a valid positive integer for the number of files!\n";
                    cout << "Please enter your command: ";
                    cin >> inp;
                    continue;
                }
                
                cout << "The " << number_of_files << " most recently modified files are:\n";
                if (number_of_files < recent_modifications.size()) {
                    recent_modifications.resize(number_of_files);
                }
            } else {
                cout << "All modified files in order of recency:\n";
            }
            
            cout << "Filename Last Modified Time\n";
            for (const auto& x : recent_modifications) {
                char* dt_string = ctime(&(x.second));
                cout << x.first << " " << dt_string;
            }
        }

        else if (to_upper(inp) == "BIGGEST_TREES") {
            // The command is a recognized as biggest_trees command and hence flag = 1;
            flag = 1;
            string rest_of_line;
            getline(cin, rest_of_line);
            rest_of_line = trim_leading_spaces(rest_of_line);

            
            vector<pair<string, long long>> largest_files = biggest_trees_heap.search(-1);
            
            if (largest_files.empty()) {
                cout << "No files have been created yet!\n";
                cout << "Please enter your command: ";
                cin >> inp;
                continue;
            }

            if (!rest_of_line.empty()) {
                // If a number was provided, only show that many entries
                bool is_valid = all_of(rest_of_line.begin(), rest_of_line.end(), ::isdigit);
                if (!is_valid) {
                    cout << "Invalid number of files. Number of files must be a positive integer.\n";
                    cout << "Please enter your command: ";
                    cin >> inp;
                    continue;
                }

                long long number_of_files = stoll(rest_of_line);
                if (number_of_files <= 0) {
                    cout << "Please enter a valid positive integer for the number of files!\n";
                    cout << "Please enter your command: ";
                    cin >> inp;
                    continue;
                }
                
                cout << "The " << number_of_files << " biggest trees are:\n";
                if (number_of_files < largest_files.size()) {
                    largest_files.resize(number_of_files);
                }
            } else {
                cout << "All files sorted by number of versions:\n";
            }
            
            cout << "Filename Number of versions\n";
            for (const auto& x : largest_files) {
                cout << x.first << " " << x.second + 1 << "\n";
            }
        }
        if (flag == 0){
            cout << "Please enter a valid command !! \n";
            cout << "The valid commands are : CREATE , READ , INSERT , UPDATE , SNAPSHOT , ROLLBACK , HISTORY , RECENT_FILES , BIGGEST_TREES \n";
            }
            cout << "Please enter your command : ";
        cin >> inp;
    }

    // Free Dynamically Allocated Memory
    for(const auto& pair : mp.get_all_pairs()) {
        delete pair.second;
    }

    return 0;
}