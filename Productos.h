#pragma once

#include "conexion.h"
#include <string>

using namespace std;

class Productos {



private:

	string idproducto, producto, idmarca, descripcion, imagen, precio_costo, precio_venta, existencia, fechaingreso;



public:
	Productos() {

	}

	Productos(string _idproducto, string _producto, string _idmarca, string _descripcion, string _imagen,
		string _precio_costo, string _precio_venta, string _existencia, string _fechaingreso) {

		idproducto = _idproducto;
		producto = _producto;
		idmarca = _idmarca;
		descripcion = _descripcion;
		imagen = _imagen;
		precio_costo = _precio_costo;
		precio_venta = _precio_venta;
		existencia = _existencia;
		fechaingreso = _fechaingreso;

	}


	void crear() {
		int q_estado;
		conexion cn = conexion();
		cn.abrir_conexion();
		if (cn.getConectar()) {

			cout << "Ingrese Producto: " << endl;
			cin >> producto;
			cout << "Ingrese idmarca de la tabla marcas: " << endl;
			cin >>idmarca;
			cin.ignore();
			cout << "Ingrese descripcion: " << endl;
			getline(cin, descripcion);
			cout << "Ingrese la Imagen: " << endl;
			cin >> imagen;
			cout << "Ingrese precio costo: " << endl;
			cin >> precio_costo;
			cout << "Ingrese precio venta: " << endl;
			cin >> precio_venta;
			cout << "Ingrese existencias: " << endl;
			cin >> existencia;

			string insert = "INSERT INTO `almacen`.`productos`(`producto`,`idmarca`,`descripcion`,`imagen`,`precio_costo`,`precio_venta`,`existencia`,`fecha_ingreso`) VALUES('" + producto + "', '" + idmarca + "', '" + descripcion + "', '" +  imagen + "', '" + precio_costo + "', '" + precio_venta + "', '" + existencia + "', current_time()); ";

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
			string consulta = "SELECT `productos`.`idproductos`,`productos`.`producto`,`productos`.`idmarca`,`productos`.`descripcion`,`productos`.`imagen`,`productos`.`precio_costo`,`productos`.`precio_venta`,`productos`.`existencia`,`productos`.`fecha_ingreso`FROM `almacen`.`productos`;";

			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);

			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());

				cout << "-----------------------------empleados----------------------------" << endl;
				while (fila = mysql_fetch_row(resultado)) {
					cout << fila[0] << " , " << fila[1] << " , " << fila[2] << " , " << fila[3] << " , " << fila[4] << " , " << fila[5] << " , " << fila[6] << " , " << fila[7] << " , " << fila[8] << endl;
					system("PAUSE");
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
			int id;
			string producto, descripcion,imagen,fechaingreso;
			int precio_costo, precio_venta, existencia,idmarca;
			cout << "Ingrese el id del producto que desea actualizar: " << endl;
			cin >> id;
			cout << "Ingrese Producto: " << endl;
			cin >> producto;
			cout << "Ingrese idmarca de la tabla marcas: " << endl;
			cin >> idmarca;
			cin.ignore();
			cout << "Ingrese descripcion: " << endl;
			getline(cin, descripcion);
			cout << "Ingrese la Imagen: " << endl;
			cin >> imagen;
			cout << "Ingrese precio costo: " << endl;
			cin >> precio_costo;
			cout << "Ingrese precio venta: " << endl;
			cin >> precio_venta;
			cout << "Ingrese existencias: " << endl;
			cin >> existencia;
			cout << "Ingrese fecha de ingreso: " << endl;
			cin >> fechaingreso;

			string ID = to_string(id);
			string compra = to_string(precio_costo);
			string venta = to_string(precio_venta);
			string exis = to_string(existencia);
			string marca = to_string(idmarca);
			string update = "UPDATE `almacen`.`productos` SET `producto` = '"+ producto + "', `idmarca` = '" + marca + "', `descripcion` = '"+ descripcion + " ', `imagen` = '" + imagen + "', `precio_costo` = '"+ compra + " ', `precio_venta` = '"+ venta + "', `existencia` = '"+ exis + "', `fecha_ingreso` = '" + fechaingreso + "' WHERE (`idproductos` = '"+ ID + "');";
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
			cout << "Ingrese el id del Producto que desea elimimnar" << endl;
			cin >> id;
			string ID = to_string(id);
			string eliminar = "DELETE FROM `almacen`.`productos` WHERE (`idproductos` = '" + ID + "');";

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



