/*
@param db_ The database connection use to execute the query
@param query The query it self
@return True if the query was successful false otherwise
*/ 
bool fast_query(Database db_, const char[] query){
    if (!SQL_FastQuery(db_, query)){
        char sqlbuffer[1024];
        SQL_GetError(db_, sqlbuffer, 1024);
        LogError(sqlbuffer);
        return false;
    }
    return true;
}