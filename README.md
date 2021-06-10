# SA:MP mSelection Inline

[![sampctl](https://img.shields.io/badge/sampctl-random--name-2f2f2f.svg?style=for-the-badge)](https://github.com/Kirima2nd/inline_mSelection)

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
native ShowModelSelectionInline(playerid, ListID, const header_text[], Func:cb<ii>, dialogBGcolor = 0x4A5A6BBB, previewBGcolor = 0x88888899, tdSelectionColor = 0xFFFF00AA);
native ShowModelSelectionInlineEx(playerid, const items_array[], item_amount, const header_text[], extraid, Func:cb<ii>, Float:Xrot = 0.0, Float:Yrot = 0.0, Float:Zrot = 0.0, Float:mZoom = 1.0, dialogBGcolor = 0x4A5A6BBB, previewBGcolor = 0x88888899 , tdSelectionColor = 0xFFFF00AA);
```

## Usage

You can check it on test.pwn

## Testing

To test, make sure you enable `local: true` and then upload the text lists into scriptfiles. After doing those steps, run the following commands:

```bash
sampctl package ensure
sampctl package run --forceBuild
```

