#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> 

using namespace std;

enum Speciality { Physics, Math, Informatics }; 
string specialityStr[] = { "Գ����", "����������" , "�����������" }; 

struct Student
{
    string surname;
    int course;
    Speciality speciality;
    int physicsGrade;
    int mathGrade;
    int informaticsGrade;
    int halfbal;
};


// ��������� �������
void Create(Student* s, const int N);
void Print(const Student* s, const int N);
double CalculateAverage(const Student& s);
void ManualSort(Student* s, const int N);
void SortByAverage(Student* s, const int N);
void SortByCourse(Student* s, const int N);
void SortBySurname(Student* s, const int N);
int* IndexSort(Student* s, const int N);
void PrintIndexSorted(Student* s, int* I, const int N);
void SortForBinSearch(Student* s, const int N);
int BinSearch(const Student* s, const int N, const string& surname, const int course, const double halfbal); // ������ �������� ������� BinSearch


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251); 

    int N;
    cout << "������ ������� �������� N: ";
    cin >> N;

    Student* s = new Student[N];
    int menuItem;

    do
    {
        cout << "\n\n������� ��:\n";
        cout << " [1] - �������� ����� ��������\n";
        cout << " [2] - ���� ����� �� �����\n";
        cout << " [3] - ���������� ������\n";
        cout << " [4] - �������� ����������\n";
        cout << " [5] - ������� �����\n";
        cout << " [0] - �����\n";
        cout << "������ ��������: ";
        cin >> menuItem;

        switch (menuItem)
        {
        case 1:
            Create(s, N);
            break;
        case 2:
            Print(s, N);
            break;
        case 3:
            ManualSort(s, N);
            break;
        case 4: {
            int* indices = IndexSort(s, N);
            cout << "��� ���� ���������� ����������:\n";
            PrintIndexSorted(s, indices, N);
            delete[] indices;
            break;
        }
        case 5:
        {
            SortForBinSearch(s, N);
            string surname;
            int course;
            double halfbal;
            cout << "������ ������� ��� ������: ";
            cin >> surname;
            cout << "������ ���� ��� ������: ";
            cin >> course;
            cout << "������ ������� ��� ��� ������: ";
            cin >> halfbal;
            int result = BinSearch(s, N, surname, course, halfbal);
            if (result != -1)
            {
                cout << "�������� �������� �� ������� " << result + 1 << ".\n";
            }
            else
            {
                cout << "�������� �� ��������.\n";
            }
            break;
        }
        case 0:
            break;
        default:
            cout << "������� ����! ������ ����� � ����.\n";
        }
    } while (menuItem != 0);

    delete[] s;
    return 0;
}

void Create(Student* s, const int N)
{
    int speciality;
    for (int i = 0; i < N; i++) 
    {
        cout << "������� �" << i + 1 << ":\n";
        cout << " �������: ";
        cin >> s[i].surname;
        cout << " ����: ";
        cin >> s[i].course;
        cout << " ������������ (0 - Գ����, 1 - ����������, 2 - �����������): ";
        cin >> speciality;

        s[i].speciality = static_cast<Speciality>(speciality);
        cout << " ������ � ������: ";
        cin >> s[i].physicsGrade;
        cout << " ������ � ����������: ";
        cin >> s[i].mathGrade;
        cout << " ������ � �����������: ";
        cin >> s[i].informaticsGrade; 

        s[i].halfbal = CalculateAverage(s[i]);
    }
}

void Print(const Student* s, const int N)
{
    cout << "=======================================================================================================\n";
    cout << "| �  | �������       | ���� | ������������       | Գ����  | ���������� | �����������  |������� ���|\n";
    cout << "-------------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < N; i++) {
        cout << "| " << setw(2) << i + 1 << " | "
            << setw(15) << left << s[i].surname << "| "
            << setw(4) << s[i].course << " | "
            << setw(20) << left << specialityStr[s[i].speciality] << "| "
            << setw(7) << s[i].physicsGrade << " | "
            << setw(10) << s[i].mathGrade << " | "
            << setw(12) << s[i].informaticsGrade << " |"
            << setw(11) <<  s[i].halfbal << " |\n";   
         
    } 
    cout << "=======================================================================================================\n";
}

double CalculateAverage(const Student& s) {
    double sum = s.physicsGrade + s.mathGrade + s.informaticsGrade; 

    return sum / 3.0; // ������� ��� � ����� ��������
}

void SortByAverage(Student* s, const int N) {
    Student tmp;
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (s[j].halfbal < s[j + 1].halfbal) { // ���������� �� ������� ����� (�� ������� �� �������)
                tmp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = tmp;
            }
        }
    }
}

