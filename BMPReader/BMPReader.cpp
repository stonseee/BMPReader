#include"BMPReader.h"

void BMPReader::load(const std::string& fileName)
{
    this->fileName = fileName;
    std::ifstream fin;
    fin.open(fileName, std::ios::binary);
    char* buffer = new char[4];

    if (fin.is_open())
    {
        fin.read(buffer, 2);
        header.bfType = BMPReader::sum_by_binary(BMPReader::ascii_comparison(buffer[1]), BMPReader::ascii_comparison(buffer[0]));
        fin.read(buffer, 4);
        header.bfSize = BMPReader::sum_by_binary(BMPReader::ascii_comparison(buffer[3]), BMPReader::ascii_comparison(buffer[2]), BMPReader::ascii_comparison(buffer[1]), BMPReader::ascii_comparison(buffer[0]));
        fin.read(buffer, 2);
        header.bfReserved1 = BMPReader::sum_by_binary(BMPReader::ascii_comparison(buffer[1]), BMPReader::ascii_comparison(buffer[0]));
        fin.read(buffer, 2);
        header.bfReserved2 = BMPReader::sum_by_binary(BMPReader::ascii_comparison(buffer[1]), BMPReader::ascii_comparison(buffer[0]));
        fin.read(buffer, 4);
        header.bfOffBits = BMPReader::sum_by_binary(BMPReader::ascii_comparison(buffer[3]), BMPReader::ascii_comparison(buffer[2]), BMPReader::ascii_comparison(buffer[1]), BMPReader::ascii_comparison(buffer[0]));

        fin.read(buffer, 4);
        infoHeader.biSize = BMPReader::sum_by_binary(BMPReader::ascii_comparison(buffer[3]), BMPReader::ascii_comparison(buffer[2]), BMPReader::ascii_comparison(buffer[1]), BMPReader::ascii_comparison(buffer[0]));
        fin.read(buffer, 4);
        infoHeader.biWidth = BMPReader::sum_by_binary(BMPReader::ascii_comparison(buffer[3]), BMPReader::ascii_comparison(buffer[2]), BMPReader::ascii_comparison(buffer[1]), BMPReader::ascii_comparison(buffer[0]));
        fin.read(buffer, 4);
        infoHeader.biHeight = BMPReader::sum_by_binary(BMPReader::ascii_comparison(buffer[1]), BMPReader::ascii_comparison(buffer[0]));
        fin.read(buffer, 2);
        infoHeader.biPlanes = BMPReader::sum_by_binary(BMPReader::ascii_comparison(buffer[1]), BMPReader::ascii_comparison(buffer[0]));
        fin.read(buffer, 2);
        infoHeader.biBitCount = BMPReader::sum_by_binary(BMPReader::ascii_comparison(buffer[3]), BMPReader::ascii_comparison(buffer[2]), BMPReader::ascii_comparison(buffer[1]), BMPReader::ascii_comparison(buffer[0]));
        fin.read(buffer, 4);
        infoHeader.biCompression = BMPReader::sum_by_binary(BMPReader::ascii_comparison(buffer[3]), BMPReader::ascii_comparison(buffer[2]), BMPReader::ascii_comparison(buffer[1]), BMPReader::ascii_comparison(buffer[0]));
        fin.read(buffer, 4);
        infoHeader.biSizeImage = BMPReader::sum_by_binary(BMPReader::ascii_comparison(buffer[3]), BMPReader::ascii_comparison(buffer[2]), BMPReader::ascii_comparison(buffer[1]), BMPReader::ascii_comparison(buffer[0]));
        fin.read(buffer, 4);
        infoHeader.biXPelsPerMeter = BMPReader::BMPReader::sum_by_binary(BMPReader::ascii_comparison(buffer[3]), BMPReader::ascii_comparison(buffer[2]), BMPReader::ascii_comparison(buffer[1]), BMPReader::ascii_comparison(buffer[0]));
        fin.read(buffer, 4);
        infoHeader.biYPelsPerMeter = BMPReader::sum_by_binary(BMPReader::ascii_comparison(buffer[3]), BMPReader::ascii_comparison(buffer[2]), BMPReader::ascii_comparison(buffer[1]), BMPReader::ascii_comparison(buffer[0]));
        fin.read(buffer, 4);
        infoHeader.biClrUsed = BMPReader::sum_by_binary(BMPReader::ascii_comparison(buffer[3]), BMPReader::ascii_comparison(buffer[2]), BMPReader::ascii_comparison(buffer[1]), BMPReader::ascii_comparison(buffer[0]));
        fin.read(buffer, 4);
        infoHeader.biClrImportant = BMPReader::sum_by_binary(BMPReader::ascii_comparison(buffer[3]), BMPReader::ascii_comparison(buffer[2]), BMPReader::ascii_comparison(buffer[1]), BMPReader::ascii_comparison(buffer[0]));

        rgb = new RGBQUAD * [infoHeader.biWidth];

        for (int i = 0; i < infoHeader.biWidth; i++)
            rgb[i] = new RGBQUAD[infoHeader.biHeight];

        for (int i = 0; i < infoHeader.biWidth; i++)
        {
            for (int j = 0; j < infoHeader.biHeight; j++)
            {
                fin.read(buffer, 3);
                rgb[i][j].rgbBlue = ascii_comparison(buffer[0]);
                rgb[i][j].rgbGreen = ascii_comparison(buffer[1]);
                rgb[i][j].rgbRed = ascii_comparison(buffer[2]);
            }
        }

        fin.close();
        delete[] buffer;
    }
    else
    {
        std::cerr << "Error: file not found" << endl;
    }
}

