#include<iostream>

#include "resource.h"

#include "ui/base/resource/data_pack.h"
#include "base/logging.h"
#include "base/string_piece.h"
#include "base/file_path.h"
#include "base/string_util.h"

int main(int argc, char** argv)
{
    ui::DataPack datapack;
    FilePath file(L"data.pak");
    CHECK(datapack.Load(file));
    base::StringPiece piece;
    datapack.GetStringPiece(IDS_HELLO_WROLD, &piece);
    //data pack string are UTF16 encode
    string16 str(reinterpret_cast<const char16*>(piece.data()), 
                 piece.length() / 2);
    std::cout << UTF16ToASCII(str) << std::endl;
    return 0;
}