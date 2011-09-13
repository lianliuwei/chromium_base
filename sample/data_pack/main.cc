#include<iostream>

#include "resource.h"

#include "ui/base/resource/data_pack.h"
#include "base/logging.h"
#include "base/string_piece.h"
#include "base/file_path.h"

int main(int argc, char** argv)
{
    ui::DataPack datapack;
    FilePath file(L"data.pak");
    CHECK(datapack.Load(file));
    base::StringPiece piece;
    datapack.GetStringPiece(IDS_HELLO_WROLD, &piece);
    std::cout << piece << std::endl;
    return 0;
}