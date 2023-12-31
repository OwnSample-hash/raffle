#if defined __join
#endinput
#endif
#define __join

Action CmdJoin(int client, int argc){
	if(!sm_dc_is_live.BoolValue){
		PrintToChat(client, "Sorry there is no raffle being held!");
		return Plugin_Handled;
	}
	char code[17];
	char[] chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_";
	for (int i = 0; i < 16;i++){
		code[i] = chars[GetRandomInt(0, strlen(chars))];
	}
	char auth2_buffer[1024];
	if (client != 0)
		if(!GetClientAuthId(client, AuthId_Steam2, auth2_buffer, 1024))
			LogError("Failed to get AuthId_Steam2 for client[%d]", client);

	char[] fmt = "INSERT INTO raffle (steam2id, raffleid) VALUES (\"%s\", \"%s:%d\")";
	char fmt_b[1024];
	int fmt_l = Format(fmt_b, 1024, fmt, auth2_buffer, code, strlen(code));
	if (fmt_l == 0)
		LogError("fmt_l 0");

	if (!SQL_FastQuery(db, fmt_b)){
		char sqlbuffer[1024];
		SQL_GetError(db, sqlbuffer, 1024);
		LogError(sqlbuffer);
		char fmt_[40] = "Duplicate entry '%s' for key 'PRIMARY'";
		char buff[512];
		int buff_l = Format(buff, 512, fmt_, auth2_buffer);
		if (buff_l == 0)
			LogError("fmt_l 0 in error handler");
		if(strcmp(sqlbuffer, buff) == 0){
			PrintToBoth(client, "You already have an active id, use it on dc or contact admins for help!");
			return Plugin_Handled;
	   	}
	}
	
	for (new i;i<5;i++) {PrintToChat(client, "\n");PrintToConsole(client, "\n");}
	PrintToBoth(client, "------------------------------------------------------");
	PrintToBoth(client, "Use this id in the dc comamnd /raffle while joinning: ");
	PrintToBoth(client, "%s:%d", code, strlen(code));
	PrintToBoth(client, "You can use the console to copy the code!");
	PrintToBoth(client, "ALSO DO NOT SHARE YOUR CODE WITH ANY ONE AS IS IT IS BOUND TO YOUR ACCOUNT! (SO THEY CAN SPEND YOUR MONEY!)");
	PrintToBoth(client, "ALSO REMEMBER THE CODE FOR LATER, IF YOU DECIDE TO CHANGE THE AMOUNT OF TICKETS YOU BOUGHT REMEMBER THAT YOU WON'T GET A REFUND!");
	PrintToBoth(client, "The price of one ticket is: %d", sm_dc_event_price.IntValue);
	PrintToBoth(client, "Once we have confirmed your registration you'll be notified!");
	PrintToBoth(client, "------------------------------------------------------");
	for (new i;i<2;i++) {PrintToChat(client, "\n");PrintToConsole(client, "\n");}
	return Plugin_Handled;
}
