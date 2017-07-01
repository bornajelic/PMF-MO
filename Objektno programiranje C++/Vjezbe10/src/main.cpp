/*
 * main.cpp
 *
 *  Created on: 21. svi 2015.
 *      Author: Tomislav
 */

#include "mi.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <assert.h>
#include <typeinfo>

/////////////////
///////Datum////
///////////////

const std::string Datum::time_format = "%02d:%02d:%04d";

Datum::Datum(std::string textual) :
		m_dan(), m_mjesec(), m_godina() {
	std::cerr << "Datum-c : " << textual << std::endl;
	std::sscanf(textual.c_str(), time_format.c_str(), &m_dan, &m_mjesec,
			&m_godina);
}

inline int Datum::dan() const {
	return m_dan;
}

inline int Datum::mjesec() const {
	return m_mjesec;
}

inline int Datum::godina() const {
	return m_godina;
}

std::string Datum::to_string() const {
	char buffer[11];
	std::sprintf(buffer, time_format.c_str(), dan(), mjesec(), godina());
	return std::string(buffer);
}

/////////////////
///////Osoba////
///////////////

Osoba::Osoba(std::string ime, std::string prezime) :
		m_ime(ime), m_prezime(prezime) {
	std::cerr << "Osoba-c : " << ime << " " << prezime << std::endl;
}

inline std::string const & Osoba::ime() const {
	return m_ime;
}

inline std::string const & Osoba::prezime() const {
	return m_prezime;
}

inline bool Osoba::jednak(Osoba const & osoba) const {
	return this->ime() == osoba.ime() && this->prezime() == osoba.prezime();
}

inline std::string Osoba::to_string() const {
	return ime() + " " + prezime();
}

/////////////////
///Zaposlenik///
///////////////

Zaposlenik::Zaposlenik(std::string ime, std::string prezime, int radno_mjesto,
		Datum pocetak_zaposlenja) :
		Osoba(ime, prezime), m_radno_mjesto(radno_mjesto), m_pocetak_zaposlenja(
				pocetak_zaposlenja) {
	std::cerr << "Zaposlenik-c : " << radno_mjesto << " " << pocetak_zaposlenja
			<< std::endl;
}

Zaposlenik::Zaposlenik(std::string ime, std::string prezime, int radno_mjesto,
		std::string pocetak_zaposlenja) :
		Zaposlenik(ime, prezime, radno_mjesto, Datum(pocetak_zaposlenja)) {
}

inline int Zaposlenik::radno_mjesto() const {
	return m_radno_mjesto;
}

inline Datum const & Zaposlenik::pocetak_zaposlenja() const {
	return m_pocetak_zaposlenja;
}

bool Zaposlenik::jednak(Osoba const & osoba) const {
	Zaposlenik const & zaposlenik = dynamic_cast<Zaposlenik const &>(osoba);
	return this->Osoba::jednak(zaposlenik)
			&& this->radno_mjesto() == zaposlenik.radno_mjesto()
			&& this->pocetak_zaposlenja() == zaposlenik.pocetak_zaposlenja();
}

inline std::string Zaposlenik::to_string() const {
	return this->Osoba::to_string() + ", radno mjesto: " + std::to_string(radno_mjesto())
			+ ", pocetak rada: " + pocetak_zaposlenja().to_string();
}

///////////////////////////
///PrivremeniZaposlenik///
/////////////////////////

PrivremeniZaposlenik::PrivremeniZaposlenik(std::string ime, std::string prezime,
		int radno_mjesto, Datum pocetak_zaposlenja, Datum kraj_zaposlenja) :
		Osoba(ime, prezime), Zaposlenik(ime, prezime, radno_mjesto,
				pocetak_zaposlenja), m_kraj_zaposlenja(kraj_zaposlenja) {
	std::cerr << "PrivremeniZaposlenik-c : " << kraj_zaposlenja << std::endl;
}

PrivremeniZaposlenik::PrivremeniZaposlenik(std::string ime, std::string prezime,
		int radno_mjesto, std::string pocetak_zaposlenja,
		std::string kraj_zaposlenja) :
		PrivremeniZaposlenik(ime, prezime, radno_mjesto,
				Datum(pocetak_zaposlenja), Datum(kraj_zaposlenja)) {
}

inline Datum const & PrivremeniZaposlenik::kraj_zaposlenja() const {
	return m_kraj_zaposlenja;
}