void BMPReader::info()
{
    cout << "header.bfType               " << header.bfType << endl;
    cout << "header.bfSize               " << header.bfSize << endl;
    cout << "header.bfReserved1          " << header.bfReserved1 << endl;
    cout << "header.bfReserved2          " << header.bfReserved2 << endl;
    cout << "header.bfOffBits            " << header.bfOffBits << endl;
    cout << "infoHeader.biSize           " << infoHeader.biSize << endl;
    cout << "infoHeader.biWidth          " << infoHeader.biWidth << endl;
    cout << "infoHeader.biHeight         " << infoHeader.biHeight << endl;
    cout << "infoHeader.biPlanes         " << infoHeader.biPlanes << endl;
    cout << "infoHeader.biBitCount       " << infoHeader.biBitCount << endl;
    cout << "infoHeader.biCompression    " << infoHeader.biCompression << endl;
    cout << "infoHeader.biSizeImage      " << infoHeader.biSizeImage << endl;
    cout << "infoHeader.biXPelsPerMeter  " << infoHeader.biXPelsPerMeter << endl;
    cout << "infoHeader.biYPelsPerMeter  " << infoHeader.biYPelsPerMeter << endl;
    cout << "infoHeader.biClrUsed        " << infoHeader.biClrUsed << endl;
    cout << "infoHeader.biClrImportant   " << infoHeader.biClrImportant << endl;
}

void BMPReader::display()
{
    for (int i = infoHeader.biWidth - 1; i >= 0; i--)
    {
        for (int j = 0; j < infoHeader.biHeight; j++)
        {
            if (rgb[i][j].rgbRed == 0 && rgb[i][j].rgbGreen == 0 && rgb[i][j].rgbBlue == 0)
                cout << "0 ";
            else
                cout << "- ";
        }
        cout << endl;
    }
}

void BMPReader::open()
{
    std::string command = "mspaint " + this->fileName;
    system(command.c_str());
}

void BMPReader::clear()
{
    header.bfType = 0;
    header.bfSize = 0;
    header.bfReserved1 = 0;
    header.bfReserved2 = 0;
    header.bfOffBits = 0;

    infoHeader.biSize = 0;
    infoHeader.biWidth = 0;
    infoHeader.biHeight = 0;
    infoHeader.biPlanes = 0;
    infoHeader.biBitCount = 0;
    infoHeader.biCompression = 0;
    infoHeader.biSizeImage = 0;
    infoHeader.biXPelsPerMeter = 0;
    infoHeader.biYPelsPerMeter = 0;
    infoHeader.biClrUsed = 0;
    infoHeader.biClrImportant = 0;

    this->fileName.resize(0);
    delete rgb;
}

bool BMPReader::empty()
{
    if (this->fileName.empty())
        return true;
    else
        return false;
}

