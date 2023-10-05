/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   saveIcon_svg;
    const int            saveIcon_svgSize = 1057;

    extern const char*   loadIcon_svg;
    const int            loadIcon_svgSize = 652;

    extern const char*   redoIcon_svg;
    const int            redoIcon_svgSize = 657;

    extern const char*   undoIcon_svg;
    const int            undoIcon_svgSize = 869;

    extern const char*   nextPresetIcon_svg;
    const int            nextPresetIcon_svgSize = 688;

    extern const char*   prevPresetIcon_svg;
    const int            prevPresetIcon_svgSize = 716;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 6;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