bool PrivremeniZaposlenik::jednak(Osoba const & osoba) const {
	PrivremeniZaposlenik const & privremeni_zaposlenik =
			dynamic_cast<PrivremeniZaposlenik const &>(osoba);
	return this->kraj_zaposlenja() == privremeni_zaposlenik.kraj_zaposlenja()
			&& this->Zaposlenik::jednak(privremeni_zaposlenik);
}

std::string PrivremeniZaposlenik::to_string() const {
	return this->Zaposlenik::to_string() + ", kraj rada: " + kraj_zaposlenja().to_string();
}

///////////////
///Student////
/////////////

Student::Student(std::string ime, std::string prezime, int godina) :
		Osoba(ime, prezime), m_godina(godina) {
	std::cerr << "Student-c : " << godina << std::endl;
}

inline int Student::godina() const {
	return m_godina;
}

bool Student::jednak(Osoba const & osoba) const {
	Student const & student = dynamic_cast<Student const &>(osoba);
	return this->godina() == student.godina() && this->Osoba::jednak(student);
}

std::string Student::to_string() const {
	return this->Osoba::to_string() + ", godina studija: " + std::to_string(godina());
}

////////////////////////
///AngaziraniStudent///
//////////////////////

AngaziraniStudent::AngaziraniStudent(std::string ime, std::string prezime,
		int radno_mjesto, Datum pocetak_zaposlenja, Datum kraj_zaposlenja,
		int godina) :
		Osoba(ime, prezime), PrivremeniZaposlenik(ime, prezime, radno_mjesto,
				pocetak_zaposlenja, kraj_zaposlenja), Student(ime, prezime,
				godina) {
	std::cerr << "AngaziraniStudent-c" << std::endl;
}

AngaziraniStudent::AngaziraniStudent(std::string ime, std::string prezime,
		int radno_mjesto, std::string pocetak_zaposlenja,
		std::string kraj_zaposlenja, int godina) :
		AngaziraniStudent::AngaziraniStudent(ime, prezime, radno_mjesto,
				Datum(pocetak_zaposlenja), Datum(kraj_zaposlenja), godina) {
}

bool AngaziraniStudent::jednak(Osoba const & osoba) const {
	AngaziraniStudent const & angazirani_student =
			dynamic_cast<AngaziraniStudent const &>(osoba);
	return this->Student::jednak(angazirani_student)
			&& this->PrivremeniZaposlenik::jednak(angazirani_student);
}

std::string AngaziraniStudent::to_string() const {
	return this->PrivremeniZaposlenik::to_string() + ", godina studija: "
			+ std::to_string(godina());
}

/////////////////////
//////operatori:////
///////////////////

bool operator==(Datum const & left, Datum const & right) {
	return left.m_dan == right.m_dan && left.m_mjesec == right.m_mjesec
			&& left.m_godina == right.m_godina;
}
std::ostream & operator<<(std::ostream & stream, Datum const & datum) {
	stream << datum.to_string();
	return stream;
}

bool operator==(Osoba const & left, Osoba const & right) {
	if (typeid(left) != typeid(right)) {
		return false;
	}
	return left.jednak(right);
}

bool operator!=(Osoba const & left, Osoba const & right) {
	return true; //!(left == right);
}

std::ostream & operator<<(std::ostream & stream, Osoba const & osoba) {
	stream << osoba.to_string();
	return stream;
}

/////////////////
////////main////
///////////////

int main() {
	AngaziraniStudent as1("Ivo", "Josic", 17, "12:02:2015", "12:03:2015", 2);

	std::cout << "----------------------------------------\n";
	std::cout << as1 << std::endl;
	std::cout << "----------------------------------------\n";

	AngaziraniStudent as2(as1);
	assert(as1 == as2);

	PrivremeniZaposlenik pz1 = as2;
	std::cout << "----------------------------------------\n";
	std::cout << pz1 << std::endl;
	std::cout << "----------------------------------------\n";
	assert(pz1 != as2);

	AngaziraniStudent * pas3 = new AngaziraniStudent("Nino", "Gusic", 16,
			"12:02:2015", "12:03:2015", 2);
	Student * ps = pas3;
	std::cout << ps->prezime() << std::endl;
	std::cout << "----------------------------------------\n";
	std::cout << *pas3 << std::endl;
	std::cout << "----------------------------------------\n";

	assert(as2 != *pas3);

	std::cout << "------------------\n";
	delete pas3;
	return EXIT_SUCCESS;
}
