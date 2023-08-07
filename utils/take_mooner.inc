enum TakeMoonerStatus {
	TMS_SUC = 0, // success
	TMS_NEG, // Negative cre
	TMS_SQL_ERR, // unhandled sql err
	TMS_SQL_HAN, // handled sql err
}

TakeMoonerStatus TakeMooner(const int tickets, const char[] ticketid){
	char[] query_pre = "SELECT store_players.credits FROM raffle INNER JOIN store_players ON raffle.steam2id = \"STEAM_1:\" + store_players.authid WHERE raffle.raffleid = 2\"%s\";";
	char[] query_fmt = "UPDATE store_players, raffle SET store_players.credits = store_players.credits - (%d * %d) WHERE raffle.steam2id = (SELECT raffle.steam2id  FROM raffle WHERE raffle.raffleid = \"%s\");";
	char query[1024];
	Format(query, 1024, query_pre, ticketid);
	DBResultSet rs = SQL_Query(db, query);
	if (rs == null) {
		char sqlbuffer[1024];
		SQL_GetError(db, sqlbuffer, 1024);
		LogError(sqlbuffer);
		return TMS_SQL_HAN;
	}
	if (SQL_FetchRow(rs)){
		int cre = rs.FetchInt(0);
		if ((cre - (tickets*sm_dc_event_price.IntValue)) < 0) {
			PrintToServer("Negative");
			return TMS_NEG;
		}
	} else {
		LogError("Sql_FetchRow failed in %s", __LINE__);
		return TMS_SQL_ERR;
	}
	int price = sm_dc_event_price.IntValue;
	Format(query, 1024, query_fmt, tickets, price, ticketid);
	if (!SQL_FastQuery(db, query)){
	   char sqlbuffer[1024];
	   SQL_GetError(db, sqlbuffer, 1024);
	   LogError(sqlbuffer);
	   return TMS_SQL_HAN;
	}
	return TMS_SUC;
}