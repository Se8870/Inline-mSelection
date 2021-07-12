#if defined _INC_mSelection_inline
	#endinput
#endif

#define _INC_mSelection_inline

#include <mSelection>
#include <YSI_Coding\y_inline>

// Using this to prevent any problem due to PAWN Limitations
DEFINE_HOOK_REPLACEMENT__(ModelSelection, ModSel);

static stock
	Func:g_sRequestModelSelection[MAX_PLAYERS]<iii>,
	g_PlayerCurrentListID[MAX_PLAYERS] = {mS_INVALID_LISTID, ...};

// Func:callback<iii> | Func:callback<ii>
stock ShowModelSelectionInline({F@_@iii, F@_@ii}:callback, playerid, listId, const string:headerText[], dialogBGcolor = 0x4A5A6BBB, previewBGcolor = 0x88888899, selectionColour = 0xFFFF00AA, tag = tagof (callback))
{
	new ret = ShowModelSelectionMenu(playerid, listId, headerText, dialogBGcolor, previewBGcolor, selectionColour);

	if (ret)
	{
		Indirect_Claim(callback);
		Indirect_SetMeta(callback, tag);

		g_PlayerCurrentListID[playerid] = listId;
		g_sRequestModelSelection[playerid] = callback;
	}
	return ret;
}

// Func:callback<iii> | Func:callback<ii>
stock ShowModelSelectionInlineEx({F@_@iii, F@_@ii}:callback, playerid, const itemsArray[], itemAmount, const string:headerText[], Float:Xrot = 0.0, Float:Yrot = 0.0, Float:Zrot = 0.0, Float:mZoom = 1.0, dialogBGcolor = 0x4A5A6BBB, previewBGcolor = 0x88888899, selectionColour = 0xFFFF00AA, tag = tagof (callback)) 
{
	new ret = ShowModelSelectionMenuEx(playerid, itemsArray, itemAmount, headerText, -1, Xrot, Yrot, Zrot, mZoom, dialogBGcolor, previewBGcolor, selectionColour);

	if (ret) 
	{
		Indirect_Claim(callback);
		Indirect_SetMeta(callback, tag);

		g_sRequestModelSelection[playerid] = callback;
	}
	return ret;
}

#include <YSI_Coding\y_hooks>
hook OnPlayerModSel(playerid, response, listid, modelid)
{
	new 
		Func:cb<iii> = g_sRequestModelSelection[playerid];
	
	g_sRequestModelSelection[playerid] = Func:0<iii>;

	if (listid != mS_INVALID_LISTID && listid == g_PlayerCurrentListID[playerid])
	{
		if (Indirect_GetMeta(cb) == tagof (F@_@iii:))
		{
			Indirect_Call(_:cb, tagof (F@_@iii:), playerid, response, modelid);
		}
		else
		{
			Indirect_Call(_:cb, tagof (F@_@ii:), response, modelid);
		}
		// Free the data after call.
		Indirect_Release(cb);
		g_PlayerCurrentListID[playerid] = mS_INVALID_LISTID;

		return Y_HOOKS_BREAK_RETURN_1;
	}
	return Y_HOOKS_CONTINUE_RETURN_0;
}

hook OnPlayerModSelEx(playerid, response, extraid, modelid) 
{
	new 
		Func:cb<iii> = g_sRequestModelSelection[playerid];

	g_sRequestModelSelection[playerid] = Func:0<iii>;

	if (cb != Func:0<iii>) 
	{
		if (Indirect_GetMeta(cb) == tagof (F@_@iii:))
		{
			Indirect_Call(_:cb, tagof (F@_@iii:), playerid, response, modelid);
		}
		else 
		{
			Indirect_Call(_:cb, tagof (F@_@ii:), response, modelid);
		}

		// Free the data after call.
		Indirect_Release(cb);
		return Y_HOOKS_BREAK_RETURN_1;
	}
	return Y_HOOKS_CONTINUE_RETURN_0;
}

hook OnPlayerDisconnect(playerid, reason) 
{
	#pragma unused reason

	// If the current cb not invalid, then we need to clear it
	if (g_sRequestModelSelection[playerid] != Func:0<iii>) 
	{
		Indirect_Release(g_sRequestModelSelection[playerid]);
		g_sRequestModelSelection[playerid] = Func:0<iii>;
	}

	// Setting it to mS_INVALID_LISTID to prevent anything happend.
	g_PlayerCurrentListID[playerid] = mS_INVALID_LISTID;
	return 1;
}
