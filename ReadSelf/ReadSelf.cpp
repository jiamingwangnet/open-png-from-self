#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

//26

int main()
{
    const std::string imageNum = "00";

    CHAR czTempPath[MAX_PATH] = { 0 };
    GetTempPathA(MAX_PATH, czTempPath);

    std::string pass = "pass1234word";
    std::string passenter;

    std::cout << ">> ";
    std::cin >> passenter;

    if (passenter != pass) return 0;

    std::ifstream in;
    in.open("./readimage" + imageNum + ".exe", std::ios::binary);
    int i = 0;
    int png[4];
    int counter = 0;
    bool isInPng = false;

    std::string pngcontent = "";

    std::string sPath = czTempPath;
    sPath += "readimage" + imageNum + ".png";

    std::ofstream out;
    out.open(sPath.c_str(), std::ios::binary);

    out << (char)0x89 << (char)0x50 << (char)0x4E << (char)0x47;
    
    while (!in.eof())
    {
        if (!isInPng)
        {
            png[counter] = (int)in.get();
            i++;
            counter++;
            if (counter == 4)
            {
                counter = 0;
            }
        }
        else
        {
            std::string str(1, in.get());
            pngcontent.append(str);
        }

        if (png[0] == 0x89 && png[1] == 0x50 && png[2] == 0x4E && png[3] == 0x47)
        {
            isInPng = true;
        }
    }

    out << pngcontent;

    in.close();
    out.close();

    ShellExecuteA(NULL, "open", sPath.c_str(), "", czTempPath, SW_SHOW);

    std::cout << ">> ";
    std::string close;
    std::cin >> close;

    std::remove(sPath.c_str());

    return 0;
}