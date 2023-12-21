#include <iostream>
#include <windows.h>
#include <vector>
#pragma pack(push,1)
using namespace std;

struct Header
{
    WORD header_crc;
    BYTE header_type;
    WORD header_flags;
    WORD header_size;
};


struct Headers
{
    DWORD pack_size;
    DWORD unpsize;
    BYTE HostOS;
    DWORD fileCRC;
    DWORD FileTime;
    BYTE unpver;
    BYTE method;
    WORD namesize;
    DWORD fileattr;
    WORD Filename;
    DWORD packed_data;
};

#pragma pack(pop)


void Print_vector(const vector <char> & printing_vector)
{
    for (char c : printing_vector){
        wcout << c;
    }
}

void PrintHeaderContent(const vector <char> &filebufer, DWORD filesize)
{
    Header header;
    Headers headers;
    cout << sizeof(headers) << "sixw" << endl;
    int first_byte = 7;

    vector <char> rar_with_no_7bytes (filebufer.begin() + first_byte , filebufer.begin() + filebufer.size());

    while (first_byte < filesize)
    {

        memcpy(&header, &filebufer[first_byte], sizeof(header));
        if (header.header_type == 0x74)
        {
            cout << headers.Filename << endl;
            first_byte += sizeof(headers);
        }
        else
        {
            cout << headers.Filename << endl;
            first_byte += sizeof(header.header_size);
        }
    }
}



int main() {


    setlocale(LC_ALL, "Russian");
    wchar_t *filname = "C:\\Users\student\Documents\Example.rar";
    HANDLE filename = CreateFileW(
        filname,
        GENERIC_READ,
        FILE_SHARE_READ|FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if (filename == INVALID_HANDLE_VALUE) {
        wcout << "Error" << endl;
        return 1;
    }

    DWORD fileSize = GetFileSize(filename, NULL);


    vector<char> buffer(fileSize);

    DWORD bytesRead;
    ReadFile(filename, &buffer[1], fileSize, &bytesRead, NULL);

    PrintHeaderContent(buffer, fileSize);

    wcout << L"Value " << endl;

    CloseHandle(filename);
    return 0;
}

