#pragma once

#include <string>
#include "conexion.h"

using namespace std;
class Proveedores {
	//atributos
private:
	string nit, direccion, proveedor;
	int telefono = 0;
	//constructor
public:
	Proveedores() {
	}
	Proveedores(string dir, string prov, int tel, string n) {
		nit = n;
		proveedor = prov;
		direccion = dir;
		telefono = tel;
	}



	// metodo


	void crear() {
		int q_estado;
		conexion cn = conexion();
		cn.abrir_conexion();
		if (cn.getConectar()) {

			string dir, proveedor;
			int nit, telefono;
			cin.ignore();
			cout << "Ingrese NIT: " << endl;
			cin >> nit;
			cin.ignore();
			cout << "Ingrese Direccion: " << endl;
			getline(cin, dir);
			cout << "Ingrese Proveedor: " << endl;
			getline(cin, proveedor);
			cout << "Ingrese Telefono: " << endl;
			cin >> telefono;
			cin.ignore();
			string ni = to_string(nit);
			string t = to_string(telefono);
			string insert = "INSERT INTO `almacen`.`proveedores` (`Proveedor`, `Nit`, `Direccion`, `Telefono`) VALUES ('"+ proveedor + "', '" + ni + "', '"+ dir + "', '" + t + "');";
			const char* i = insert.c_str();
			q_estado = mysql_query(cn.getConectar(), i);
			if (!q_estado) {
				cout << "Ingreso Exitoso...." << endl;
			}
			else {
				cout << "xxxx Error al Ingresar xxxxx" << endl;
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
			string consulta = "select * from proveedores";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				cout << "-----------------------------Proveedores----------------------------" << endl;
				while (fila = mysql_fetch_row(resultado)) {
					cout << fila[0] << " , " << fila[1] << " , " << fila[2] << " , " << fila[3] << " , " << fila[4] << endl;
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
			int q_estado;
			string  dir, prove;
			int nit, id;
			int telefono;
			cout << "Ingrese el Id del Proveedor que desea Actualizar: " << endl;
			cin >> id;
			cin.ignore();

			cout << "Ingrese Proveedor: " << endl;
			getline(cin, prove);

			cout << "Ingrese Nit: " << endl;
			cin >> nit;
			cin.ignore();

			cout << "Ingrese Direccion: " << endl;
			getline(cin, dir);

			cout << "Ingrese Telefono: " << endl;
			cin >> telefono;
			cin.ignore();
			string tel = to_string(telefono);
			string ni = to_string(nit);
			string ID = to_string(id);
			string update = "UPDATE `almacen`.`proveedores` SET `Proveedor` = '" + prove + "', `Nit` = '"+ ni + "', `Direccion` = '" + dir + "', `Telefono` = '" + tel + "' WHERE (`idProveedor` = '" + ID + "');";
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
			cout << "Ingrese el id del Proveedor que desea eliminar" << endl;
			cin >> id;
			string ID = to_string(id);
			string eliminar = "DELETE FROM `almacen`.`proveedores` WHERE (`idProveedor` = '" + ID + "');";
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
