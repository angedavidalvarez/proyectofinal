#pragma once
#include <string>
#include "conexion.h"
#include <ctime>
using namespace std;
class Cliente {
	//atributos
private:
	string nit, nombres, apellidos, genero, correo_electronico, fecha_ingreso;
	int telefono = 0;
	//constructor
public:
	Cliente() {
	}
	Cliente(string nom, string ape, string gen, int tel, string correo, string fi, string n) {
		nit = n;
		nombres = nom;
		apellidos = ape;
		genero = gen;
		correo_electronico = correo;
		telefono = tel;
		fecha_ingreso = fi;
	}
	// metodo
	void crear() {
		int q_estado;
		conexion cn = conexion();
		cn.abrir_conexion();
		if (cn.getConectar()) {
			string  nombres, apellidos, correo_electronico, fecha_ingreso;
			int genero, nit, telefono;
			cin.ignore();
			cout << "Ingrese NIT: " << endl;
			cin >> nit;
			cout << "Ingrese Nombres: " << endl;
			cin.ignore();
			getline(cin, nombres);
			cout << "Ingrese Apellidos: " << endl;
			getline(cin, apellidos);

			cout << "Ingrese su genero (FEMENINO = 0 / MASCULINO = 1)" << endl;
			cin >> genero;
			cin.ignore();

			cout << "Ingrese Telefono: " << endl;
			cin >> telefono;
			cin.ignore();
			cout << "Ingrese Correo Electronico: " << endl;
			cin.ignore();
			getline(cin, correo_electronico);
			cout << "Ingrese Fecha de Ingreso (año-mes-dia): " << endl;
			getline(cin, fecha_ingreso);


			string t = to_string(telefono);
			string ni = to_string(nit);
			string gen = to_string(genero);

			string insert = "INSERT INTO `almacen`.`clientes` (`nombre`, `apellido`, `nit`, `genero`, `telefono`, `correo_electronico`, `fechaingreso`) VALUES ('" + nombres + "', '"+ apellidos + "', '"+ ni + "', '" + gen + "', '"+ t + "', '" + correo_electronico + "', '" + fecha_ingreso + "');";
			const char* i = insert.c_str();
			q_estado = mysql_query(cn.getConectar(), i);
			if (!q_estado) {
				cout << "Ingreso Exitoso...." << endl;
			}
			else {
				cout << "---- Error al Ingresar ----" << endl;
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
			string consulta = "select * from clientes";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				cout << "-----------------------------Clientes----------------------------" << endl;
				while (fila = mysql_fetch_row(resultado)) {
					cout << fila[0] << " , " << fila[1] << " , " << fila[2] << " , " << fila[3] << " , " << fila[4] << " , " << fila[5] << " , " << fila[6] << " , " << fila[7] << endl;
				}
			}
			else {
				cout << "---- Error al Consultar ----" << endl;
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
			int q_estado;
			string  nom, ape, correo, fi;
			int id=0;
			int genero, nit, telefono;
			cout << "Ingrese el ID del cliente que desea Actualizar: " << endl;
			cin >> id;
			cin.ignore();

			cout << "Ingrese nombres: " << endl;
			getline(cin, nom);

			cout << "Ingrese apellidos: " << endl;
			getline(cin, ape);

			cout << "Ingrese Nit (Sin Guiones): " << endl;
			cin >> nit;

			cout << "Ingrese Genero (FEMENINO = 0 / MASCULINO = 1): " << endl;
			cin >> genero;

			cout << "Ingrese Telefono: " << endl;
			cin >> telefono;
			cin.ignore();

			cout << "Ingrese Correo Electronico: " << endl;
			getline(cin, correo);

			cout << "Ingrese Fecha de Ingreso ( Año-mes-dia) : " << endl;
			getline(cin, fi);

			string ID = to_string(id);
			string ni = to_string(nit);
			string gen = to_string(genero);
			string t = to_string(telefono);
			string update = "UPDATE `almacen`.`clientes` SET `nombre` = '" + nom + "', `apellido` = '" + ape + "', `nit` = '"+ ni + "', `genero` = '"+ gen + "', `telefono` = '"+ t + "', `correo_electronico` = '"+ correo + "', `fechaingreso` = '" + fi + "' WHERE (`idclientes` = '"+ ID + "');";
			const char* i = update.c_str();
			q_estado = mysql_query(cn.getConectar(), i);
			if (!q_estado) {
				cout << " Registro Actualizado Exitosamente... " << endl;
			}
			else {
				cout << "xxx Error al actualizar el Registro xxx " << endl;
			}

		}
		else {
			cout << "Error en la conexion... " << endl;
		}
		cn.cerrar_conexion();
	}
	void eliminar() {
		conexion cn = conexion();
		cn.abrir_conexion();
		if (cn.getConectar()) {
			int q_estado;
			int id;
			cout << "Ingrese el ID del cliente que desea eliminar" << endl;
			cin >> id;
			string ID = to_string(id);

			string eliminar = "DELETE FROM `almacen`.`clientes` WHERE (`idclientes` = '"+ ID + "');";
			const char* i = eliminar.c_str();
			q_estado = mysql_query(cn.getConectar(), i);
			if (!q_estado) {
				cout << " Registro Eliminado Exitosamente... " << endl;
			}
			else {
				cout << "--- Error al eliminar el Registro --- " << endl;
			}

		}
		else {
			cout << "Error en la conexion... " << endl;
		}
		cn.cerrar_conexion();
	}

};