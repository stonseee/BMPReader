#define _CRT_SECURE_NO_WARNINGS
#include"BMPReader.h"

using std::cin;
using std::cout;
using std::endl;

const std::map<int, std::string>MENU_ITEMS =
{
    {1, "Upload .bmp"},
    {2, "Open .bmp"},
    {3, "Info "},
    {4, "Release memory"},    
};

int menu();

void main()
{
    //setlocale(LC_ALL, "");    

    BMPReader bmp;
    std::string fileName;    

    do
    {
        switch (menu())
        {
            case 0: return;
            case 1:
            {
                cout << "Input file name: ";
                cin >> fileName;                
                bmp.load(fileName);
                bmp.info();
                system("PAUSE");
                break;
            }
            case 2:
            {
                if (bmp.empty())
                    cout << ".bmp is empty!!" << endl;
                else
                {
                    bmp.display();
                    bmp.open();
                }                
                system("PAUSE");                
                break;
            }
            case 3:
            {
                bmp.info();
                system("PAUSE");
                break;
            }case 4:
            {
                if (bmp.empty())
                    cout << ".bmp is empty!!" << endl;
                else
                    bmp.clear();
                system("PAUSE");
                break;
            }
        }
    } while (true);

   
}

int menu()
{
    int selected_item = 1;
    char key;
    do
    {
        system("CLS");
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        for (int i = 1; i <= MENU_ITEMS.size(); i++)
        {
            cout << (i == selected_item ? "[" : " ");
            cout << i << ". ";
            cout.width(32);
            cout << std::left;
            if (i == selected_item)SetConsoleTextAttribute(hConsole, 0x70);
            cout << MENU_ITEMS.at(i);
            SetConsoleTextAttribute(hConsole, 0x07);
            cout << (i == selected_item ? "  ]" : " ");
            cout << endl;
        }
        key = _getch();

        switch (key)
        {
        case 72: selected_item--; break;
        case 80: selected_item++; break;
        case 13: return selected_item;
        case 27: return 0;
        }
        if (selected_item == MENU_ITEMS.size() + 1)selected_item = 1;
        if (selected_item == 0)selected_item = MENU_ITEMS.size();
    } while (key != 27);
    return 0;
}



