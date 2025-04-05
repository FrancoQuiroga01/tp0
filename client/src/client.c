#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char *ip;
	char *puerto;
	char *valor;

	t_log *logger;
	t_config *fileConfig;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();
	log_info(logger, "Iniciando cliente...");

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	fileConfig = iniciar_config();
	log_info(logger, config_get_string_value(fileConfig, "CLAVE"));

	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	ip = config_get_string_value(fileConfig, "IP");
	puerto = config_get_string_value(fileConfig, "PUERTO");
	valor = config_get_string_value(fileConfig, "CLAVE");

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);
	log_info(logger, "Conectado al servidor");
	log_info(logger, "IP: %s", ip);
	log_info(logger, "PUERTO: %s", puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor, conexion);
	log_info(logger, "Enviando mensaje al servidor");

	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, fileConfig);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log *iniciar_logger(void)
{
	t_log *nuevo_logger;

	nuevo_logger = log_create("/home/utnso/Documents/tp0/client/log/cliente.log", "clientLogger", 1, LOG_LEVEL_INFO);

	return nuevo_logger;
}

t_config *iniciar_config(void)
{
	t_config *nuevo_config;

	nuevo_config = config_create("/home/utnso/Documents/tp0/client/cliente.config");

	return nuevo_config;
}

void leer_consola(t_log *logger)
{
	char *linea;
	while (1)
	{
		linea = readline(">");

		if (strcmp(linea, "") == 0)
		{
			break;
			free(linea);
		}
		printf("%s\n", linea);
		log_info(logger, linea);
		free(linea);
	}
}

void paquete(int conexion)
{

	char *leido = NULL;
	t_paquete *paquete;

	paquete = crear_paquete();

	leido = readline("> ");
	while (strcmp(leido, "") != 0)
	{
		agregar_a_paquete(paquete, leido, strlen(leido) + 1);
		free(leido);
		leido = readline("> ");
	}

	free(leido);

	enviar_paquete(paquete, conexion);

	eliminar_paquete(paquete);
}

void terminar_programa(int conexion, t_log *logger, t_config *config)
{
	log_destroy(logger);
	config_destroy(config);
	close(conexion);
}
