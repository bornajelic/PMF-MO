/*
 * Vect.h
 *
 *  Created on: 1. tra 2015.
 *      Author: Tomislav
 */

#ifndef __VECT_REALLOC_H_IS_INCLUDDED__
#define __VECT_REALLOC_H_IS_INCLUDDED__

#include <iostream>
#include <string>

// Klasa Vect implemetira vektor dinami�ki alociranih double-ova kojima je pridru�en jedan string
// (ime varijable). Klasa vr�i realokaciju kada vi�e nema dovoljno mjesta za novi element.
// Implementira metodu push_back. Implementirana je potpuna kontrola kopiranja te neke uobi�ajene
// metode.
class Vect
{
    public:
        // konstruktor i delegiraju�e verzije
        Vect(size_t n, double v, std::string const & ime); // Ctor
        Vect(size_t n, double v) : Vect(n, v, "") {}       // Ctor
        explicit Vect(size_t n) : Vect(n, 0.0, "") {}      // Ctor
        explicit Vect(std::string const & ime) : Vect(0, 0.0, ime) {} // Ctor

        // Kontrola kopiranja
        Vect(const Vect& v);                            // CCtor
        Vect(Vect && v) noexcept;                       // MCtor

        Vect& operator=(const Vect& v);                 // OP
        Vect& operator=(Vect && v) noexcept;            // MOP

        ~Vect(){std::cout << "Dtor\n";  free(); }

        // dohvat elemenata
        double const& operator[](size_t i) const { return mdata[i]; }
        double&       operator[](size_t i)       { return mdata[i]; }

        // push_back kao u std::vector. Eventualno izaziva realokaciju �itavog vektora
        void push_back(double);

        // info rutine
        size_t  size()     const {return mfirst_free - mdata; }
        size_t  capacity() const {return mend - mdata; }

        // utility-rutine
        double norm2() const;
        Vect& scale(double alpha);
        void print(std::ostream& out) const;

        // Ime vektora je javna varijabla
        std::string  ime;   // ime varijable
    private:
        double *mdata;       // pokaziva� na prvi element
        double *mfirst_free; // pokaziva� na prvo slobodno mjesto
        double *mend;        // pokaziva� na kraj alociranog prostora
                             // (jedno mjesto iza posljednjeg)

        // Vra�a true ako imamo prostora za jo� jedan element, ina�e vra�a false.
        bool has_space() const {  return ( size() == capacity() ) ?  false : true; }

        // Oslobodi zauzeti prostor (pomo�u alokatora)
        void free();
        // realociraj na novu lokaciju. Pove�aj dimenziju vektora 2 puta; ako je
        // vektor prazan dodaj jedan element.
        void reallocate();

        void copy_vect_to_this(const Vect&);

        // alokator ne mora imati pristup varijablama �lanicama klase pa ga �inimo
        // stati�kim. Ne zaboraviti definirati ga u izvornoj datoteci.
        static std::allocator<double> alloc;

};
#endif
