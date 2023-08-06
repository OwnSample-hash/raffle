#!/bin/zsh
spcomp dc_event.sp \
-o`pwd`/dc_event.smx \
-i`pwd`/include \
-i `pwd` \
-O2 -v2 
cp dc_event.smx cs_server/csgo/addons/sourcemod/plugins
echo donE
