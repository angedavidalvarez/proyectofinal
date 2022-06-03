#pragma once

#include <string>
# include <time.h>

#include "conexion.h"
#include "gotoxy.h"
#include "Cliente.h"

using namespace std;

Cliente* client = new Cliente();

class Ventas
{
protected: int idcl = 0, idemp = 0, idpr = 0;
		 string serie, fechafact;

public:

	struct registroVentas {
		float cantidad = 0;
		float precio = 0;
		float total = 0;
		float totalPagar = 0;
		int nofact = 1;
	}factura[100];

	string fecha() {
		time_t now = time(0);
		tm time;
		char buf[80];
		time = *localtime(&now);

		strftime(buf, sizeof(buf), "%Y-%m-%d", &time);
		return buf;
	}

	conexion cn = conexion();
	int q_estado;
	MYSQL_ROW fila;
	MYSQL_RES* resultado;
	registroVentas registro;

	short z, x = 14, y = 10, f, cantcompra;
	
	void buscarcl(string nit) {
		
		char addnit;

		cn.abrir_conexion();

		if (cn.getConectar()) {
			string consulta = "SELECT * FROM clientes WHERE nit = '" + nit + "'";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);

			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				
				uint64_t rows = mysql_num_rows(resultado);

				if (mysql_num_rows(resultado) > 0) {
					while (fila = mysql_fetch_row(resultado)) {
						gotoxy(25, 4);  cout << "Nombre: " << fila[1] << " " << fila[2] << endl;
						int id = atoi(fila[0]);
						int id_empl;

						gotoxy(65, 4); cout << "Ingrese su ID de empleado: ";
						cin >> id_empl;

						ingresarventa(id, id_empl);
					}
				}
				else {
					cout << "El NIT del cliente no se encuentra en la base, desea agregarlo S/N: ";
					cin >> addnit;
					if (addnit == 'S') {
                          // aqui debe ir la funcion para agregar nuevo cliente.
						system("cls");
						string  nombres, apellidos, correo_electronico, fecha_ingreso;
						int genero, nit, telefono;
						cin.ignore();
						cout << "Ingrese NIT: " << endl;
						cin >> nit;
						cin.ignore();
						cout << "Ingrese Nombres: " << endl;
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

						string insert = "INSERT INTO `almacen`.`clientes` (`nombre`, `apellido`, `nit`, `genero`, `telefono`, `correo_electronico`, `fechaingreso`) VALUES ('" + nombres + "', '" + apellidos + "', '" + ni + "', '" + gen + "', '" + t + "', '" + correo_electronico + "', '" + fecha_ingreso + "');";
						const char* i = insert.c_str();
						q_estado = mysql_query(cn.getConectar(), i);
						if (!q_estado) {
							cout << "Ingreso Exitoso...." << endl;
							system("cls");

							buscarcl(ni);
						}
						else {
							cout << "---- Error al Ingresar ----" << endl;
						}
					}
					else if(addnit == 'N')
					{
						string nit;
						system("cls");
						cout << "Por favor vuelva a ingresar el nit: ";
						cin >> nit;
						buscarcl(nit);

					}
				}
			}
			else {
				cout << "Error al consultar..." << endl;
				cout << consulta << endl << mysql_error(cn.getConectar()) << endl;
			}
		}
		else {
			cout << "Conexion fallida..." << endl;
		}
		cn.cerrar_conexion();
	}

	void ingresarventa(int id_c, int id_e) {

		cn.abrir_conexion();
		
		if (cn.getConectar()) {
			int nf1 = numerofact();

			string nf = to_string(nf1 + 1);
			string idcl1 = to_string(id_c);
			string idem = to_string(id_e);

			string insertv = "INSERT INTO ventas(nofactura, serie, fechafactura, idcliente, idempleado, fechaingreso) VALUES (" + nf + ", 'A', '" + fecha() + "', " + idcl1 + ", " + idem + ", now()); ";
			
			const char* i = insertv.c_str();
			q_estado = mysql_query(cn.getConectar(), i);

			if (!q_estado) {
				facturar();
				//cout << "Ingreso exitoso..." << endl;
			}
			else {
				cout << "Error al ingresar encabezado venta" << endl;
				cout << insertv << endl << mysql_error(cn.getConectar()) << endl;
			}
		}
		else {
			cout << "Conexion fallida..." << endl;
		}
		cn.cerrar_conexion();
	}

	void facturar() {
		x = 14;
		y = 10;

		float acumulador = 0;
		int prod, cant = 0, nofactura = 1;
		char SN;
		string str, prodto, canti;

		gotoxy(10, 8); cout << "ID Producto ";
		gotoxy(27, 8); cout << "Producto ";
		gotoxy(57, 8); cout << "Cantidad ";
		gotoxy(72, 8); cout << "Precio ";

		cn.abrir_conexion();

		do {
			gotoxy(x+1, y-1);
			cin >> prod;
			prodto = to_string(prod);
			cin.ignore();
			//getline(cin, prodto);

			str = "SELECT * FROM productos WHERE idproductos = " + prodto; cout << endl;
			
			if (cn.getConectar()) {
				const char* c = str.c_str();
				q_estado = mysql_query(cn.getConectar(), c);
				if (!q_estado) {
					resultado = mysql_store_result(cn.getConectar());

					uint64_t rows = mysql_num_rows(resultado);

					if (mysql_num_rows(resultado) > 0) {
						while (fila = mysql_fetch_row(resultado)) {
							registro.precio = stof(fila[6]);
							string price = to_string(registro.precio);

							gotoxy(x + 15, y);
							cout << fila[3] << endl;
							gotoxy(x + 47, y);
							cin >> registro.cantidad;
							canti = to_string(registro.cantidad);
							cin.ignore();

							gotoxy(x + 60, y);
							factura[f].total = registro.cantidad * registro.precio;
							printf("%.2f", factura[f].total);
							acumulador += factura[f].total;
							fflush(stdin);

							gotoxy(x, y+10);
							string str = "INSERT INTO `almacen`.`venta_detalle` (`idventa`, `idproducto`, `cantidad`, `precio_unitario`) VALUES((SELECT MAX(idventas) FROM ventas), " + prodto + ", " + canti + ", " + price +");";
							
							const char* i = str.c_str();
							q_estado = mysql_query(cn.getConectar(), i);

							if (!q_estado) {
								//cout << "Ingreso exitoso..." << endl;
							}

						}
					}
				}
			}
			else {
				cout << "Conexion fallida..." << endl;
				cn.cerrar_conexion();
			}

			gotoxy(80, 7);
			fflush(stdin);
			factura[f].totalPagar = acumulador;
			gotoxy(60, 25);
			printf("Total a pagar: %.2f", acumulador);

			gotoxy(80, 7);
			cout << "Agregar mas? (S/N): ";
			gotoxy(100, 7);
			cin >> SN;
			if (SN == 'N' || SN == 'n') {
				cout << " " << endl;
				cout << " " << endl;
				cout << "Compra Finalizada" << endl;
			}
			f++;
			y += 2;
			
		} while (SN == 'S' || SN == 's');

		cn.cerrar_conexion();
	}	

	int numerofact() {
		int fact = 0;
		cn.abrir_conexion();

		if (cn.getConectar()) {
			string consulta = "SELECT MAX(nofactura) FROM ventas;";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);

			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());

				uint64_t rows = mysql_num_rows(resultado);

				if (mysql_num_rows(resultado) > 0) {
					while (fila = mysql_fetch_row(resultado)) {
						fact = atoi(fila[0]);
						gotoxy(25, 3); cout << "No.: " << fact + 1;
					}
				}
				else {
					cout << "El NIT del cliente no se encuentra en la base, desea agregarlo S/N: ";
				}
			}
			else {
				cout << "Error al consultar..." << endl;
				cout << consulta << endl << mysql_error(cn.getConectar()) << endl;
			}
		}
		else {
			cout << "Conexion fallida..." << endl;
		}
		return fact;
	}

	void mostrarventa(int nofact) {

		//int prod;
		string prodto, canti;

		cn.abrir_conexion();

		if (cn.getConectar()) {
			string f = to_string(nofact);
			string strv = "SELECT idventa, nofactura, serie, fechafactura, c.nit, c.nombres, c.apellidos FROM ventas v INNER JOIN clientes c ON v.idcliente = c.idCliente WHERE nofactura = " + f;

			const char* c = strv.c_str();
			q_estado = mysql_query(cn.getConectar(), c);

			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				while (fila = mysql_fetch_row(resultado)) {

					system("cls");
					gotoxy(5, 3);
					cout << "Fecha: "<< fila[3];
					gotoxy(25, 3);
					cout << "No: " << fila[1];
					gotoxy(36, 3);
					cout << "Serie: " << fila[2];
					gotoxy(5, 4);
					cout << "NIT: " << fila[4];
					gotoxy(25, 4);  cout << "Nombre: " << fila[5] << " " << fila[6] << endl;
					gotoxy(10, 8); cout << "ID Producto ";
					gotoxy(27, 8); cout << "Producto ";
					gotoxy(57, 8); cout << "Cantidad ";
					gotoxy(72, 8); cout << "Precio ";

					string idventa = to_string(atoi(fila[0]));

					string strvd = "SELECT vd.idproducto, p.descripcion, vd.existencia, (vd.existencia * vd.precio_venta) AS Precio FROM venta_detalle vd INNER JOIN producto p ON vd.idproducto = p.idproducto WHERE idventa = " + idventa;

					const char* cc = strvd.c_str();
					q_estado = mysql_query(cn.getConectar(), cc);

					if (!q_estado) {
						resultado = mysql_store_result(cn.getConectar());

						if (mysql_num_rows(resultado) > 0) {
							y = 10;
							x = 15;
							while (fila = mysql_fetch_row(resultado)) {
								
								gotoxy(x, y++); cout << fila[0];
								gotoxy(x + 15, y-1); cout << fila[1];
								gotoxy(x + 47, y - 1); cout << atoi(fila[2]);
								gotoxy(x + 60, y - 1); cout << stof(fila[3]);
							}

							char SN;
							gotoxy(38, 20);
							cout << "Desea modificar los productos vendidos (S/N): ";
							cin >> SN;

							if (SN == 'S' || SN == 's') {
								facturar();
								/*gotoxy(x, 9);
								cin >> prod;
								prodto = to_string(prod);
								cin.ignore();
								gotoxy(x + 15, 9);
								cout << fila[3] << endl;
								gotoxy(x + 47, 9);
								cin >> registro.cantidad;
								canti = to_string(registro.cantidad);
								cin.ignore();*/
								
							}
						}
					}
					else {
						cout << "Error al consultar encabezado venta" << endl;
						cout << strvd << endl << mysql_error(cn.getConectar()) << endl;
					}
				}
			}
			else {
				cout << "Error al consultar..." << endl;
			}
		}
		else {
			cout << "Conexion fallida..." << endl;
		}
		cn.cerrar_conexion();

	}

	void eliminarventa() {

		gotoxy(15, 15);
		int fact;
		cout << "Ingrese la factura que desea eliminar: ";
		cin >> fact;

		cn.abrir_conexion();

		if (cn.getConectar()) {

			string f = to_string(fact);
			string eliminard = "DELETE FROM `almacen`.`venta_detalle` WHERE (`idventa_detalle` = '(SELECT `ventas`.`idventas`FROM `almacen`.`ventas` WHERE (`nofactura` = '" + f + "'));";
			string eliminarv = "DELETE FROM ventas WHERE nofactura = '" + f + "';";

			const char* i = eliminard.c_str();
			q_estado = mysql_query(cn.getConectar(), i);

			if (!q_estado) {
				cout << "Eliminacion exitosa..." << endl;
			}
			else {
				cout << "Error al eliminar..." << endl;
				cout << eliminard << endl << mysql_error(cn.getConectar()) << endl;
			}

			const char* ii = eliminarv.c_str();
			q_estado = mysql_query(cn.getConectar(), ii);

			if (!q_estado) {
				cout << "Eliminacion exitosa..." << endl;
				return;
			}
			else {
				cout << "Error al eliminar..." << endl;
				cout << eliminarv << endl << mysql_error(cn.getConectar()) << endl;
			}
		}


	};

	void consumidorfinal(){


	}
};
