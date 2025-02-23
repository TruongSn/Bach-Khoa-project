#include "header.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Hàm đọc dữ liệu vào đầu file
bool readFile(string filename, int LF1[17], int LF2[17], int &exp1, int &exp2, int &t1, int &t2, int &E)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        return false;
    }
    string line;
    getline(file, line);
    stringstream ss1(line.substr(1, line.size() - 2));
    for (int i = 0; i < 17; i++)
    {
        ss1 >> LF1[i];
    }

    getline(file, line);
    stringstream ss2(line.substr(1, line.size() - 2));
    for (int i = 0; i < 17; i++)
    {
        ss2 >> LF2[i];
    }
    file >> exp1 >> exp2;
    file >> t1 >> t2;
    file >> E;
    file.close();
    return true;
}

// Hàm tính sức mạnh đội quân
int gatherForce(int LF1[17], int LF2[17])
{
    int weights[17] = {1, 2, 3, 4, 5, 7, 8, 9, 10, 12, 15, 18, 20, 30, 40, 50, 70};
    int strength1 = 0;
    int strength2 = 0;
    for (int i = 0; i < 17; i++)
    {
        strength1 += LF1[i] * weights[i];
        strength2 += LF2[i] * weights[i];
    }
    return strength1 + strength2;
}

// Hàm giải mã nghi binh
string determineRightTarget(string target)
{
    vector<int> numbers;
    string extractedText = "";
    for (char c : target)
    {
        if (isdigit(c))
        {
            numbers.push_back(c - '0');
        }
        else
        {
            extractedText += c;
        }
    }

    if (numbers.size() == 1)
    {
        return extractedText;
    }

    if (numbers.size() == 2)
    {
        return "Buon Ma Thuot";
    }

    if (numbers.size() == 3)
    {
        return "National Route 14";
    }
    return "INVALID";
}

// Hàm giải mã thông điệp
string decodeTarget(string message, int exp1, int exp2)
{
    int shift = (exp1 + exp2) % 26;
    if (exp1 >= 300 && exp2 >= 300)
    {
        for (char &c : message)
        {
            if (isalpha(c))
            {
                c = (c - shift < 'A') ? c - shift + 26 : c - shift;
            }
        }
    }
    else
    {
        reverse(message.begin(), message.end());
    }
    return message;
}

// Hàm quản lý hậu cần
void manageLogistics(int LF1, int LF2, int exp1, int exp2, int &t1, int &t2, int e)
{
    int total = t1 + t2;
    t1 = (LF1 * total) / (LF1 + LF2) * (1 + (exp1 - exp2) / 100.0);
    t2 = total - t1;
    if (e >= 1 && e <= 9)
    {
        t1 -= (t1 * e / 100);
        t2 -= (t2 * e / 200);
    }
    else if (e >= 10 && e <= 29)
    {
        t1 += e * 50;
        t2 += e * 50;
    }
    else if (e >= 30 && e <= 59)
    {
        t1 += (t1 * e / 200);
        t2 += (t2 * e / 500);
    }
}

int planAttack(int LF1, int LF2, int exp1, int exp2, int t1, int t2, int battleField[10][10])
{
    int s = (LF1 + LF2) + (exp1 + exp2) * 5 + (t1 + t2) * 2;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (i % 2 == 0)
            {
                s -= (battleField[i][j] * 2) / 3;
            }
            else
            {
                s -= (battleField[i][j] * 3) / 2;
            }
        }
    }
    return s;
}

// Hàm bổ sung tiếp tế
int resupply(int shortfall, int supply[5][5])
{
    vector<int> flatSupply;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            flatSupply.push_back(supply[i][j]);
        }
    }
    sort(flatSupply.begin(), flatSupply.end());

    int total = 0;
    for (int i = 0; i < 5; i++)
    {
        total += flatSupply[i];
        if (total >= shortfall)
        {
            return total;
        }
    }
    return -1;
}



int main()
{
    // Khai báo biến
    int LF1[17], LF2[17], EXP1, EXP2, T1, T2, E;

    // Đọc dữ liệu từ file
    string filename = "readFile.txt";
    if (!readFile(filename, LF1, LF2, EXP1, EXP2, T1, T2, E))
    {
        cout << "Không thể đọc dữ liệu từ file!" << endl;
        return 1;
    }

    // 1️⃣ Tính tổng sức mạnh quân đội
    int totalStrength = gatherForce(LF1, LF2);
    cout << "Tổng sức mạnh quân đội: " << totalStrength << endl;

    // 2️⃣ Giải mã nghi binh
    string fakeTarget = "Ple9i␣ku5";
    string realTarget = determineRightTarget(fakeTarget);
    cout << "Mục tiêu thực sự: " << realTarget << endl;

    // 3️⃣ Giải mã thông điệp quân sự
    string encodedMessage = "Zwg Hwg";
    string decodedMessage = decodeTarget(encodedMessage, EXP1, EXP2);
    cout << "Thông điệp giải mã: " << decodedMessage << endl;

    // 4️⃣ Quản lý hậu cần
    manageLogistics(totalStrength / 2, totalStrength / 2, EXP1, EXP2, T1, T2, E);
    cout << "Tiếp tế sau điều chỉnh - Quân đoàn 1: " << T1 << ", Quân đoàn 2: " << T2 << endl;

    // 5️⃣ Lập kế hoạch tấn công (Giả lập ma trận chiến sự)
    int battleField[10][10] = {
        {106, 15, 20, 25, 305, 635, 540, 145, 50, 55},
        {25, 18, 24, 330, 36, 442, 48, 54, 660, 665},
        {14, 21, 28, 35, 452, 49, 56, 63, 70, 77},
        {162, 24, 323, 404, 484, 60, 40, 72, 80, 88},
        {181, 27, 36, 52, 543, 63, 72, 81, 90, 99},
        {5, 30, 40, 501, 602, 70, 80, 90, 100, 110},
        {22, 33, 442, 55, 66, 77, 58, 99, 10, 121},
        {24, 36, 48, 60, 72, 84, 96, 108, 20, 132},
        {264, 39, 525, 65, 78, 91, 104, 70, 130, 143},
        {28, 42, 56, 50, 84, 98, 125, 126, 140, 154}};
    int remainingStrength = planAttack(totalStrength / 2, totalStrength / 2, EXP1, EXP2, T1, T2, battleField);
    cout << "Sức mạnh còn lại sau trận đánh: " << remainingStrength << endl;

    // 6️⃣ Bổ sung tiếp tế nếu cần
    if (remainingStrength < 0)
    {
        int supply[5][5] = {
            {150, 200, 180, 90, 110},
            {70, 80, 120, 140, 160},
            {220, 240, 200, 190, 130},
            {100, 110, 300, 280, 320},
            {170, 210, 260, 230, 290}};
        int addedSupply = resupply(abs(remainingStrength), supply);
        cout << "Tiếp tế bổ sung: " << addedSupply << endl;
    }
    else
    {
        cout << "Quân đội đủ sức mạnh để chiến thắng!" << endl;
    }

    return 0;
}
