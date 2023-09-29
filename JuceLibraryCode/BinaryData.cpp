/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#include <cstring>

namespace BinaryData
{

//================== save.svg ==================
static const unsigned char temp_binary_data_0[] =
"<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"100\" height=\"100\" viewBox=\"0 0 100 100\" id=\"save\"><g><path d=\"M82.4 24.3l-9.8-9.8c-.4-.4-.9-.6-1.4-.6H19c-1.1 0-2 .9-2 2v68c0 1.1.9 2 2 2h62c1.1 0 2-.9 2-2V25.8c0-.6-.2-1.1-.6-1.5zM31 18h38v32"
"H31V18zm48 64H21V18h6v34c0 1.1.9 2 2 2h42c1.1 0 2-.9 2-2V20.6l6 6V82zM64.8 24.5v19c0 1.1-.9 2-2 2s-2-.9-2-2v-19c0-1.1.9-2 2-2s2 .9 2 2z\" fill=\"white\"></path></g><g><path fill=\"#00F\" d=\"M1504-930V754H-280V-930h1784m8-8H-288V762h1800V-938z\"></pa"
"th></g></svg>\r\n";

const char* save_svg = (const char*) temp_binary_data_0;


const char* getNamedResource (const char* resourceNameUTF8, int& numBytes);
const char* getNamedResource (const char* resourceNameUTF8, int& numBytes)
{
    unsigned int hash = 0;

    if (resourceNameUTF8 != nullptr)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0x847ba8a2:  numBytes = 497; return save_svg;
        default: break;
    }

    numBytes = 0;
    return nullptr;
}

const char* namedResourceList[] =
{
    "save_svg"
};

const char* originalFilenames[] =
{
    "save.svg"
};

const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8)
{
    for (unsigned int i = 0; i < (sizeof (namedResourceList) / sizeof (namedResourceList[0])); ++i)
        if (strcmp (namedResourceList[i], resourceNameUTF8) == 0)
            return originalFilenames[i];

    return nullptr;
}

}
