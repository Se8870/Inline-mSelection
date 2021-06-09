#if defined _INC_mSelection_inline
	#endinput
#endif

#define _INC_mSelection_inline

#include <mSelection>
#include <YSI_Coding\y_inline>

static stock 
	g_PlayerCurrentListID[MAX_PLAYERS],
	Func:g_sRequestModelSelection[MAX_PLAYERS]<ii>;

stock ShowModelSelectionInline(playerid, ListID, const header_text[], Func:cb<ii>, dialogBGcolor = 0x4A5A6BBB, previewBGcolor = 0x88888899, tdSelectionColor = 0xFFFF00AA) {
	new ret = ShowModelSelectionMenu(playerid, ListID, header_text, dialogBGcolor, previewBGcolor, tdSelectionColor);

	if (ret) {
		Indirect_Claim(cb);
		g_sRequestModelSelection[playerid] = cb;
		g_PlayerCurrentListID[playerid] = ListID;
	}
	return ret;
}

stock ShowModelSelectionInlineEx(playerid, const items_array[], item_amount, const header_text[], extraid, Func:cb<ii>, Float:Xrot = 0.0, Float:Yrot = 0.0, Float:Zrot = 0.0, Float:mZoom = 1.0, dialogBGcolor = 0x4A5A6BBB, previewBGcolor = 0x88888899 , tdSelectionColor = 0xFFFF00AA) {
	new ret = ShowModelSelectionMenuEx(playerid, items_array, item_amount, header_text, extraid, Xrot, Yrot, Zrot, mZoom, dialogBGcolor, previewBGcolor, tdSelectionColor);

	if (ret) {
		Indirect_Claim(cb);
		g_sRequestModelSelection[playerid] = cb;
		g_PlayerCurrentListID[playerid] = extraid;
	}
	return ret;
}

#include <YSI_Coding\y_hooks>
DEFINE_HOOK_REPLACEMENT__(ModelSelection, ModSel);

hook OnPlayerModSel(playerid, response, listid, modelid) {
	new 
		Func:cb<ii> = g_sRequestModelSelection[playerid];

	g_sRequestModelSelection[playerid] = Func:0<ii>;

	if (listid != mS_INVALID_LISTID && listid == g_PlayerCurrentListID[playerid]) {
		g_PlayerCurrentListID[playerid] = mS_INVALID_LISTID;
		@.cb(response, modelid);
	}
	Indirect_Release(cb);
	return 1;
}

hook OnPlayerModSelEx(playerid, response, extraid, modelid) {
	new 
		Func:cb<ii> = g_sRequestModelSelection[playerid];

	g_sRequestModelSelection[playerid] = Func:0<ii>;

	if (extraid != mS_INVALID_LISTID && extraid == g_PlayerCurrentListID[playerid]) {
		g_PlayerCurrentListID[playerid] = mS_INVALID_LISTID;
		@.cb(response, modelid);
	}
	Indirect_Release(cb);
	return 1;
}

hook OnPlayerDisconnect(playerid, reason) {

	// Release it when player disconnect
	Indirect_Release(g_sRequestModelSelection[playerid]);
	g_sRequestModelSelection[playerid] = Func:0<ii>;
	g_PlayerCurrentListID[playerid] = mS_INVALID_LISTID;
}