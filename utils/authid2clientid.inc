/*
	@param authid The auth2id of a client
	@param authtype The auth id type default AuthId_Steam2
	@return The client's current id or -1 if none found
*/
stock int AuthId2ClientId(const char[] authid, AuthIdType authtype=AuthId_Steam2){
	int client = -1;
	char auth2_buffer[256];
	for (int i = 1; i < MAXPLAYERS; i++)
		if (IsClientInGame(i))
			if(GetClientAuthId(i, authtype, auth2_buffer, 256))
				if (strcmp(auth2_buffer, authid) == 0) return i;
				else continue;
			else LogError("Failed to get AuthId for client[%d]", i);
	return client;
}