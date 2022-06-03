#pragma once

#include "conexion.h"
#include <string>

using namespace std;

class empleados {

	//atributos
private:

	string idemple, id_puesto, nombres, apellidos, genero, direccion,
		fecha_ingreso, dpi, fecha_nacimiento, fecha_iniciolabor;

	int telefono = 0;

	//constructor
public:
	empleados() {

	}
	empleados(string _idemple, string _direccion, string nom, string ape,
		string gen, int tel, string fi, string _dpi, string _fecha_nacimiento,
		string _id_puesto, string _fecha_iniciolabor) {

		direccion = _direccion;
		nombres = nom;
		apellidos = ape;
		genero = gen;
		telefono = tel;
		fecha_ingreso = fi;
		dpi = _dpi;
		fecha_nacimiento = _fecha_nacimiento;
		id_puesto = _id_puesto;
		fecha_iniciolabor = _fecha_iniciolabor;
		idemple = _idemple;

	}

	// metodo
	void crear() {
		int q_estado;
		conexion cn = conexion();
		cn.abrir_conexion();
		if (cn.getConectar()) {

			int  gen;
			string  nom, ape, correo, fecha_ingreso, fecha_nacimiento,fecha_inicio, dire;
			int  telefono, dpi, id_puesto;
			cout << "Ingrese Nombres: " << endl;
			cin.ignore();
			getline(cin, nom);
			cout << "Ingrese Apellidos: " << endl;
			cin.ignore();
			getline(cin, ape);

			cout << "Ingrese su genero (FEMENINO = 0 / MASCULINO = 1)" << endl;
			cin >> gen;
			cin.ignore();

			cout << "Ingrese su direccion " << endl;
			getline(cin, dire);
			cout << "Ingrese Telefono: " << endl;
			cin >> telefono;
			cin.ignore();
			cout << "Ingrese DPI: " << endl;
			cin.ignore();
			cin >> dpi;
			cin.ignore();
			cout << "Ingrese su fecha nacimiento (año-mes-dia)" << endl;
			getline(cin, fecha_nacimiento);
			cout << "Ingrese el ID_puesto de la tabla puesto para poder realizar la incercion: " << endl;
			cin >> id_puesto;
			cin.ignore();
			cout << "Ingrese fecha de inicio de labores (año-mes-dia)" << endl;
			getline(cin, fecha_inicio);

			string DPI = to_string(dpi);
			string t = to_string(telefono);
			string puesto = to_string(id_puesto);
			string genero = to_string(gen);
			string insert = "INSERT INTO `almacen`.`empleados` (`nombre`, `apellido`, `direccion`, `telefono`, `dpi`, `genero`, `fecha_nacimiento`, `idpuesto`, `fecha_inicio_labores`, `fechaingreso`) VALUES ('" + nom + "', '" + ape + "', '"+ dire + "', '" + t + "', '" + DPI + "', ' " + genero + " ', '" + fecha_nacimiento + "', '" + puesto + "', '" + fecha_inicio + "', 'now()');";

			const char* i = insert.c_str();

			q_estado = mysql_query(cn.getConectar(), i);

			if (!q_estado) {
				cout << "Ingreso Exitoso...." << endl;
			}
			else {
				cout << "xxxx Error al Ingresar xxxxx" << endl;
				cout << insert << endl << mysql_error(cn.getConectar()) << endl;
			}
		}
		else {
			cout << "Error en la Conexion..." << endl;
		}
		cn.cerrar_conexion();
	}

	void leer() {

		int q_estado;
		conexion cn = conexion();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;

		cn.abrir_conexion();

		if (cn.getConectar()) {
			string consulta = "SELECT `empleados`.`idempleados`,`empleados`.`nombre`,`empleados`.`apellido`,`empleados`.`direccion`,`empleados`.`telefono`,`empleados`.`dpi`,`empleados`.`genero`,`empleados`.`fecha_nacimiento`,`empleados`.`idpuesto`,`empleados`.`fecha_inicio_labores`,`empleados`.`fechaingreso` FROM `almacen`.`empleados`;";

			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);

			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());

