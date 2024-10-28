#pragma once
#include <iostream>
#include <string>

using std::string;
using std::ostream;
using std::cout;
using std::endl;


class clsPerson {
private:
	unsigned int attIdentificacion;
	string attNombres, attApellidos, attTelefono, attDireccion;
	string attLongitud, attLatitud;
public:

	clsPerson(int prmIdentificacion, string prmNombres, string prmApellidos, string prmTelefono, string prmDireccion, string prmLongitud,  string prmLatitud) {
		attIdentificacion = prmIdentificacion;
		attNombres = prmNombres;
		attApellidos = prmApellidos;
		attTelefono = prmTelefono;
		attDireccion = prmDireccion;
		attLongitud = prmLongitud;
		attLatitud = prmLatitud;
	}

	friend ostream& operator << (ostream& os, clsPerson& p) {
		os << p.attIdentificacion << endl;
		os << p.opGenerateURL() << endl;
		return os;
	}

	string opGenerateURL() {
		return "https://www.google.com/maps/search/?api=1&query=" + attLatitud +"," + attLongitud;
	}
};