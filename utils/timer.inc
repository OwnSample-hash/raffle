Action TimerCheckCompleted(Handle timer_){
	char[] query = "SELECT raffle.steam2id FROM raffle WHERE raffle.notified IS NULL;";
	char[] query_fmt = "UPDATE raffle SET raffle.notified = %d WHERE raffle.steam2id = \"%s\";";
	DBResultSet res = SQL_Query(db, query);
	if (res == null) {
		char sqlbuffer[1024];
		SQL_GetError(db, sqlbuffer, 1024);
		LogError(sqlbuffer);
		return Plugin_Stop;
	}
	while (res.MoreRows)
		if (SQL_FetchRow(res)){
			char authid[1024];
			res.FetchString(0, authid, 1024);
			int client = AuthId2ClientId(authid);
			char query_u[512];
			Format(query_u, 512, query_fmt, GetTime(), authid);
			if (!fast_query(db, query_u)){
				return Plugin_Stop;
			}
			PrintToBoth(client, "We have confirmed your raffel join! Good luck!");
		}
	delete res;
	return Plugin_Handled;
}
