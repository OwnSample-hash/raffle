Action CmdChooseWiner (int argc) {
    char[] query = "SELECT raffle.steam2id FROM raffle ORDER BY RAND() * raffle.tickets DESC LIMIT 1;"
    DBResultSet res = SQL_Query(db, query);
    if (res == null) {
		char sqlbuffer[1024];
		SQL_GetError(db, sqlbuffer, 1024);
		LogError(sqlbuffer);
		return Plugin_Stop;
	}
    if (SQL_FetchRow(res)){
        char authid[1024];
        res.FetchString(0, authid, 1024);
        PrintToServer("The steamid of the winner: %s", authid);
        int client = AuthId2ClientId(authid);
        if (client != -1)
            PrintToBoth(client, "You have wont the raffle");
    }
    return Plugin_Handled;
}