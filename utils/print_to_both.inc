#if defined __print_to_both
#endinput
#endif
#define __print_to_both

void PrintToBoth(int client, const char[] msg, any ...){
	char buffer[1024];
	VFormat(buffer, sizeof(buffer), msg, 3);
	PrintToChat(client, "%s", buffer);
	PrintToConsole(client, "%s", buffer);
	//PrintToServer("client[%d]:%s", client, buffer);
}
