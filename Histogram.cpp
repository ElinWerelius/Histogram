#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

// Globala konstanter:

const int ANTAL_BOKSTAVER = 26;  //A-Z
const int ANTAL_SPRAK = 4;



const double TOLK_HJALP[ANTAL_SPRAK][ANTAL_BOKSTAVER]=
{{8.27,1.48,2.94,4.03,11.78,2.22,1.72,6.77,                    //engelska
    7.39,0.12,0.81,3.76,2.85,6.71,7.79,1.54,
    0.05,5.95,6.69,9.07,2.66,1.13,2.14,0.19,
    1.89,0.03},
    {7.97,1.40,3.55,3.79,16.89,1.02,1.00,0.75,                 //franska
        7.08,0.38,0.04,5.51,2.82,8.11,5.19,2.78,
        1.01,6.69,8.35,7.22,6.09,1.35,0.02,0.54,
        0.30,0.15},
    {9.50,1.11,1.53,5.30,8.94,1.74,3.57,3.94,                  //svenska
        3.98,0.89,3.26,4.93,3.41,8.46,5.01,1.77,
        0.00,6.73,5.56,9.20,1.94,2.42,0.00,0.05,
        0.45,0.00},
    {5.12,1.95,3.57,5.07,16.87,1.35,3.00,5.79,                 //tyska
        8.63,0.19,1.14,3.68,3.12,10.64,1.74,0.42,
        0.01,6.30,6.99,5.19,3.92,0.77,1.79,0.01,
        0.69,1.24}};


int berakna_histogram_abs(string &text, double f[]);

void abs_till_rel(double f[], int &bokstaver);

void plotta_histogram_rel( double f[]);

void tolkning(double f[], int &bokstaver);

string namn_pa_fil();

string inlasning(string &filnamn);


int main()
{
    string filnamn;
    string text = "File not found";
    double f[ANTAL_BOKSTAVER];
    int bokstaver = 0;

    while (text == "File not found")
    {
        filnamn = namn_pa_fil();
        cout << endl;
        text = inlasning(filnamn);
    }

    bokstaver = berakna_histogram_abs(text, f);

    abs_till_rel(f, bokstaver);

    tolkning(f, bokstaver);

    plotta_histogram_rel(f);

    return 0;
}

int berakna_histogram_abs(string &str, double f[])
{
    int index;
    int a = 0;

//Nollställ frekvens:
    for (int i=0; i<ANTAL_BOKSTAVER; i++)

        f[i] = 0;

// Loopar igenom strängen
    for ( int i=0; i< (int) str.length(); i++)
    {
        a++;   // Räknar antal bokstäver                 //Den är inte på noll, BEHÖVS FIXAS!

        // Om tecknet är en gemen
        if (str.at(i)>='a' && str.at(i)<='z')
        {
            // räkna ut platsen i arrayen
            index = str.at(i) - 'a';
            // uppdatera räknaren på rätt plats
            f[index]++;
        }

        // Om tecknet är en versal
        if (str.at(i)>='A' && str.at(i)<='Z')
        {
            // räkna ut platsen i arrayen
            index = str.at(i) - 'A';
            // uppdatera räknaren på rätt plats
            f[index]++;
        }
    }
   return a;
}

void abs_till_rel( double f[], int &bokstaver)
{

    for(int i = 0; i < ANTAL_BOKSTAVER; i++)
    {
        f[i] = ((double) f[i] / (double) bokstaver) * 100;
    }
}

void plotta_histogram_rel(double f[])
{
    cout << "Bokstavsfördelning:" << endl << endl << endl << endl;


    for(int i=0; i < ANTAL_BOKSTAVER; i++)
    {
        char c = char (i+'A');
        cout << c << " ";

        for(int j=0; j<f[i]*2; j++)
            cout << "*";
        cout << endl;
    }
}

void tolkning(double f[], int &bokstaver)
{

    string spraknamn[ANTAL_SPRAK] = {"Engelska", "Franska", "Svenska", "Tyska"};
    double sum[ANTAL_SPRAK] = {0};
    double skillnad;
    double kvsumma = 999999999;
    int sannolikt_sprak = 0;


    cout << "Resultat för bokstäverna A-Z" << endl << endl;
    cout << "Antal bokstäver: " << bokstaver << endl;

    for(int i = 0; i < ANTAL_SPRAK; i++)
    {

        for(int j=0; j<ANTAL_BOKSTAVER; j++)
        {
            skillnad = TOLK_HJALP[i][j] - f[j];
            sum[i] = sum[i] + skillnad * skillnad;
        }

        if(sum[i]<kvsumma)
        {
            kvsumma = sum[i];
            sannolikt_sprak = i;
        }

        cout << spraknamn[i] << " har kvadratsumma: " << sum[i] << endl;
    }

    cout << spraknamn[sannolikt_sprak] << " är det mest sannolika språket."
    << endl << endl;
}

string namn_pa_fil()
{
    string filnamn;
    string namn = ".txt";


    cout << "Ange fil att jämföra: ";
    getline(cin, filnamn);


    size_t key = filnamn.rfind(namn);


    if(key == string::npos)
    {
        filnamn.append(".txt");
    }

    return filnamn;
}



string inlasning(string &filnamn)
{
    string fil;

    ifstream infil(filnamn.c_str());


    if(!infil.good())
    {
        cout << filnamn << " existerar inte, kontrollera filnamnet." << endl;
        return "file not found"; // Eller 0 för att inte få rest.
    }

    while(infil.good())
    {
        char c = infil.get();
        if(infil.good())
            fil += c;
    }

    infil.close();

    return fil;
}
