#ifndef File_H
#define File_H
#include <string>
#include "Liste.h"
using namespace std;

class File {
    private:
        Liste m_liste;
        Liste* m_queue;
    public:
        File();
        File(const File&);
        ~File();
        File& operator=(const File&);
        bool estVide() const;
        int premier() const;
        // File& suivant() const;
        void enfiler(int);
        void defiler();
        // bool appartient(int) const;
        string toString() const;
};

#endif