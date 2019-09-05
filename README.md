# icc3201-201920-tarea1
Repositorio base para tarea 1 de Sistemas Operativos y Redes 201920

Miembros:
-Francisco Jimenez
-Vcente Lucero

Informe de la Tarea 1:
	
*Dificultades:
	- El como realizar implementar correctamente el socket para comunicar al cliente con el servidor. 
	- La lectura de datos parael server dado que recibian mas bytes de lo que realmente utilizaba el comando, esto debido al tamaño predefinido del buffer al inicio del main.

*No implementado:
	- No esta implementado el manejor de errores en caso de se envien comandos incompletos, como por ejemplo update(key) en vez de update(key,value)
	- listen del cliente ante las respuestas del usuario.
	- procesar key y value para guardarlos en la base de datos.
	- generar un valor aleatorio si key llega vacio 
	
*Problemas conocidos:
	- El temporizador a pesar de estar implementado, no siempre realiza su correcta funcion, puede ser debido al mal uso del thread y de la recepcion de su finalización. 
	- aparecen caracteres extra al momento de recibir los valores en el servidor 
