#if defined __cre_table
#endinput
#endif
#define __cre_table

Action CmdCreateTbl(int argc){
	// "DROP TABLE IF EXISTS raffle;CREATE TABLE raffle (steam2id VARCHAR(255) PRIMARY KEY NOT NULL, raffleid VARCHAR(20) NOT NULL);"
	if (!fast_query(db, "DROP TABLE IF EXISTS raffle;")){
	   return Plugin_Stop;
	}
	if (!fast_query(db, "CREATE TABLE raffle (steam2id VARCHAR(255) PRIMARY KEY NOT NULL, raffleid VARCHAR(25) NOT NULL, tickets INT NULL, completed BIGINT NULL, notified BIGINT NULL);")){
 		return Plugin_Stop;
	}
	
	PrintToServer("DONE!");
	return Plugin_Handled;
}
