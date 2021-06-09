#include <a_samp>

#define YSI_NO_HEAP_MALLOC
#define YSI_NO_VERSION_CHECK
#define YSI_NO_CACHE_MESSAGE
#define YSI_NO_OPTIMISATION_MESSAGE

#include <Inline_mSelection>

new 
	g_MakeSkins = mS_INVALID_LISTID;

public OnGameModeInit() {
	g_MakeSkins = LoadModelSelectionMenu("makeskin.txt");
}

main() { 

}

public OnPlayerSpawn(playerid) {
	inline _OnModelResponse(response, modelid) {
		if (!response) return Kick(playerid);

		SetPlayerSkin(playerid, modelid);
	}
	ShowModelSelectionInline(playerid, g_MakeSkins, "Select Skin", using inline _OnModelResponse);
	return 1;
}
