#if defined __globals
#endinput
#endif
#define __globals

Database db;
Handle timer;
ConVar sm_dc_event_price;
ConVar sm_dc_event_db;
ConVar sm_dc_timer_time;
ConVar sm_dc_is_live;

public Plugin myinfo = {
    name="Dc raffle shitfest!",
    author="os",
    description="Idk mate this shit is the hackiest way of doing things",
    version="0.69-final-beta-rc-early_access-alpha",
    url=""
};
