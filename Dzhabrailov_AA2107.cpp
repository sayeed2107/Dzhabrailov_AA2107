#include <iostream>
#include <cmath>
#include <string>
#include <fstream>

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
    do
    {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Enter pipe lenght: ";
        cin >> p.length;
    } while (cin.fail() || p.length == 0);
    do
    {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Enter pipe diameter: ";
        cin >> p.diameter;
    } while (cin.fail() || p.diameter == 0);

    do
    {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Enter pipe status(Is it working or not, enter '1' or '0'): ";
        cin >> p.status;
    } while (cin.fail());

    return p;
}

void PrintPipe(const Pipe &p)
{
    cout << "Pipe #1" << endl;
    cout << "Lenght:" << p.length << "\tDiameter:" << p.diameter << "\tStatus:" << p.status << endl;
}

CS CreateNewCS()
{
    CS new_station;
    cout << "Enter CS name: ";
    cin.clear();
    cin.ignore(256, '\n');
    getline(cin, new_station.name);
    do
    {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Enter the amount of workshops in CS: ";
        cin >> new_station.workshops;
    } while (cin.fail());
    do
    {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Enter the amount of active workshops in CS: ";
        cin >> new_station.active_workshops;
    } while (cin.fail() || new_station.active_workshops > new_station.workshops);
    new_station.efficiency = (float)new_station.active_workshops / new_station.workshops * 100;
    return new_station;
}

void PrintCS(const CS &s)
{
    cout << "Comressor station #1" << endl;
    cout << "Name:" << s.name << "\tWorkshops:" << s.workshops << "\tActive workshops:" << s.active_workshops << "\tEfficiency:" << round(s.efficiency) << "%\n";
}

void ViewObjects(const Pipe &p, const CS &station)
{
    if (p.length != 0)
    {
        PrintPipe(p);
    }
    if (station.workshops != 0 && p.length != 0)
    {
        cout << "\n";
    }
    if (station.workshops != 0)
    {
        PrintCS(station);
    }
    if (p.length == 0 && station.workshops == 0)
    {
        cout << "Nothing to view, please create new objects. " << endl;
    }
}

Pipe EditPipe(Pipe &p)
{
    if (p.length == 0)
    {
        cout << "There are no pipes, pleaese create a new pipe." << endl;
        return p;
    }

    bool old_status = p.status;
    do
    {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Pleaese, enter new status for the pipe (Is it working or not, enter '1' or '0'): ";
        cin >> p.status;
    } while (cin.fail());
    if (old_status == p.status)
    {
        cout << "Nothing was changed" << endl;
    }
    else
    {
        cout << "Changes were applied!" << endl;
    }

    return p;
}

CS EditCS(CS &station)
{
    if (station.workshops == 0)
    {
        cout << "There are no CS, pleaese create a new CS." << endl;
        return station;
    }

    int old_active_workshops = station.active_workshops;

    do
    {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Please, enter new amount of active workshops: " << endl;
        cin >> station.active_workshops;
    } while (cin.fail() || station.active_workshops > station.workshops);
    if (old_active_workshops == station.active_workshops)
    {
        cout << "Nothing was changed" << endl;
    }
    else
    {
        station.efficiency = (float)station.active_workshops / station.workshops * 100;
        cout << "Changes were applied!" << endl;
    }

    return station;
}

int SaveFile(const Pipe &p, const CS &s)
{
    if (p.length == 0 && s.workshops == 0)
    {
        cout << "Nothing to save, please create new objects. " << endl;
        return 0;
    }
    ofstream fout;
    fout.open("DataForHuman.txt", ios::out);
    if (p.length != 0)
    {
        fout << "Pipe #1" << endl;
        fout << "Lenght:" << p.length << "\tDiameter:" << p.diameter << "\tStatus:" << p.status << endl;
    }
    if (s.workshops != 0 && p.length != 0)
    {
        fout << "\n";
    }
    if (s.workshops != 0)
    {
        fout << "Comressor station #1" << endl;
        fout << "Name:" << s.name << "\tWorkshops:" << s.workshops << "\tActive workshops:" << s.active_workshops << "\tEfficiency:" << round(s.efficiency) << "%\n";
    }
    fout.close();

    fout.open("DataForProgramm.txt", ios::out);
    if (s.workshops != 0 && p.length != 0)
    {
        fout << p.length << endl
             << p.diameter << endl
             << p.status << endl;
        fout << s.name << endl
             << s.workshops << endl
             << s.active_workshops << endl
             << round(s.efficiency);
    }
    if (p.length != 0 && s.workshops == 0)
    {
        fout << p.length << endl
             << p.diameter << endl
             << p.status << endl;
    }
    if (s.workshops != 0 && p.length == 0)
    {
        fout << endl
             << endl
             << endl;
        fout << s.name << endl
             << s.workshops << endl
             << s.active_workshops << endl
             << round(s.efficiency);
    }

    fout.close();
    cout << "File was succefully saved!" << endl;
    return 0;
}

Pipe LoadPipe()
{
    Pipe p;
    ifstream check("DataForProgramm.txt");
    if (check.bad() == true)
    {
        cout << "No existing file to load, please create a new file" << endl;
        return p;
    }

    ifstream fin;
    fin.open("DataForProgramm.txt", ios::in);
    fin >> p.length;
    fin >> p.diameter;
    fin >> p.status;
    fin.close();
    return p;
}

CS LoadCS()
{
    CS s;
    ifstream check("DataForProgramm.txt");
    if (check.bad() == true)
    {
        cout << "No existing file to load, please create a new file" << endl;
        return s;
    }

    ifstream fin;
    fin.open("DataForProgramm.txt", ios::in);
    fin.ignore(256, '\n');
    fin.ignore(256, '\n');
    fin.ignore(256, '\n');
    fin >> s.name;
    fin >> s.workshops;
    fin >> s.active_workshops;
    fin >> s.efficiency;
    fin.close();
    return s;
}

void PrintMenu()
{
    cout << "1. Add new pipe" << endl
         << "2. Add new CS" << endl
         << "3. View all objects" << endl
         << "4. Edit pipe" << endl
         << "5. Edit CS" << endl
         << "6. Save to the file" << endl
         << "7. Load from the file" << endl
         << "0. Exit" << endl
         << "Choose action: ";
}

int main()
{
    Pipe p;
    p.length = 0;
    CS station;
    while (1)
    {
        cout << "\n";
        PrintMenu();
        int i;
        cin >> i;
        cout << "\n";
        switch (i)
        {
        case 1:
        {
            p = CreateNewPipe();
            break;
        }
        case 2:
        {
            station = CreateNewCS();
            break;
        }
        case 3:
        {
            ViewObjects(p, station);
            break;
        }
        case 4:
        {
            EditPipe(p);
            break;
        }
        case 5:
        {
            EditCS(station);
            break;
        }
        case 6:
        {
            SaveFile(p, station);
            break;
        }
        case 7:
        {
            p = LoadPipe();
            station = LoadCS();
            break;
        }
        case 0:
        {
            return 0;
        }
        default:
        {
            cout << "Wrong action";
        }
        }
    }
    return 0;
}