#include <iostream>
#include <cmath>

using namespace std;

struct Pipe
{
    float length;
    float diameter;
    bool status;
};

struct CS
{
    string name;
    int workshops;
    int active_workshops;
    float efficiency;
};

Pipe CreateNewPipe()
{
    Pipe p;
    cout << "Enter pipe lenght: ";
    cin >> p.length;
    cout << "Enter pipe diameter: ";
    cin >> p.diameter;
    cout << "Enter pipe status(Is it working or not, enter '1' or '0'): ";
    cin >> p.status;

    return p;
}

void PrintPipe(const Pipe &p)
{
    cout << "Lenght:" << p.length << "\tDiameter:" << p.diameter << "\tStatus:" << p.status << endl;
}

CS CreateNewCS()
{
    CS new_station;
    cout << "Enter CS name: ";
    cin >> new_station.name;
    cout << "Enter the amount of workshops in CS: ";
    cin >> new_station.workshops;
    cout << "Enter the amount of active workshops in CS: ";
    cin >> new_station.active_workshops;
    new_station.efficiency = (float)new_station.active_workshops / new_station.workshops * 100;
    return new_station;
}

void PrintCS(const CS &s)
{
    cout << "Name:" << s.name << "\tWorkshops:" << s.workshops << "\tActive workshops:" << s.active_workshops << "\tEfficiency:" << round(s.efficiency) << "%\n";
}

void PrintMenu()
{
    cout << "1. Add new pipe" << endl;
    cout << "2. Add new CS" << endl;
    cout << "3. View all objects" << endl;
    cout << "4. Edit pipe" << endl;
    cout << "5. Edit CS" << endl;
    cout << "6. Save to the file" << endl;
    cout << "7. Load from the file" << endl;
    cout << "0. Exit" << endl;
}

int main()
{
    Pipe TestPipe;
    CS TestCS;
    TestPipe = CreateNewPipe();
    PrintPipe(TestPipe);
    TestCS = CreateNewCS();
    PrintCS(TestCS);
    return 0;
}