				cout << "-----------------------------empleados----------------------------" << endl;
				while (fila = mysql_fetch_row(resultado)) {
					cout << fila[0] << " , " << fila[1] << " , " << fila[2] << " , " << fila[3] << " , " << fila[4] << " , " << fila[5] << " , " << fila[6] << " , " << fila[7] <<" , " << fila[8] << " , " << fila[9] << endl;
				}
			}
			else {
				cout << "xxxx Error al Consultar xxxxx" << endl;
			}
		}
		else {
			cout << "Error en la Conexion..." << endl;
		}
		cn.cerrar_conexion();
	}

	void actualizar() {
		conexion cn = conexion();
		cn.abrir_conexion();

		if (cn.getConectar()) {
			int id;
			int q_estado;
			string nom, ape, dir, fechanacimiento, fechainicio;
			int gen, telefono, dpi, idpuesto;
			cout << "Ingrese el ID que desea eliminar de Empleados" << endl;
			cin >> id;
			cout << "Ingrese Nombres: " << endl;
			cin.ignore();
			getline(cin, nom);
			cout << "Ingrese Apellidos: " << endl;
			cin.ignore();
			getline(cin, ape);

			cout << "Ingrese su genero  (FEMENINO = 0 / MASCULINO = 1)" << endl;
			cin >> gen;
			cin.ignore();

			cout << "Ingrese su direccion " << endl;
			getline(cin, dir);
			cout << "Ingrese Telefono: " << endl;
			cin >> telefono;
			cin.ignore();
			cout << "Ingrese DPI: " << endl;
			cin >> dpi;
			cin.ignore();

			cout << "Ingrese su fecha nacimiento (año-mes-dia)" << endl;
			getline(cin, fechanacimiento);
			cout << "Ingrese el ID_puesto de la tabla puesto para poder realizar la incercion: " << endl;
			cin >> idpuesto;
			cin.ignore();

			cout << "Ingrese fecha de inicio de labores (año-mes-dia)" << endl;
			getline(cin, fechainicio);

			string ID = to_string(id);
			string t = to_string(telefono);
			string DPI = to_string(dpi);
			string gene = to_string(gen);
			string puesto = to_string(idpuesto);
			string update = "UPDATE `almacen`.`empleados` SET `nombre` = '" + nom + "', `apellido` = '"+ ape + "', `direccion` = '" + dir + "', `telefono` = '" + t + "', `dpi` = '" + DPI + "', `genero` = '" + gene + "', `fecha_nacimiento` = '" + fechanacimiento + "', `idpuesto` = '" + puesto + "', `fecha_inicio_labores` = '"+ fechainicio + "' WHERE (`idempleados` = '" + ID + "');";
			const char* i = update.c_str();

			q_estado = mysql_query(cn.getConectar(), i);

			if (!q_estado) {
				cout << " Registro Actualizado Exitosamente... " << endl;
			}
			else {
				cout << "xxx Error al actualizar el Registro xxx " << endl;
				cout << update << endl << mysql_error(cn.getConectar()) << endl;
			}
		}
		else {
			cout << "Error en la conexion... " << endl;
		}
		cn.cerrar_conexion();
	}

	void eliminar()
	{
		conexion cn = conexion();
		cn.abrir_conexion();

		if (cn.getConectar()) {
			int q_estado;
			int id;
			cout << "Ingrese el ID del empleado que desea eliminar" << endl;
			cin >> id;

			string ID = to_string(id);
			string eliminar = "DELETE FROM `almacen`.`empleados` WHERE (`idempleados` = '" + ID + "');";

			const char* i = eliminar.c_str();
			q_estado = mysql_query(cn.getConectar(), i);

			if (!q_estado) {
				cout << " Registro Eliminado Exitosamente... " << endl;
			}
			else {
				cout << "xxx Error al eliminar el Registro xxx " << endl;
			}
		}
		else {
			cout << "Error en la conexion... " << endl;
		}
		cn.cerrar_conexion();
	}


};
