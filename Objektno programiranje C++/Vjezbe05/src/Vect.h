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

// Klasa Vect implemetira vektor dinamièki alociranih double-ova kojima je pridružen jedan string
// (ime varijable). Klasa vrši realokaciju kada više nema dovoljno mjesta za novi element.
// Implementira metodu push_back. Implementirana je potpuna kontrola kopiranja te neke uobièajene
// metode.
class Vect
{
    public:
        // konstruktor i delegirajuæe verzije
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

        // push_back kao u std::vector. Eventualno izaziva realokaciju èitavog vektora
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
        double *mdata;       // pokazivaè na prvi element
        double *mfirst_free; // pokazivaè na prvo slobodno mjesto
        double *mend;        // pokazivaè na kraj alociranog prostora
                             // (jedno mjesto iza posljednjeg)

        // Vraæa true ako imamo prostora za još jedan element, inaæe vraæa false.
        bool has_space() const {  return ( size() == capacity() ) ?  false : true; }

        // Oslobodi zauzeti prostor (pomoæu alokatora)
        void free();
        // realociraj na novu lokaciju. Poveæaj dimenziju vektora 2 puta; ako je
        // vektor prazan dodaj jedan element.
        void reallocate();

        void copy_vect_to_this(const Vect&);

        // alokator ne mora imati pristup varijablama èlanicama klase pa ga èinimo
        // statièkim. Ne zaboraviti definirati ga u izvornoj datoteci.
        static std::allocator<double> alloc;

};
#endif
