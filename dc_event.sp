#include <sourcemod>
#include <globals>

#include <sql/fast_query>

#include <utils/authid2clientid>
#include <utils/cvar>
#include <utils/print_to_both>
#include <utils/take_mooner>
#include <utils/timer>

#include <cmds/cre_table>
#include <cmds/dc_join>
#include <cmds/join>

public void OnPluginStart() {
	RegConsoleCmd("sm_join", CmdJoin, "Joins the raffle on dc!");
	RegServerCmd("sm_dc_join", CmdDcJoin);
	RegServerCmd("sm_dc_cre_table", CmdCreateTbl);

	init_Cvar();

	char ebuffer[1024], db_name[256];
	GetConVarString(sm_dc_event_db, db_name, 256);
	db = SQL_Connect(db_name, true, ebuffer, 1024);
	db == null ? LogError(ebuffer) : LogError("Connected to db: %s", db_name);
	timer = CreateTimer(sm_dc_timer_time.FloatValue, TimerCheckCompleted, 0, TIMER_REPEAT);
	timer == INVALID_HANDLE ? LogError("Failed to create timer!!") : LogMessage("Created timer!");
}

public void OnPluginEnd() {
	delete db;
}
