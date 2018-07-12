//
//  sql_file_indexer.hpp
//  FileSearchIndexer
//
//  Created by Stephen James Tenniswood on 7/12/18.
//  Copyright © 2018 Stephen James Tenniswood. All rights reserved.
//

#ifndef sql_file_indexer_hpp
#define sql_file_indexer_hpp

#include <stdio.h>
#include <string>

using namespace std;

void init_sql();
void close_sql();
void use_database();
void create_database();
void create_table();
void drop_table  ();
void insert_file (string filename, string path);
void find_file   (string filename);
void print_results();

#endif /* sql_file_indexer_hpp */
