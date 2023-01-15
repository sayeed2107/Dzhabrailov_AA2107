#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <map>

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

int GetCorrectNumber(int min, int max)
{
    int i;
    while ((cin >> i).fail() || i < min || i > max)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Choose action(0-7): ";
    }
    return i;
}

void GetCorrectStatus(Pipe &p)
{
    do
    {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Enter pipe status(Is it working or not, enter '1' or '0'): ";
        cin >> p.status;
    } while (cin.fail());
}

void GetCorrectActWorkshops(CS &st)
{
    do
    {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Enter the amount of active workshops in CS: ";
        cin >> st.active_workshops;
    } while (cin.fail() || st.active_workshops > st.workshops || st.active_workshops < 0);
}

void AddToPipeMap(Pipe &p, map<int, Pipe> &PipeMap)
{
    if (PipeMap.find(1) != PipeMap.end())
    {
        int j = PipeMap.rbegin()->first;
        PipeMap.insert(make_pair(j + 1, p));
    }
    else
    {
        int j = 1;
        PipeMap.insert(make_pair(j, p));
    }
}

void ShowPipeMap(map<int, Pipe> &PipeMap)
{

    if (PipeMap.find(1) != PipeMap.end())
    {
        int max = PipeMap.rbegin()->first;
        for (int i = 1; i <= max; ++i)
        {
            Pipe p = PipeMap[i];
            cout << "Pipe #" << i << endl;
            cout << "Length:" << p.length << "\tDiameter:" << p.diameter << "\tStatus:" << p.status << endl;
        }
    }
    else
    {
        cout << "Nothing to view, please create new objects. " << endl;
    }
}

void EditPipeMap(map<int, Pipe> &PipeMap)
{
    int i;
    cout << "Enter name of the tube to change: ";
    cin >> i;
    Pipe p = PipeMap[i];

    if (p.length == 0)
    {
        cout << "There are no pipes, pleaese create a new pipe." << endl;
        return;
    }

    bool old_status = p.status;
    GetCorrectStatus(p);
    if (old_status == p.status)
    {
        cout << "Nothing was changed" << endl;
    }
    else
    {
        cout << "Changes were applied!" << endl;
    }

    PipeMap[i] = p;
}

istream &operator>>(istream &in, Pipe &p)
{
    do
    {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Enter pipe length: ";
        cin >> p.length;
    } while (cin.fail() || p.length <= 0);
    do
    {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Enter pipe diameter: ";
        cin >> p.diameter;
    } while (cin.fail() || p.diameter <= 0);

    GetCorrectStatus(p);

    return in;
}

istream &operator>>(istream &in, CS &st)
{
    cout << "Enter CS name: ";
    cin.clear();
    cin.ignore(256, '\n');
    getline(cin, st.name);
    do
    {
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Enter the amount of workshops in CS: ";
        cin >> st.workshops;
    } while (cin.fail() || st.workshops <= 0);
    GetCorrectActWorkshops(st);
    st.efficiency = (float)st.active_workshops / st.workshops * 100;
    return in;
}

ostream &operator<<(ostream &out, const Pipe &p)
{
    out << "Pipe #1" << endl;
    out << "Length:" << p.length << "\tDiameter:" << p.diameter << "\tStatus:" << p.status << endl;
    return out;
}

ostream &operator<<(ostream &out, const CS &st)
{
    out << "Compressor station #1" << endl;
    out << "Name:" << st.name << "\tWorkshops:" << st.workshops << "\tActive workshops:" << st.active_workshops << "\tEfficiency:" << round(st.efficiency) << "%\n";
    return out;
}

void ViewObjects(const Pipe &p, const CS &st)
{
    if (p.length != 0)
    {
        cout << p;
    }
    if (st.workshops != 0 && p.length != 0)
    {
        cout << "\n";
    }
    if (st.workshops != 0)
    {
        cout << st;
    }
    if (p.length == 0 && st.workshops == 0)
    {
        cout << "Nothing to view, please create new objects. " << endl;
    }
}

void EditPipe(Pipe &p)
{
    if (p.length == 0)
    {
        cout << "There are no pipes, pleaese create a new pipe." << endl;
        return;
    }

    bool old_status = p.status;
    GetCorrectStatus(p);
    if (old_status == p.status)
    {
        cout << "Nothing was changed" << endl;
    }
    else
    {
        cout << "Changes were applied!" << endl;
    }
}

CS EditCS(CS &station)
{
    if (station.workshops == 0)
    {
        cout << "There are no CS, pleaese create a new CS." << endl;
        return station;
    }

    int old_active_workshops = station.active_workshops;

    GetCorrectActWorkshops(station);
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
        fout << p << endl;
    }
    if (s.workshops != 0 && p.length != 0)
    {
        fout << "\n";
    }
    if (s.workshops != 0)
    {
        fout << s << endl;
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
    Pipe p = {};
    CS st = {};
    map<int, Pipe> PipeMap;

    while (1)
    {
        cout << "\n";
        PrintMenu();
        switch (GetCorrectNumber(0, 7))
        {
        case 1:
        {
            cin >> p;
            AddToPipeMap(p, PipeMap);
            break;
        }
        case 2:
        {
            cin >> st;
            break;
        }
        case 3:
        {
            ShowPipeMap(PipeMap);
            break;
        }
        case 4:
        {
            EditPipeMap(PipeMap);
            break;
        }
        case 5:
        {
            EditCS(st);
            break;
        }
        case 6:
        {
            SaveFile(p, st);
            break;
        }
        case 7:
        {
            p = LoadPipe();
            st = LoadCS();
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