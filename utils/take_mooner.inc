bool TakeMooner(const int tickets, const char[] ticketid){
	char[] query_fmt = "UPDATE store_players, raffle SET store_players.credits = store_players.credits - (%d * %d) WHERE raffle.steam2id = (SELECT raffle.steam2id  FROM raffle WHERE raffle.raffleid = \"%s\");";
	char query[1024];
	int price = sm_dc_event_price.IntValue;
	Format(query, 1024, query_fmt, tickets, price, ticketid);
	return fast_query(db, query);
}