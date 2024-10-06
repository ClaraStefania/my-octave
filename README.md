// Copyright Stefania-Clara Diaconescu 313CAb 2023-2024

Problema are ca obiectiv realizarea unui software numeric asemanator cu
Octave, ce realizeaza operatii cu matrice, tablourile fiind alocate dinamic.

Se citeste caracterul l. Cat timp acesta este diferit de 'Q', se fac
urmatoarele verificari:

- In  cazul in care l = 'L', se citesc dimensiunile matricei, acestea fiind
adaugate in doi vectori separati, unul pentru numarul de linii, iar celalalt
pentru numarul de coloane. Functia 'aloc_lin_col()' aloca memorie pentru cei
doi vectori. In cazul in care indicele noului element + 1 (numerotatea pornind
de la 0) depaseste capacitatea vectorilor, aceasta se dubleaza. Daca nu se
poate aloca memorie, se va afisa mesajul corespunzator si se va iesi din
functie. Functia 'aloc()' adauga o matrice la finalul vectorului de matrice.
Verifica daca este nevoie sa realoce memorie pentru vector prin apelarea
functiei 'realoc()',  urmand sa aloce si pentru matrice. Ca in cazul vectorilor
pentru linii si coloane, daca nu se poate aloca memorie se afiseaza un mesaj si
se iese din functie. Prin apelarea functiei 'citire()' se citeste noua matrice.

- In cazul in care l = 'D', se citeste indexul matricei ale carei dimensiuni
trebuie afisate. Daca indexul nu corespunde niciunei matrice, se afiseaza un
mesaj. In caz contrar, se afiseaza numarul de linii si numarul de coloane.

- In cazul in care l = 'P', se citeste indexul matricei care trebuie afisata.
Daca indexul nu corespunde niciunei matrice, se afiseaza un mesaj. Altfel, se
afseaza matricea.

- In cazul in care l = 'C', se apeleaza functia 'redimensionare()'. Se verifica
daca indexul corespunde vreunei matrice. Se citesc numarul de linii si de
coloane si indicii acestora care se salveaza in vectori separati. Va fi
construita o matrice auxiliara prin intersectia liniilor si coloanelor si se va
adauga in locul celei vechi. La final se elibereaza vectorii de linii si de
coloane.

- In cazul in care l = 'M', se apeleaza functia 'inmultire()'. Se verifica daca
indecsii corespund unor matrice din vector si daca numarul de coloane al primei
matrice este egal cu numarul de linii al celei de-a doua. Se adauga o noua
matrice in vector si dimensiunile acesteia. Se apeleaza functia 'inm()' care
realizeaza inmultirea. Functia 't_inm()' calculeaza separat fiecare element.

- In cazul in care l = 'O', se apeleaza functia 'sortare()'. Se calculeaza suma
elementelor fiecarei matrice si se salveaza intr-un vector. Am sortat matricele
crescator in functie de suma, prin algoritmul "bubble sort", interschimband si
dimensiunile.

- In cazul in care l = 'F', se apeleaza functia 'stergere()'. Se verifica daca
indexul corespunde vreunei matrice. Se elibereaza memoria ocupata de matricea
cu indexul dat si se deplaseaza restul matricelor spre stanga. In cazul in
care numarul de matrice este mai mic decat jumatate din dimensiune, se
injumatateste capacitatea si se realoca vectorul de matrice. Acest procedeu
are loc si pentru vectorii de dimensiuni.

- In cazul in care l = 'T', se apeleaza functia 'transpunere()'. Se verifica
daca indexul dat corespunde vreunei matrice. Se interschimba numarul de linii
cu cel de coloane si se aloca o matrice auxiliara cu noile dimensiuni. Functia
'aloc_mat()' aloca memorie pentru o matrice, fara sa o adauge in vector. Dupa
ce transpusa este realizata, se elibereaza memoria ocupata de matricea veche,
iar in locul ei se pune cea noua.

- In cazul in care l = 'R', se apeleaza functia 'ridicare()'. Se verifica daca
indexul dat corespunde vreunei matrice. Daca exponentul este negativ, ridicarea
nu poate avea loc. Daca exponentul este 0, matricea va deveni matricea
identitate. Altfel, luam o matrice auxiliara care este matricea identitate.
Cat timp exponentul este pozitiv, in cazul in care este impar, matricea se
inmulteste cu cea initiala. Altfel, se ridica la patrat, iar exponentul se
injumatateste. La final, matricea este inlocuita de ce obtinuta in urma
ridicarii.

- In cazul in care l = 'S', se verifica daca indecsii corespund unor matrice
din vector si daca se poate realiza inmultirea acestora. Se aloca memorie
pentru o noua matrice si se adauga dimensiunile in vectori. Daca dimensiunea
este egala cu 1, matricea de o linie si o coloana se obtine prin inmultirea
celorlalte doua, care contin cate un element. Altfel, se imparte fiecare
matrice in patru matrice blocuri cu dimensiunile injumatatite. Se calculeaza
cele sapte matrice auxiliare conform algoritmului, tot prin aplicarea recursiva
a acestuia, pana ajung la dimensiunea de 1 x 1. In final, se calculeaza
blocurile matricei rezultate si dupa matricea per total, urmand sa se elibereze
memoria ocupata de toate celelalte matrice auxiliare.

- In cazul in care l = 'Q', se iese din while si sunt dealocate toate
resursele. 

- In cazul in care se citeste orice alta litera, se va afisa mesajul
corespunzator.
