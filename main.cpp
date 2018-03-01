#include <iostream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

const vector<int> gaps = {701, 301, 132, 57, 23, 10, 4, 1};

int doOneInsertion(vector<double>& v, int n)
{
    int count = 0;

    double value = v[n];
    int j = n-1;

    while(j>=0 && v[j] < value)
    {
        count++;
        v[j+1] = v[j];
        j--;
    }
    count++;

    v[j+1] = value;

    return count;
}

int insertionsort(vector<double>& vec)
{
    int count = 0;

    for(int i=1;i<vec.size();i++)
    {
        count = count + doOneInsertion(vec,i);
    }

    return count;
}

int doOneInsertionSS(vector<double>& v, int n, int h)
{
    int count = 0;

    double value = v[n];
    int j = n-h;

    while(j>=0 && v[j] < value)
    {
        count++;
        v[j+h] = v[j];
        j=j-h;
    }
    count++;

    v[j+h] = value;

    return count;
}

int shellsort(vector<double>& vec)
{
    int count = 0;

    for(int i=0;i<gaps.size();i++)
    {
        for(int j=1;j<vec.size();j++)
        {
            count = count + doOneInsertionSS(vec,j,gaps[i]);
        }
    }

    return count;
}

/* Print a vector to standard output, cout. */
void printVector(vector<double>& data)
{
    int nentries = data.size();
    for (int n = 0 ; n<nentries ; n++)
    {
        cout << data[n] << " ";
    }
    cout << endl;
}

/* Returns true if vec is sorted in nonincreasing order, false
   otherwise, and prints a message to cout. */
bool testSorted(vector<double>& vec)
{
    int s = vec.size();
    for (int i=1; i<s; i++)
    {
        if (vec[i-1] < vec[i])
        {
            cout << "Data is not sorted" << endl;
            return false;
        }
    }
    cout << "Data is sorted" << endl;
    return true;
}

/* A version of selectionsort that returns the number of comparisons made. */
int selectionsort(vector<double>& vec)
{
    int count = 0;
    int s = vec.size();
    for (int i=0; i<s; i++)
    {
        for (int j=i+1; j<s; j++)
        {
            count++; // There's a comparison coming up!
            if (vec[i] < vec[j])
            {
                double x = vec[i];
                vec[i] = vec[j];
                vec[j] = x;
            }
        }
    }
    return count;
}

void fillVector(vector<double>& data, int nentries)
{
    data.clear();
    for (int n = 0 ; n<nentries ; n++)
    {
        double p = double(rand())/RAND_MAX;
        // you may prefer to replace the above line with
        //   cin >> p;
        // so that you can enter your own data from the keyboard.
        // or put this version as a new function to be called from main.
        data.push_back(p);
    }
}

/* fills the vector "data" with nentries chosen
   "in a partially sorted way" from 0..1 */
void fillVectorPS(vector<double>& data, int nentries)
{
    data.clear();
    /* create data in "blocks".  Block n=k contains
       values from k/10 to (k+1)/10  Blocks count
       downwards. */
    int k = 10; // number of block we are in
    int nblocks = 10; // number of blocks
    int n = 0; // index of next item;
    double blocksize = 1.0/k;
    while(n<nentries) {
        double p = double(rand())/RAND_MAX; // from 0 to 1
        p = p*blocksize + k*blocksize;
        data.push_back(p);
        n++;
        if (n%nblocks == 0) k--;
    }
}

int main ()
{
    int count = 0;
    vector<double> data1;
    vector<double> data2;
    vector<double> data3;
    int nentries;
    cout << "Number of entries? " << endl;
    cin >> nentries;

     /* initialize random seed: */
    srand(time(NULL));
    // OR
    // srand(102938); // change this number if needed

    fillVector(data1, nentries);
    // vectors can be copied in C++ using = like any other variables
    data2 = data1;
    data3 = data1;

    // printVector(data1);

    testSorted(data1); // check if the vector is already sorted
    cout << "Sorting.." << endl;

    cout << "Using selectionsort..." << endl;
    count = selectionsort(data1);
    testSorted(data1);
    cout << "selectionsort complete with " << count << " comparisons" << endl;

    cout << "Using insertionsort..." << endl;
    count = insertionsort(data2);
    printVector(data2);
    testSorted(data2);
    cout << "insertionsort complete with " << count << " comparisons" << endl;

    cout << "Using shellsort..." << endl;
    count = shellsort(data3);
    printVector(data3);
    testSorted(data3);
    cout << "shellsort complete with " << count << " comparisons" << endl;

    return 0;
}