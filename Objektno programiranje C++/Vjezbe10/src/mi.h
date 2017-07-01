/*
 * mi.h
 *
 *  Created on: 21. svi 2015.
 *      Author: Tomislav
 */

#ifndef SRC_MI_H_
#define SRC_MI_H_

#include <string>


class Datum {
public:
	Datum(std::string);
	int dan() const;
	int mjesec() const;
	int godina() const;

	std::string to_string() const;

	friend bool operator==(Datum const &, Datum const &);
private:
	int m_dan;
	int m_mjesec;
	int m_godina;

	static const std::string time_format;
};

std::ostream & operator<<(std::ostream &, Datum const &);


class Osoba {
public:
	Osoba(std::string, std::string);
	std::string const & ime() const;
	std::string const & prezime() const;
	virtual std::string to_string() const;

	virtual ~Osoba() {
	}

	friend bool operator==(Osoba const &, Osoba const &);
	friend bool operator!=(Osoba const &, Osoba const &);
protected:
	virtual bool jednak(Osoba const &) const;
private:
	std::string m_ime;
	std::string m_prezime;
};


class Zaposlenik: public virtual Osoba {
public:
	// Radim delegirajuci konstruktor zbog opcenitijeg slucaja kada se klasa konstruira i iz datuma.
	//
	// Kada bih podrzao samo stvaranje iz stringa, klasa se ne bi mogla stvoriti iz Datuma, a
	// iz dijagrama izgleda kao nesto sto bi se trebalo moci.
	Zaposlenik(std::string, std::string, int, Datum);
	Zaposlenik(std::string, std::string, int, std::string);
	int radno_mjesto() const;
	Datum const & pocetak_zaposlenja() const;
	virtual std::string to_string() const;

	virtual ~Zaposlenik() {
	}

	friend bool operator==(Osoba const &, Osoba const &);
	friend bool operator!=(Osoba const &, Osoba const &);
protected:
	virtual bool jednak(Osoba const &) const;
private:
	int m_radno_mjesto;
	Datum m_pocetak_zaposlenja;
};


class PrivremeniZaposlenik: public Zaposlenik {
public:
	PrivremeniZaposlenik(std::string, std::string, int, std::string, std::string);
	PrivremeniZaposlenik(std::string, std::string, int, Datum, Datum);
	Datum const & kraj_zaposlenja() const;
	virtual std::string to_string() const;

	virtual ~PrivremeniZaposlenik() {
	}

	friend bool operator==(Osoba const &, Osoba const &);
	friend bool operator!=(Osoba const &, Osoba const &);
protected:
	virtual bool jednak(Osoba const &) const;
private:
	Datum m_kraj_zaposlenja;
};


class Student: public virtual Osoba {
public:
	Student(std::string, std::string, int);
	int godina() const;
	virtual std::string to_string() const;

	virtual ~Student() {
	}

	friend bool operator==(Osoba const &, Osoba const &);
	friend bool operator!=(Osoba const &, Osoba const &);
protected:
	virtual bool jednak(Osoba const &) const;
private:
	int m_godina;
};

class AngaziraniStudent: public PrivremeniZaposlenik, public Student {
public:
	AngaziraniStudent(std::string, std::string, int, Datum, Datum, int);
	AngaziraniStudent(std::string, std::string, int, std::string, std::string, int);
	virtual std::string to_string() const;

	friend bool operator==(Osoba const &, Osoba const &);
	friend bool operator!=(Osoba const &, Osoba const &);
protected:
	virtual bool jednak(Osoba const &) const;
};

#endif /* SRC_MI_H_ */
