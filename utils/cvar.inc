void init_Cvar(){
    sm_dc_event_price = FindConVar("sm_dc_event_price");
    if (sm_dc_event_price == null)
        sm_dc_event_price = CreateConVar("sm_dc_event_price", "50000", "Price of one raffle!");

    sm_dc_event_db = FindConVar("sm_dc_event_db");	
    if (sm_dc_event_db == null)
        sm_dc_event_db = CreateConVar("sm_dc_event_db", "store", "Name of the db!");

    sm_dc_timer_time = FindConVar("sm_dc_timer_time");
    if (sm_dc_timer_time == null)
        sm_dc_timer_time = CreateConVar("sm_dc_timer_time", "15", "Time for repeating the notification \"thread\"!");

    char buffer[1024];
    sm_dc_event_price.GetString(buffer, 1024);
    PrintToServer("Value of sm_dc_event_price:%s", buffer);
    
    for (new i;i<1023;i++) buffer[i] = 0;
    sm_dc_event_db.GetString(buffer, 1024);
    PrintToServer("Value of sm_dc_event_db:%s", buffer);
    
    for (new i;i<1023;i++) buffer[i] = 0;
    sm_dc_timer_time.GetString(buffer, 1024);
    PrintToServer("Value of sm_dc_timer_time:%s", buffer);

    sm_dc_event_price.AddChangeHook(Cvar_dc_event_price);
    sm_dc_event_db.AddChangeHook(Cvar_dc_event_db);
    sm_dc_timer_time.AddChangeHook(Cvar_dc_timer_time);
}

void Cvar_dc_event_price(ConVar cvar, const char[] oldv, const char[] newv){
	LogMessage("Value of sm_dc_event_price new %s, old %s", newv, oldv);
}

void Cvar_dc_event_db(ConVar cvar, const char[] oldv, const char[] newv){
	LogMessage("Value of sm_dc_event_price new %s, old %s", newv, oldv);
	char ebuffer[1024], db_name[256];
	GetConVarString(sm_dc_event_db, db_name, 256);
	db = SQL_Connect(db_name, true, ebuffer, 1024);
	if (db == null)	{
		LogError(ebuffer);
	}
}

void Cvar_dc_timer_time(ConVar cvar, const char[] oldv, const char[] newv){
	LogMessage("Value of sm_dc_event_price new %s, old %s", newv, oldv);
	KillTimer(timer);
	timer = CreateTimer(sm_dc_timer_time.FloatValue, TimerCheckCompleted, 0, TIMER_REPEAT);
	timer == INVALID_HANDLE ? LogError("Failed to create timer!!") : LogMessage("Stared the new timer with %s time", newv);
}