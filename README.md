# SA:MP mSelection Inline

[![sampctl](https://img.shields.io/badge/sampctl-inline--mSelection-2f2f2f.svg?style=for-the-badge)](https://github.com/Kirima2nd/inline_mSelection)

Added inline support for mSelection

## Installation

Simply install to your project:

```bash
sampctl package install Kirima2nd/inline_mSelection
```

Include in your code and begin using the library:

```pawn
#include <Inline_mSelection>
```

## Function Lists

```pawn
forward ShowModelSelectionInline({F@_@iii, F@_@ii}:callback, playerid, listId, const string:headerText[], dialogBGcolor = 0x4A5A6BBB, previewBGcolor = 0x88888899, selectionColour = 0xFFFF00AA, tag = tagof (callback));

forward ShowModelSelectionInlineEx({F@_@iii, F@_@ii}:callback, playerid, const itemsArray[], itemAmount, const string:headerText[], Float:Xrot = 0.0, Float:Yrot = 0.0, Float:Zrot = 0.0, Float:mZoom = 1.0, dialogBGcolor = 0x4A5A6BBB, previewBGcolor = 0x88888899, selectionColour = 0xFFFF00AA, tag = tagof (callback));
```

## Usage

The basic usage of this include is like this:
```pawn
public OnPlayerSpawn(playerid) 
{
	inline _OnModelResponse(response, modelid) 
	{
		if (!response) return Kick(playerid);
		SetPlayerSkin(playerid, modelid);
	}
	ShowModelSelectionInline(using inline _OnModelResponse, playerid, g_MakeSkins, "Select Skin");
	return 1;
}

```

And you can also use `using public yourFunction<iii>` or `using function yourFunction<iii>` if you don't want to use inline.

For example:
```pawn
forward OnModelResponse(playerid, response, modelid);
public OnModelResponse(playerid, response, modelid)
{
	if (!response) return Kick(playerid);
	SetPlayerSkin(playerid, modelid);
	return 1;
}

public OnPlayerSpawn(playerid) 
{
	ShowModelSelectionInline(using public OnModelResponse<iii>, playerid, g_MakeSkins, "Select Skin");
	return 1;
}
```

## Testing

To test, make sure you enable `local: true` and then upload the text lists into scriptfiles. After doing those steps, run the following commands:

```bash
sampctl package ensure
sampctl package run --forceBuild
```

