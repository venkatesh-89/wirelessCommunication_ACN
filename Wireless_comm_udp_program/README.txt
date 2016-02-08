Energy Efficient Wireless Communication UDP Program 	Version 1.0 	12/14/2014

GENERAL USAGE NOTES
--------------------------------------------------------------------
1. Extract the contents of the *.zip file into a folder
2. Transfer all the files to the cs1.utdallas.edu server 

COMPILATION :
--------------------------------------------------------------------
1. Execute the make file using the following command :-> 'make all' or 'make'
2. Executable with name 'spanningTree' will be generated

CLEAN :
--------------------------------------------------------------------
1. Execute the make file using the following command :-> 'make clean'
2. All Executables and object files will be deleted


INSTRUCTIONS (How To Use) :
--------------------------------------------------------------------
1. Execute the start_proc.sh script to run the nodes from 'B' to 'T'
2. Execute the spanningTree executable with Arguments 'Node_Name' and File_Name
3. Select the approriate option from the menu.
4. Output of all nodes are written into a file starting with the Node_Name followed by the date and timestamp.


# USAGE (using start_proc.sh):
--------------------------------------------------------------------
>> ./start_proc.sh <File_Name>
>> Example : ./start_proc.sh Topology_1
>> This command above will start 19 instances of './spanningTree' with node names from 'B' to 'T'


# USAGE (using executable):
--------------------------------------------------------------------
>> ./spanningTree <Node_Name> <File_Name>
>> Example : ./spanningTree A Topology_1


# USAGE (using kill_proc.sh):
--------------------------------------------------------------------
>> ./kill_proc.sh
>> Example : ./kill_proc.sh
>> This command above will kill all instances of './spanningTree'



************************************************
Contact Information :                    
************************************************

Name   : Iyer Venkatesh Narayanan        
Mobile : +1 (469) 279-0848               
Email  : vxi140430@utdallas.edu

Name   : Lokeshwar Kesavan        
Mobile : +1 (469) 237-9356               
Email  : lxk140030@utdallas.edu

Name   : Sahith Katukuri        
Mobile : +1 (469) 250-9280               
Email  : sxk145130@utdallas.edu


