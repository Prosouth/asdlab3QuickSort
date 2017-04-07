//
//  qsort.cpp
//
//  Created by Olivier Cuisenaire on 10.04.15.
//  Copyright (c) 2015 Olivier Cuisenaire. All rights reserved.
//
#include <iostream>
#include <utility>
#include <climits>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// selectPivot(begin,end)
//
// choisit un pivot pour le tri rapide parmi le tableau
// entre begin et end (non inclus). Calcule la médiane
// entre le premier, le dernier et l'élément central.
// retourne un iterateur du même type que begin et end
// pointant sur la valeur choisie.
template <typename RandomAccessIterator>
RandomAccessIterator selectPivot( const RandomAccessIterator begin, const RandomAccessIterator end )
{
    RandomAccessIterator p1 = begin;
    RandomAccessIterator p2 = begin + ( end-begin ) / 2;
    RandomAccessIterator p3 = end-1;
    
    if(*p1 < *p2) {
        if( *p2 < *p3 ) return p2;
        else if(*p1 < *p3) return p3;
        return p1;
    } else {
        if( *p1 < *p3 ) return p1;
        else if(*p2 < *p3) return p3;
        return p2;
    }
}

// display
//
// Affiche les valeur entre begin et end (non inclus)
// en entourant de [] la valeur du pivot située entre
// begin et end.
template <typename RandomAccessIterator>
void display( const RandomAccessIterator begin,
             const RandomAccessIterator pivot,
             const RandomAccessIterator end )
{
    for(auto it = begin; it<pivot; ++it) cout << *it << " ";
    cout << "[" << *pivot << "] ";
    for(auto it = pivot+1; it<end; ++it) cout << *it << " ";
    cout << endl;
}

// quickSort
//
// Effectue le tri rapide des éléments entre begin
// et end (non inclus). Doit appeler selectPivot(...)
// pour le choix du pivot, et display() après chaque
// partition
template <typename RandomAccessIterator>
void quickSort(RandomAccessIterator begin,
        RandomAccessIterator end)
{

    RandomAccessIterator i;
    RandomAccessIterator j;
    RandomAccessIterator hi = end - 1;

    // Arrêt de la récursivité
    if (end <= begin) 
    {
        return;
    }

    RandomAccessIterator pivot = selectPivot(begin, end); // on sélectionne le pivot
    swap(*pivot, *hi); // on met le pivot à la fin

    i = begin - 1;
    j = hi;
    while (true) // boucle infinie
    {
        do 
        {
            ++i;
        } while (*i < *hi); // éléments à gauche du pivot < à val de i

        do 
        {
            --j;
        } while (j > begin and *j > *hi); // élément à droite du pivot > à val de j

        if (i >= j) // nécessaire pour ne pas effectuer le dernier swap
        {
            break;
        }
        swap(*i, *j);
    }

    swap(*i, *hi); // on échange i et la valeur tout à droite

    if (begin != end - 1) 
    {
        display(begin, i, end); // on fait l'affichage
    }

    // on lance récursivement de begin  
    quickSort(begin, i);
    quickSort(i + 1, end);
}

// main
//
// Programme testant la mise en oeuvre de quickSort
// appelle cette fonction avec une string, un tableau
// C d'entiers et un std::vector<double>
int main(int argc, const char * argv[]) {
    
    // std::string
    
    string s("EXEMPLE_DE_TRI_RAPIDE");
    cout << s << endl;
    
    quickSort(s.begin(),s.end());
    
    cout << s << endl;
    
    // C array
    
    int array[] = { 7, 3, 6, 1, 9, 2, 0, 10, 12, -3 };
    cout << endl;
    for(int i : array)
        cout << i << " ";
    cout << endl;
    
    quickSort(array,array+10);
    
    for(int i : array)
        cout << i << " ";
    cout << endl;
    
    // std::vector
    
    vector<double> vd { 0.1, 1.2, 3.5, 1.8, 0.4, 10.2, -0.4, 5.8, 6.9, 12.5, 24.3, 0.6, 12.2, 4.5, 3.1415 };
    cout << endl;
    for(double d : vd)
        cout << d << " ";
    cout << endl;
    
    quickSort(vd.begin(),vd.end());
    
    for(double d : vd)
        cout << d << " ";
    cout << endl;
    
    return 0;
}