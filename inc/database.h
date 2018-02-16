#ifndef database_h
#define database_h

int open_or_new_db (/* char* custom_name, */ sqlite3* db_ptr, int scope);

#endif