#include <iostream>
#include <windows.h>
#include <vector>


#pragma pack(push,1)
using namespace std;

// C�������� Volume Header
struct Volume_Header
{
    WORD header_crc;
    BYTE header_type;
    WORD header_flags;
    WORD header_size;
};

// C�������� File_head ��� ���������� ��� ������

struct File_head
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
// �������� ������� ������ ��� ������
void PrintHeaderContent(const vector <char> &, DWORD filesize);

void Print_vector(const vector <char> & printing_vector, int vectorsize);

int main() {
    // ��������� ����

    setlocale(LC_ALL, "Russian");
    wchar_t *filname =L"D:\\CodeBlocks\\rar_reader\\Example.rar";
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
    // �������� ������ �����
    DWORD fileSize = GetFileSize(filename, NULL);

    // ������� ���������� ����� � �����
    vector<char> buffer(fileSize);

    DWORD bytesRead;
    ReadFile(filename, &buffer[1], fileSize, &bytesRead, NULL);


    PrintHeaderContent(buffer, fileSize);

    wcout << L"Value " << endl;
    //for (char c : buffer) {
        //std::wcout << c ;

    //}

    // ��������� ����
    CloseHandle(filename);



    return 0;
}

void Print_vector(const vector <char> & printing_vector)
{
    for (char c : printing_vector){
        wcout << c;
    }
}

void PrintHeaderContent(const vector <char> & filebufer, DWORD filesize)
{
//    for (char c : filebufer) {
//        std::wcout << c ;
//
//    }
    // ������ ��������� ��������� Volume Header
    cout << "\nFile size : " <<  filesize << endl ;
    Volume_Header header_main;
    // ������ ��������� ��������� ��� header �����
    File_head file_header;
    cout << sizeof(file_header);
    int index_to_cut = 7; // ���������� ��� ����, ����� ������� ������ 7 ���� �����

    vector <char> rar_with_no_7bytes (filebufer.begin() + index_to_cut , filebufer.begin() + filebufer.size());

    while (index_to_cut < filesize)
    {
        cout << "\nIndex_to_cut = " << index_to_cut << endl;
        cout << "\nFileSize = " << filesize << endl;
        memcpy(&header_main, &rar_with_no_7bytes[index_to_cut], sizeof(file_header));
        cout << header_main.header_type << endl;
        if (header_main.header_type == 0x74)
        {
            cout << "123"<< endl;
            index_to_cut += sizeof(file_header) ;
        }
        else
        {
            cout << "12"<< endl;
            index_to_cut += header_main.header_size;
        }
    }






}
