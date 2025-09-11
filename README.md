# TimeTravellingFileSystem <br>  
## Code Functionality and Error Handling Per Operation :  <br>  

## Instructions for running the code : <br>
Works only on macos , linux , Windows (might have compilation issues) <br>
1.) just open up terminal and go to the folder where you have extracted the folder. Inside the folder open up terminal and type ./compile.sh(For mac and linux ) , For windows type ./compile.ps1 . <br>
2.) Choose the option in terms of numbers that you want to run  and it should work automatically . <br>
3.) Note that the documentation opens up this very document. <br>
4.) If you select option 2 then you will have to manually open the output.txt file to view the output file in your favourite text editor. <br>



### Create  :   <br>
Error Handling :  <br>
1.) If create is misspelled then it redirects to the start and says to you to type in only valid codes in any case you like all the cases are acceptable that is even inputs of the type CreAte is considered valid but the spelling should be correct.<br>
2.) If the filename is not provided and enter is pressed then the program will not move on and ask for the next command untill you enter the name of the file. <br>
3.) FileName with spaces will be accepted but only the first block of text without spaces will be considered as the filename . Any character besides space is allowed for naming files.<br>
Behaviour of code : <br>
1.) Creates a file with the given fllename subject to above conditions and also sets the various attributes given such as created timestamp . <br>
2.) Since the root of the file that is the newly created file is automatically a snapshot it always contains blank contents inside it since you can't modify the root according to the needs of the assignment. <br>
3.) Moreover a default snapshot message is provided to indicate that the root is the default snapshot and no modifications can be made to it.<br>

### Read : <br>
Error Handling : <br>
1.) Misspelling of commands is handled the same way as in create and same comments about the case of the input .<br>
2.) If the filename is not provided  then same behaviour as create occurs .<br>
3.) If the filename is provided such that the file does not exist then it is indicated by an error message and the user is prompted to the start to input the correct set of codes. <br>
4.) Moreover if multiple blocks of filenames are provided at once with spaces in between then only the first block of text is considered to be the filename under process . For multiple files you will have to run the read command multiple times with a single filename.<br>
5.) As specified earlier filenames are assumed to be without spaces hence point 4 does not cause issue in the correctness of the code.<br>

Behaviour of code: <br>
1.) Prints the message stored in the current active version of the file .<br>
2.) If no message is stored for example as in root then it a blank line is printed on the terminal output. <br>
3.) Initial spaces in the message are ignored but the message can have spaces in between and that is printed. For example : 
"width of space extra initial space before actual message  "  message is treated as message but message " width of space in between two message components " message2 is treated as message                   message2 (depending on the width). <br>
4.)Moreover extra space after the end of the message is not discarded for example : message "extra space after the message " is printed on the terminal as message with apt space left . <br>

### Insert : <br>
Error Handling and Behaviour of code :<br>
1.) Misspelling and case same as create. <br>
2.) Filename handling same as Read. <br>
3.) Initial , ending and spaces in between the message are handled same as Read. <br>
4.) Note if there is already a content in the file , then the newly inserted content is inserted after a space in between the two messages. If there is no existing content in the file then no initial spaces are added. For example if the file consisted of message1 and we are inserting in the same file message2 then the new content becomes message1 message2 and not message1message2. Moreover if it is the first message then the same logic as Read is followed that is starting and ending spaces are ignored. <br>
5.) Moreover if the file is already a snapshot then a new file is created as a child of the snapshotted file and its content is inherited and then the newcontent is appended to the child by the same logic as above.<br>
6.) However for non snapshotted file the active version's content becomes existing + newly added by the same logic as above .<br>


### Update: <br>
Everything identical to Insert except that since there is  no initial content so the rules for initial content do not apply here.

### Snapshot:  <br>
Error Handling :
1.) Misspelling is handled the sameway as in Create. <br>
2.) Filenames are handled the sameway as in Insert , Update and Read. <br>
3.) If trying to snapshot an already snapshotted file then that is indicated with an error message and the code returns back to prompting the user for entering correct code.<br>
4.) Providing message is user's choice that is empty messages are also acceptable in which case they are reflected as empty messages. <br>
Behaviour of code:
1.) Snapshots if already not a snapshot and update the heaps for tracking system wide analytics.<br>
2.) You cannot change a message of a snapshot that is if you re-run the command snapshot on an already snapshotted version with a different message it does not work and you are prompted to enter the correct code.  <br>
3.) Initial spaces are discarded in the message but the ending spaces are not and messages can have spaces in between them.<br>

### History: <br>
Error Handling: 
1.) Misspelling is handled the same way as in create. <br>
2.) Filenames are handled the sameway as in snapshot . <br>

Behaviour of code:<br>
1.) Returns the snapshotted versions , their messages and time stamps in a sequential order , recent one first from the active version to the root on a new line each. <br>

### Rollback: <br>
Error Handling : 
1.) Misspelling and incorrect filenames are handled same as History. <br>
2.) If the version_id is not in the range (0(root's verision id) : last_version_id / total_number_of_versions - 1) then an error is thrown indicating the same. <br>
3.) If no argument is given then we go back to the parent of the last active version . <br>
4.) If no argument is provided at the root version then it is also indicated by the correct message. <br>
5.) If instead of integer anything else is provided , then that is also handled and is indicated by a message .<br>

Behaviour :<br>
1.)Sets the active version to the specific version_id provided.


### Recent Files : <br>
Error Handling : 
1.) Misspelling is handled the same way as in Create <br>
2.) Works only if a number >= 0 is provided , in all other cases it is indicated by an apt message . <br>
3.) Works even if no argument is provided . <br>

Behaviour: <br>
1.) Lists out the last k recent modifications made in the order which they were made starting from the most recent.<br>
2.) If no input is provided then lists out all the modifications in the above order . <br>
3.) If an input more than the number of modifications is provided , then also all the modifications uptill now are displayed along with an apt message stating the above fact. <br>



### Biggest Trees : <br>
Error handling is exactly identical to Recent Files <br>
Behaviour of code : 
Identical to recent files except that the files with the most number of versions are displayed in decreasing order of number of versions, Rest logic is identical to recent files just with the aforementioned slight modification . <br>

