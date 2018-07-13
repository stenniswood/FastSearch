//
//  main.cpp
//  FileSearchIndexer
//
//  Created by Stephen James Tenniswood on 7/12/18.
//  Copyright © 2018 Stephen James Tenniswood. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <strings.h>

#include <list>
#include <sys/types.h>
#include <dirent.h>
#include "sql_file_indexer.hpp"


using namespace std;

std::list<std::string>     m_unprocessed_list;
std::list<std::string>     m_processed_list;

bool create_index;
std::string Path;
std::string Filename;

void sql_add_folder(std::string Pathname)
{
    m_unprocessed_list.push_back(Pathname);
}

void sql_add_file(std::string filename, string Path )
{
    insert_file(filename, Path);
}

void read_directory(string Basepath)
{
    cout << "Reading: " << Basepath << endl;
    
    DIR *dir;
    struct dirent *ent;
    dir = opendir (Basepath.c_str());
    if (dir != NULL)
    {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            if (ent->d_type==DT_DIR)
                sql_add_folder(Basepath+"/"+ent->d_name);
            else
                sql_add_file(ent->d_name, Basepath );
        }
        closedir (dir);
    }
}

void capture_and_repeat()
{
    m_processed_list = m_unprocessed_list;
    m_unprocessed_list.clear();
    
    for (std::list<string>::iterator iter = m_processed_list.begin();
         iter != m_processed_list.end();
         iter++)
    {
        // skip if "/." or "/.."
        size_t len = (*iter).length();
	string sub1="";
	string sub2="";
	if (len>1)
        	sub1 = iter->substr(len-1, 1);
        if (len>2)
		sub2 = iter->substr(len-2, 2);
        if ((sub1.compare(".")==0) || (sub2.compare("..")==0))
            continue;
        
        read_directory( *iter );
    }
    if (m_unprocessed_list.size()!=0)
        capture_and_repeat();
}
void help()
{
    cout << endl << "Fast File Searcher.  This app creates an SQL index for the entire directory."<<endl;
    cout << "For instant searches for a file."<<endl<<endl;
    cout << "OPTIONS:"<<endl;
    cout << "         -I    create the index"<<endl;
    cout << "         -b    set the basepath"<<endl;
    cout << "         [filename] to search for."<<endl;
    
}

int main (int argc, char** argv )
{
    init_sql();
    create_database();
    use_database();

    // Process Arguments
    for (int i=0; i<argc; i++)
    {
	//cout << "argument: " << argv[i] << endl;
        if ((strcmp(argv[i], "-h")==0) || (strcmp(argv[i], "help")==0))
            help();

        if (strcmp(argv[i], "-I")==0)
		create_index = true;
        if (strcmp(argv[i], "-b")==0)
        {
            Path = argv[i+1];
            size_t len = Path.length();
            if (Path[len-1]=='/') {
                    Path.erase(len - 1);
			//Path.pop_back();
		}
            cout << "Basepath = " << Path << endl;
        }
    }
    Filename = argv[argc-1];
    
    if (create_index)
    {
        drop_table();
        create_table();
        cout << "Creating Index!!!" << endl;
        m_unprocessed_list.push_back( Path );
        capture_and_repeat();
    }
    else
    {
        cout << "Finding file: " << Filename << endl;
        find_file(Filename);
        print_results();
        
    }
    
}
