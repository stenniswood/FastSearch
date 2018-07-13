//
//  sql_file_indexer.cpp
//  FileSearchIndexer
//
//  Created by Stephen James Tenniswood on 7/12/18.
//  Copyright © 2018 Stephen James Tenniswood. All rights reserved.
//
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "sql_file_indexer.hpp"
#include "mysql.h"

using namespace std;

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;

void init_sql()
{
    char *server = "localhost";
    char *user = "root";
    char *password = "password"; /* set me first */
    char *database = "Files";
    
    conn = mysql_init(NULL);
    
    /* Connect to database */
    if (!mysql_real_connect(conn, server,
                            user, password, NULL, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
}

void close_sql()
{
    
}

void create_database()
{
    string query = "create database Files;";
    /* send SQL query */
    if (mysql_query(conn, query.c_str() ))
    {
        //fprintf(stderr, "%s\n", mysql_error(conn));
        //exit(1);
    }
}
void use_database()
{
    string query = "use Files;";
    if (mysql_query(conn, query.c_str() ))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
}

void create_table()
{
    string query = "create table FileList (_fileId INT PRIMARY KEY AUTO_INCREMENT, Name VARCHAR(255), Type VARCHAR(1), Path VARCHAR(255) );";

    if (mysql_query(conn, query.c_str() ))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

}
void drop_table()
{
    string query = "DROP table FileList;";
    
    if (mysql_query(conn, query.c_str() ))
    {
        //fprintf(stderr, "%s\n", mysql_error(conn));
        //exit(1);
    }
}

void insert_file(string filename, string path)
{
    string query = "INSERT INTO FileList () VALUE (0, \"";
    query += filename;
    query += "\", 'F', '";
    query += path;
    query += "' );";
    
    if (mysql_query(conn, query.c_str() ))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
}

MYSQL_RES *result=0;

void find_file(string filename)
{
    string query = "SELECT * FROM FileList where Name like '%";
    query += filename;
    query += "%'; ";
    
    if (mysql_query(conn, query.c_str() ))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    result = mysql_store_result(conn);
    
}

void print_results()
{
    while ((row = mysql_fetch_row(result)))
    {
        cout << row[3] << "/" << row[1] << endl;
    }
}