int BMPReader::ascii_comparison(char sym)
{
    if (sym == (char)128)return 128;
    if (sym == (char)129)return 129;

    if (sym == (char)130)return 130;
    if (sym == (char)131)return 131;
    if (sym == (char)132)return 132;
    if (sym == (char)133)return 133;
    if (sym == (char)134)return 134;
    if (sym == (char)135)return 135;
    if (sym == (char)136)return 136;
    if (sym == (char)137)return 137;
    if (sym == (char)138)return 138;
    if (sym == (char)139)return 139;

    if (sym == (char)140)return 140;
    if (sym == (char)141)return 141;
    if (sym == (char)142)return 142;
    if (sym == (char)143)return 143;
    if (sym == (char)144)return 144;
    if (sym == (char)145)return 145;
    if (sym == (char)146)return 146;
    if (sym == (char)147)return 147;
    if (sym == (char)148)return 148;
    if (sym == (char)149)return 149;

    if (sym == (char)150)return 150;
    if (sym == (char)151)return 151;
    if (sym == (char)152)return 152;
    if (sym == (char)153)return 153;
    if (sym == (char)154)return 154;
    if (sym == (char)155)return 155;
    if (sym == (char)156)return 156;
    if (sym == (char)157)return 157;
    if (sym == (char)158)return 158;
    if (sym == (char)159)return 159;

    if (sym == (char)160)return 160;
    if (sym == (char)161)return 161;
    if (sym == (char)162)return 162;
    if (sym == (char)163)return 163;
    if (sym == (char)164)return 164;
    if (sym == (char)165)return 165;
    if (sym == (char)166)return 166;
    if (sym == (char)167)return 167;
    if (sym == (char)168)return 168;
    if (sym == (char)169)return 169;

    if (sym == (char)170)return 170;
    if (sym == (char)171)return 171;
    if (sym == (char)172)return 172;
    if (sym == (char)173)return 173;
    if (sym == (char)174)return 174;
    if (sym == (char)175)return 175;
    if (sym == (char)176)return 176;
    if (sym == (char)177)return 177;
    if (sym == (char)178)return 178;
    if (sym == (char)179)return 179;

    if (sym == (char)180)return 180;
    if (sym == (char)181)return 181;
    if (sym == (char)182)return 182;
    if (sym == (char)183)return 183;
    if (sym == (char)184)return 184;
    if (sym == (char)185)return 185;
    if (sym == (char)186)return 186;
    if (sym == (char)187)return 187;
    if (sym == (char)188)return 188;
    if (sym == (char)189)return 189;

    if (sym == (char)190)return 190;
    if (sym == (char)191)return 191;
    if (sym == (char)192)return 192;
    if (sym == (char)193)return 193;
    if (sym == (char)194)return 194;
    if (sym == (char)195)return 195;
    if (sym == (char)196)return 196;
    if (sym == (char)197)return 197;
    if (sym == (char)198)return 198;
    if (sym == (char)199)return 199;

    if (sym == (char)200)return 200;
    if (sym == (char)201)return 201;
    if (sym == (char)202)return 202;
    if (sym == (char)203)return 203;
    if (sym == (char)204)return 204;
    if (sym == (char)205)return 205;
    if (sym == (char)206)return 206;
    if (sym == (char)207)return 207;
    if (sym == (char)208)return 208;
    if (sym == (char)209)return 209;

    if (sym == (char)210)return 210;
    if (sym == (char)211)return 211;
    if (sym == (char)212)return 212;
    if (sym == (char)213)return 213;
    if (sym == (char)214)return 214;
    if (sym == (char)215)return 215;
    if (sym == (char)216)return 216;
    if (sym == (char)217)return 217;
    if (sym == (char)218)return 218;
    if (sym == (char)219)return 219;

    if (sym == (char)220)return 220;
    if (sym == (char)221)return 221;
    if (sym == (char)222)return 222;
    if (sym == (char)223)return 223;
    if (sym == (char)224)return 224;
    if (sym == (char)225)return 225;
    if (sym == (char)226)return 226;
    if (sym == (char)227)return 227;
    if (sym == (char)228)return 228;
    if (sym == (char)229)return 229;

    if (sym == (char)230)return 230;
    if (sym == (char)231)return 231;
    if (sym == (char)232)return 232;
    if (sym == (char)233)return 233;
    if (sym == (char)234)return 234;
    if (sym == (char)235)return 235;
    if (sym == (char)236)return 236;
    if (sym == (char)237)return 237;
    if (sym == (char)238)return 238;
    if (sym == (char)239)return 239;

    if (sym == (char)240)return 240;
    if (sym == (char)241)return 241;
    if (sym == (char)242)return 242;
    if (sym == (char)243)return 243;
    if (sym == (char)244)return 244;
    if (sym == (char)245)return 245;
    if (sym == (char)246)return 246;
    if (sym == (char)247)return 247;
    if (sym == (char)248)return 248;
    if (sym == (char)249)return 249;

    if (sym == (char)250)return 250;
    if (sym == (char)251)return 251;
    if (sym == (char)252)return 252;
    if (sym == (char)253)return 253;
    if (sym == (char)254)return 254;
    if (sym == (char)255)return 255;
    else return sym;
}

