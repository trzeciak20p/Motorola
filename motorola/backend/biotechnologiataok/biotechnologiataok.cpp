// biotechnologiataok.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
//zaraz ogarniemy wczytywanie z pliku sekwencji
using namespace std;

bool isSequenceCorrect(string sequence) {           //sprawdzamy tutaj czy podana sekwencja składa sie wyłącznie z nukleoidów
    for (int i = 0; i < sequence.length(); i++) {
        if (sequence[i] != 'T' || sequence[i] != 'A' || sequence[i] != 'U' || sequence[i] != 'G' || sequence[i] != 'C')
            return false;
    }
    return true;
}
bool isRNA(string sequence) {
    for (int i = 0; i < sequence.length(); i++) {
        if (sequence[i] == 'T')
            return false;
        if (sequence[i] == 'U')
            return true;
    }
}
string changeDNAtoRNA(string sequence) {
    for (int i = 0; i < sequence.length(); i++) {
        if (sequence[i] == 'T')
            sequence[i] = 'U';   
    }
    return sequence;
}

vector <string> codons;     //dodawaqne są tutaj przesunięte sekwencję RNA zaczynające się od kodonu 'AUG'
vector < string> proteins;  //zestaw wszystkich potencjalnych białek(z odpowiendnim kodonem startowym i końcowym

void createCodon(string sequence) {     //tworzenie przesunięć sekwencji w taki sposób, aby rozpoczynały się od kodonu startowego
    for (int i = 0; i < sequence.length(); i++) {
        if (sequence[i] == 'A' && sequence[i + 1] == 'U' && sequence[i + 2] == 'G') {
            
            codons.push_back(sequence.substr(i, sequence.length() - i));
        }
    }
}

string createProteins(string sequence) {    //tworzenie białek
    string aminoSequence = "";
    char amino;
    string protein = "";
    //dzielimy sekwencję na stringi długości 3, następnie sprawdzamy jakiemu aminokwasowi jest string przypożądkowany, tworzymy białko 
    for (int i = 0; i < sequence.length(); i += 3) {
        aminoSequence = sequence.substr(i, 3);
        

        switch (aminoSequence[0]) {
            //pierwszy nuekleoid
            case 'U': 

                switch (aminoSequence[1]) {
                    //drugi nukleoid
                    case 'U': 
                        //trzeci nukleoid
                        switch (aminoSequence[2]) {
                            case 'U':
                            case 'C':
                                amino = 'F';   
                                break;
                            case 'A':
                            case 'G':
                                amino = 'L';
                                break;
                            default:
                                break;
                        }
                        break;
                    case 'C':
                        //trzeci nukleoid
                        amino = 'S';
                        break;
                    case 'A':
                        //trzeci nukleoid
                        switch (aminoSequence[2]) {
                            case 'U':
                            case 'C':
                                amino = 'Y';
                                break;
                            case 'A':
                            case 'G':
                                amino = 'X';
                                break;
                            default:
                                break;
                        }
                        break;
                    case 'G':
                        //trzeci nukleoid
                        switch (aminoSequence[2]) {
                        case 'U':
                        case 'C':
                            amino = 'C';
                            break;
                        case 'A':
                            amino = 'X';
                            break;
                        case 'G':
                            amino = 'W';
                            break;
                        default:
                            break;
                        }
                        break;
                    default:
                        break;
                }
                break;
            case 'C': 
                switch (aminoSequence[1]) {
                    //drugi nukleoid
                    case 'U':
                        amino = 'L';
                        break;

                    case 'C':
                        amino = 'P';
                        break;
                    case 'A':
                        //trzeci nukleoid
                        switch (aminoSequence[2]) {
                        case 'U':
                        case 'C':
                            amino = 'H';
                            break;
                        case 'A':
                        case 'G':
                            amino = 'Q';
                            break;
                        default:
                            break;
                        }
                        break;
                    case 'G':
                        amino = 'L';
                        break;
                    default:
                        break;
                }
                break;
            case 'A':
                switch (aminoSequence[1]) {
                    //drugi nukleoid
                    case 'U':
                        //trzeci nukleoid
                        switch (aminoSequence[2]) {
                        case 'U':
                        case 'C':
                        case 'A':
                            amino = 'I';
                            break;
                        case 'G':
                            amino = 'M';
                            break;
                        default:
                            break;
                        }
                        break;
                    case 'C':
                        //trzeci nukleoid
                        amino = 'T';
                        break;
                    case 'A':
                        //trzeci nukleoid
                        switch (aminoSequence[2]) {
                        case 'U':
                        case 'C':
                            amino = 'N';
                            break;
                        case 'A':
                        case 'G':
                            amino = 'K';
                            break;
                        default:
                            break;
                        }
                        break;
                    case 'G':
                        //trzeci nukleoid
                        switch (aminoSequence[2]) {
                            case 'U':
                            case 'C':
                                amino = 'S';
                                break;
                            case 'A':
                            case 'G':
                                amino = 'R';
                                break;
                            default:
                                break;
                        }
                        break;
                    default:
                        break;
                }
                break;
            case 'G':
                switch (aminoSequence[1]) {
                    //drugi nukleoid
                    case 'U':
                        amino = 'V';
                        break;

                    case 'C':
                        //trzeci nukleoid
                        amino = 'A';
                        break;
                    case 'A':
                        //trzeci nukleoid
                        switch (aminoSequence[2]) {
                        case 'U':
                        case 'C':
                            amino = 'D';
                            break;
                        case 'A':
                        case 'G':
                            amino = 'E';
                            break;
                        default:
                            break;
                        }
                        break;
                    case 'G':
                        amino = 'G';
                        break;
                    
                    default:
                        break;
                    
                }
                break;
            default:
                break;
         


            

        }
        
        protein += amino;

    }
    return protein;
   
}
int main()
{
    //sekwencja z pliku
    fstream file;
    string url;
    cout << "podaj nazwe pliku" << endl;
    cin >> url;
    file.open(url, ios::in);
    if (file.good() != true) {
        cout << "problem z plikkiem";
        return 0;
    }
    //od ręki wpisywana sekwencja
    string sequenceRNA; //sekwencja RNA lub DNA wprowadzona przez użytkownika
    string potencialProtein;    //potencjalne białka, jeszcze nie zweryfikowane pod względem ostatniego kodonu
    //wczytywanie sekwencji do momentu kiedy nie będzie poprawna
    do {
        
        cout << "Podaj sekwencę RNA!\n";
        cin >> sequenceRNA;
    } while (isSequenceCorrect(sequenceRNA) == true);
    //sprawdzenie czy podana sekwencja to RNA czy DNA, w wypadku DNA => zmiana na RNA
    if (isRNA(sequenceRNA) != true) {
        sequenceRNA = changeDNAtoRNA(sequenceRNA);
    }
    //Tworzenie przesunięć sekwencji takie, aby powstałe przesunięcie rozpoczynało się kodonem 'AUG'
    createCodon(sequenceRNA);
    //tworzenie potencjalnych białek i ich weryfikacja
    for (int i = 0; i < codons.size(); i++) {
        potencialProtein = createProteins(codons.at(i));    //tworzenie białka
        if (potencialProtein[potencialProtein.length() - 1] == 'X') {   //sprawdzenie czy kończy się odpowiedni kodonem
            proteins.push_back(potencialProtein);   //dodadenie potencjalnego białka do wektora proteins
        }
    }
    cout << "ile bialek: " << proteins.size();

}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