void SortByCourse(Student* s, const int N) {
    Student tmp;
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (s[j].course > s[j + 1].course) { // ���������� �� ������ (�� ������� �� �������)
                tmp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = tmp;
            }
        }
    }
}

void SortBySurname(Student* s, const int N) {
    Student tmp;
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (s[j].surname < s[j + 1].surname) { // ���������� �� �������� (�� Z �� A)
                tmp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = tmp;
            }
        }
    }
}



void ManualSort(Student* s, const int N) {
    int sortChoice;
    cout << "������ ������� ����������:\n";
    cout << "1. ���������� �� ������� ����� (�� ������� �� �������)\n";
    cout << "2. ���������� �� ������ (�� ������� �� �������)\n";
    cout << "3. ���������� �� �������� (�� � �� A)\n";
    cout << "��� ����: ";
    cin >> sortChoice;

    switch (sortChoice)
    {
    case 1:
        SortByAverage(s, N);
        break;
    case 2:
        SortByCourse(s, N);
        break;
    case 3:
        SortBySurname(s, N);
        break;
    default:
        cout << "������� ����!\n";
        break;
    }

    Print(s, N); 
}


void Sort(Student* s, const int N)
{
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++)
    {
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
        {
            if (
                (s[i1].halfbal < s[i1 + 1].halfbal) || // ������� �� ������� ����� (�� ������� �� �������)
                (s[i1].halfbal == s[i1 + 1].halfbal
                    && s[i1].course > s[i1 + 1].course) || // ���� ������� ��� ���������, ������� �� ������
                (s[i1].halfbal == s[i1 + 1].halfbal && s[i1].course == s[i1 + 1].course && s[i1].surname < s[i1 + 1].surname) // ���� ������� ��� �� ���� �������, ������� �� �������� (�� Z �� A)
                ) {
                tmp = s[i1];
                s[i1] = s[i1 + 1];
                s[i1 + 1] = tmp;
            }
        }
    }
}

int* IndexSort(Student* s, const int N) {
    int* I = new int[N];
    for (int i = 0; i < N; i++)
        I[i] = i;

    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (
                (s[I[j]].halfbal < s[I[j + 1]].halfbal) ||
                (s[I[j]].halfbal == s[I[j + 1]].halfbal && s[I[j]].course > s[I[j + 1]].course) ||
                (s[I[j]].halfbal == s[I[j + 1]].halfbal && s[I[j]].course == s[I[j + 1]].course && s[I[j]].surname < s[I[j + 1]].surname)
                ) {
                swap(I[j], I[j + 1]);
            }
        }
    }

    return I;
}

void PrintIndexSorted(Student* s, int* I, const int N)
{
    cout << "======================================================================================================\n";
    cout << "| �  | �������      | ���� | ������������       | Գ����  | ���������� | �����������  |������� ���|\n";
    cout << "------------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < N; i++) {
        int idx = I[i];
        cout << "| " << setw(1) << i + 1 << " | "
            << setw(15) << left << s[idx].surname << "| "
            << setw(4) << s[idx].course << " | "
            << setw(20) << left << specialityStr[s[idx].speciality] << "| "
            << setw(7) << s[idx].physicsGrade << " | "
            << setw(10) << s[idx].mathGrade << " | "
            << setw(12) << s[idx].informaticsGrade << " |" 
         << setw(11) <<  s[idx].halfbal << " |\n"; 
    }
    cout << "======================================================================================================\n"; 
}

int BinSearch(const Student* s, const int N, const string& surname, const int course, const double halfbal)
{
    int L = 0, R = N - 1, m;

    do {
        m = (L + R) / 2;

        if (s[m].surname == surname && s[m].course == course && s[m].halfbal == halfbal)
            return m;

        if ((s[m].course < course) ||
            (s[m].course == course && s[m].surname < surname) ||
            (s[m].course == course && s[m].surname == surname && s[m].halfbal < halfbal))
        {
            L = m + 1;
        }
        else {
            R = m - 1;
        } 
    } while (L <= R);

    return -1;
}

void SortForBinSearch(Student* s, const int N) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if ((s[j].course > s[j + 1].course) ||
                (s[j].course == s[j + 1].course && s[j].surname > s[j + 1].surname) ||
                (s[j].course == s[j + 1].course && s[j].surname == s[j + 1].surname && s[j].halfbal > s[j + 1].halfbal)) {
                swap(s[j], s[j + 1]);
            }
        }
    }
}