int BMPReader::sum_by_binary(int a, int b)
{
    int* binaryA = new int[8] {};
    int* binaryB = new int[8] {};
    int* binaryC = new int[16] {};
    int result = 0;

    for (int j = 128, i = 0; i < 8; j /= 2)
    {
        if (a - j >= 0)
        {
            a -= j;
            binaryA[i] = 1;
        }
        else
        {
            binaryA[i] = 0;
        }
        ++i;
    }

    for (int j = 128, i = 0; i < 8; j /= 2)
    {
        if (b - j >= 0)
        {
            b -= j;
            binaryB[i] = 1;
        }
        else
        {
            binaryB[i] = 0;
        }
        ++i;
    }

    for (int i = 0; i < 16; ++i)
    {
        if (i < 8)
        {
            binaryC[i] = binaryA[i];
        }
        if (i >= 8)
        {
            binaryC[i] = binaryB[i - 8];
        }
    }

    for (int i = 0, j = 15; i < 16; i++)
    {
        result += binaryC[i] * pow(2, j);
        --j;
    }

    delete[] binaryC;
    delete[] binaryB;
    delete[] binaryA;

    return result;
}

int BMPReader::sum_by_binary(int a, int b, int c, int d)
{
    int* binaryA = new int[8] {};
    int* binaryB = new int[8] {};
    int* binaryC = new int[8] {};
    int* binaryD = new int[8] {};
    int* binaryE = new int[32] {};
    int result = 0;

    for (int j = 128, i = 0; i < 8; j /= 2)
    {
        if (a - j >= 0)
        {
            a -= j;
            binaryA[i] = 1;
        }
        else
        {
            binaryA[i] = 0;
        }
        ++i;
    }

    for (int j = 128, i = 0; i < 8; j /= 2)
    {
        if (b - j >= 0)
        {
            b -= j;
            binaryB[i] = 1;
        }
        else
        {
            binaryB[i] = 0;
        }
        ++i;
    }

    for (int j = 128, i = 0; i < 8; j /= 2)
    {
        if (c - j >= 0)
        {
            c -= j;
            binaryC[i] = 1;
        }
        else
        {
            binaryC[i] = 0;
        }
        ++i;
    }

    for (int j = 128, i = 0; i < 8; j /= 2)
    {
        if (d - j >= 0)
        {
            d -= j;
            binaryD[i] = 1;
        }
        else
        {
            binaryD[i] = 0;
        }
        ++i;
    }

    for (int i = 0; i < 32; ++i)
    {
        if (i < 8)
        {
            binaryE[i] = binaryA[i];
        }
        if (i >= 8 && i < 16)
        {
            binaryE[i] = binaryB[i - 8];
        }
        if (i >= 16 && i < 24)
        {
            binaryE[i] = binaryC[i - 16];
        }
        if (i >= 24 && i < 32)
        {
            binaryE[i] = binaryD[i - 24];
        }
    }

    for (int i = 0, j = 31; i < 32; i++)
    {
        result += binaryE[i] * pow(2, j);
        --j;
    }

    delete[] binaryE;
    delete[] binaryD;
    delete[] binaryC;
    delete[] binaryB;
    delete[] binaryA;

    return result;
}