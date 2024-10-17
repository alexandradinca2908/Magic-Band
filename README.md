DINCĂ Alexandra-Cristina - 311CD

=== struct.h ===

    Continte 6 structuri:
        Nodul unei liste, care memoreaza un element de tip caracter, adresa nodului urmator si a celui anterior.
        Lista (Banda), alcatuita dintr-o santinela si un pointer catre pozitia curenta a degetului pe banda.
        Nodul unui stack, similar nodului de lista, cu diferenta ca memoreaza adresa "degetului" inainte de executarea unei operatii de tip MOVE.
        Stack-ul (Stiva), ce urmeaza pattern-ul benzii; difera doar tipul variabilelor.
        Nodul unui queue, cu particularitatea ca retine siruri de caractere (comenzile introduse de user).
        Queue-ul (Coada), care este similara cu stiva si banda.

=== update.c ===

    moveFinger: functia verifica intai daca degetul trebuia mutat la stanga sau la dreapta; in cazul mutarii la stanga, aceasta se poate efectua doar daca nodul curent NU este echivalent cu nodul din dreapta santinelei; pentru dreapta, se verifica daca mutarea se efectueaza direct sau necesita intai crearea unui nod nou.

    moveToChar: pentru a extrage caracterul din comanda, se atribuie unui vector subsirul returnat de strchr(command, ' ');
                    ex: pentru MOVE_LEFT_CHAR X, strstr returneaza " X"
        apoi, cautand prin banda al doilea element din vector(caracterul), se itereaza la stanga sau la dreapta si se respecta aceleasi conditii ca la moveFinger.

    writeChar: metoda de extragere a caracterului din comanda este la fel ca mai sus; dupa aceea, caracterul gasit este atribuit 
        elementului de pe nodul curent.

    insertChar: implementarea este aproape identica cu cea din moveFinger; singura diferenta este ca, daca toate conditiile sunt 
        respectate, se creeaza un nod nou si se insereaza in banda prin stabilirea legaturilor next si prev.


=== query.c ===

    showCurrent: arata elementul curent catre care indica degetul de pe banda.

    showAll: folosind un iterator, este parcursa toata lista, incepand cu elementul legat de santinela, si se afiseaza elementele.

=== create.c===

    Functiile corespund cu structurile din struct.h, si sunt folosite pentru alocarea memoriei.

=== main.c ===

    Pentru inceput, sunt alocate toate listele necesare rularii programului. Apoi, primul pas este de a extrage numarul de comenzi 
        ce urmeaza a fi introduse. Pentru asta, se retine primul rand din fisierul tema1.in intr-un vector, iar apoi fiecare caracter in parte este convertit in int si adunat intr-o variabila ce retine numarul final.
    Apoi, se incepe un while loop, care este folosit fie pentru memorarea comenzilor, fie pentru executarea sau anularea lor.
        EXECUTE: daca comanda intalnita in fisier este cea de executie si exista comenzi in coada, atunci prima comanda din queue 
            este executata; pentru cele de MOVE, in urma executiei, se stocheaza in coada UNDO pozitia degetului inainte de mutare; pentru cea de WRITE, se elibereaza memoria din stive pentru ca nu va mai fi folosita.
        SHOW: daca se intalneste comanda SHOW, se executa una din funtiile de afisare.
        UNDO/REDO: pentru UNDO, degetul de pe banda se muta la ultima pozitie din stack-ul undo, iar acest ultim nod din UNDO se 
            duce in stack-ul REDO; pentru REDO, se executa invers.
        OTHER: orice alta comanda este adaugata in coada de executie si se asteapta inserarea unui EXECUTE.
        Mentiuni: in pasii de adaugare sunt tratate mereu cazurile in care listele sunt vide.
    La final, fisierele sunt inchise, iar structurile de date alocate dinamic sunt eliberate.