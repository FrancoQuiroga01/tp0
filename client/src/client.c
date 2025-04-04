#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char *ip;
	char *puerto;
	char *valor;
	char *linea;

	t_log *logger;
	t_config *config;

	/* ---------------- LOGGING ---------------- */

	logger = log_create("/home/utnso/Documents/tp0/client/log/tp0.log", "clientLogger", 1, LOG_LEVEL_INFO);

	log_info(logger, "Hola! soy un log");

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = config_create("/home/utnso/Documents/tp0/client/cliente.config");

	log_info(logger, config_get_string_value(config, "CLAVE"));

	/* ---------------- LEER DE CONSOLA ---------------- */

	while (1)
	{
		linea = readline(">");

		if (strcmp(linea, "") == 0)
		{
			free(linea);
			abort();
		}
		printf("%s\n", linea);
		log_info(logger, linea);
		free(linea);
	}

	config_destroy(config);
	log_destroy(logger);
	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje

	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log *iniciar_logger(void)
{
	t_log *nuevo_logger;

	return nuevo_logger;
}

t_config *iniciar_config(void)
{
	t_config *nuevo_config;

	return nuevo_config;
}

void leer_consola(t_log *logger)
{
	char *leido;

	// La primera te la dejo de yapa
	leido = readline("> ");

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío

	// ¡No te olvides de liberar las lineas antes de regresar!
}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char *leido;
	t_paquete *paquete;

	// Leemos y esta vez agregamos las lineas al paquete

	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
}

void terminar_programa(int conexion, t_log *logger, t_config *config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config)
	  con las funciones de las commons y del TP mencionadas en el enunciado */
}
