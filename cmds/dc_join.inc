Action CmdDcJoin(int argc){
	if (argc < 3) {
		LogError("Not enough args");
		return Plugin_Stop;
	}
	char id[1024];
	char tickets[256];
	char timestamp[64];
	GetCmdArg(1, id, 1024);
	GetCmdArg(2, tickets, 256);
	GetCmdArg(3, timestamp, 64);

	char[] fmt = "UPDATE raffle SET tickets = %s, completed = %s WHERE raffleid = \"%s\";";
	char query[1024];
	Format(query, 1024, fmt, tickets, timestamp, id);
	if (!TakeMooner(StringToInt(tickets), id)) {
		LogError("Failed to take mooner lmao!");
	}
	if (!fast_query(db, query)) {
		return Plugin_Stop;
	}
	PrintToServer("Take: %d*%d=%d", StringToInt(tickets), sm_dc_event_price.IntValue, StringToInt(tickets) * sm_dc_event_price.IntValue);
	PrintToServer("OK.");
	return Plugin_Handled;
}