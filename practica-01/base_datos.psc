	Algoritmo base_de_datos
		Definir capacidad_maxima Como Entero
		Definir total_estudiantes Como Entero
		Definir menu_opciones Como Entero
		Definir indice Como Entero
		Definir existencia Como Logico
		Definir matricula_buscada Como Cadena
		Definir respuesta_continuar Como Cadena
		
		// Variables temporales para captura
		Definir matricula_ingresada Como Cadena
		Definir nombre_ingresado Como Cadena
		Definir primer_apellido_ingresado Como Cadena
		Definir segundo_apellido_ingresado Como Cadena
		Definir carrera_ingresada Como Cadena
		Definir semestre_ingresado Como Entero
		Definir promedio_ingresado Como Real
		Definir matricula_repetida Como Logico
		Definir calificacion_valida Como Logico
		
		// Arreglos para almacenar los registros de los alumnos
		capacidad_maxima <- 100
		Dimension matricula[100]
		Dimension nombre[100]
		Dimension primer_apellido[100]
		Dimension segundo_apellido[100]
		Dimension carrera[100]
		Dimension semestre[100]
		Dimension promedio[100]
		
		// Inicialización del contador de alumnos
		total_estudiantes <- 0
		
		
		// CICLO PRINCIPAL (INTERFAZ Y CONTROL DE FLUJO)
		
		Repetir
			// Presentar interfaz con opciones
			Escribir "   BASE DE DATOS DE ESTUDIANTES DE LA UACM"   
			Escribir "1. Registrar estudiante"
			Escribir "2. Buscar estudiante por matrícula"
			Escribir "3. Salir"
			Escribir "Seleccione una opción: "
			
			//  Leer la opción seleccionada
			Leer menu_opciones
			
			//  Realizar operaciones según la opción seleccionada
			Segun menu_opciones Hacer
				
					// REGISTRO DE ESTUDIANTES
				1:
					// 1. Verificar si no se ha rebasado la capacidad máxima
					Si total_estudiantes >= capacidad_maxima Entonces
						Escribir "ERROR: Se ha alcanzado la capacidad máxima de alumnos."
					SiNo
						Escribir "--- REGISTRO DE NUEVO ALUMNO ---"
						Escribir "Ingrese matrícula:"
						Leer matricula_ingresada
						
						// 2. Revisar si la matrícula ya está repetida
						matricula_repetida <- Falso
						Para indice <- 1 Hasta total_estudiantes Con Paso 1 Hacer
							Si matricula[indice] = matricula_ingresada Entonces
								matricula_repetida <- Verdadero
							FinSi
						FinPara
						
						Si matricula_repetida = Verdadero Entonces
							Escribir "ERROR: La matrícula ya se encuentra registrada."
						SiNo
							// 3. Solicitar datos académicos y personales
							Escribir "Ingrese nombre:"
							Leer nombre_ingresado
							Escribir "Ingrese primer apellido (paterno):"
							Leer primer_apellido_ingresado
							Escribir "Ingrese segundo apellido (materno):"
							Leer segundo_apellido_ingresado
							Escribir "Ingrese carrera:"
							Leer carrera_ingresada
							Escribir "Ingrese semestre:"
							Leer semestre_ingresado
							
							// 4. Validar calificación (debe estar entre 0.0 y 10.0)
							Repetir
								Escribir "Ingrese promedio (0.0 a 10.0):"
								Leer promedio_ingresado
								
								// Validar si la calificación está entre 0.0 y 10.0
								Si promedio_ingresado >= 0.0 Y promedio_ingresado <= 10.0 Entonces
									calificacion_valida <- Verdadero
								SiNo
									calificacion_valida <- Falso
									Escribir "Promedio no válido. Debe estar en el rango de 0.0 a 10.0."
								FinSi
							Hasta Que calificacion_valida = Verdadero
							
							// 5. Guardar datos e incrementar el número de estudiantes registrados
							total_estudiantes <- total_estudiantes + 1
							matricula[total_estudiantes] <- matricula_ingresada
							nombre[total_estudiantes] <- nombre_ingresado
							primer_apellido[total_estudiantes] <- primer_apellido_ingresado
							segundo_apellido[total_estudiantes] <- segundo_apellido_ingresado
							carrera[total_estudiantes] <- carrera_ingresada
							semestre[total_estudiantes] <- semestre_ingresado
							promedio[total_estudiantes] <- promedio_ingresado
							
							Escribir "Confirmación: Estudiante registrado con éxito."
						FinSi
					FinSi
					
					// BÚSQUEDA DE ALUMNO
					
				2:
					Si total_estudiantes = 0 Entonces
						Escribir "No hay estudiantes registrados en el sistema."
					SiNo
						// 1. Recibir la matrícula
						Escribir "--- BÚSQUEDA DE ALUMNO ---"
						Escribir "Ingrese la matrícula buscada:"
						Leer matricula_buscada
						
						existencia <- Falso
						
						// 2. Recorrer la lista usando índice desde el primer hasta el último alumno
						Para indice <- 1 Hasta total_estudiantes Con Paso 1 Hacer
							// 3. Comparar cada registro
							Si matricula[indice] = matricula_buscada Entonces
								// 4. Si coincide, mostrar el registro con los datos solicitados
								Escribir "========================================"
								Escribir "DATOS DEL ESTUDIANTE ENCONTRADO:"
								Escribir "Matrícula: ", matricula[indice]
								Escribir "Nombre completo: ", nombre[indice], " ", primer_apellido[indice], " ", segundo_apellido[indice]
								Escribir "Carrera: ", carrera[indice]
								Escribir "Semestre: ", semestre[indice]
								Escribir "Promedio: ", promedio[indice]
								Escribir "========================================"
								existencia <- Verdadero
							FinSi
						FinPara
						
						// Si no coincide, mostrar que no existe
						Si existencia = Falso Entonces
							Escribir "Aviso: La matrícula buscada no existe en los registros."
						FinSi
					FinSi
					
					// SALIR
				3:
					Escribir "Cerrando el sistema..."
					
				De Otro Modo:
					Escribir "Opción inválida. Intente nuevamente."
			FinSegun
			
			// Preguntar si se desea realizar otra acción
			Si menu_opciones <> 3 Entonces
				Escribir "¿Desea realizar otra acción? (S/N):"
				Leer respuesta_continuar
			FinSi
			
			// Si es 'S' regresa a la interfaz principal, si es 'N' o eligió 3, termina
		Hasta Que menu_opciones = 3 O Mayusculas(respuesta_continuar) = "N"
		
		// Finalizar el programa
		Escribir "Programa finalizado con éxito."
FinAlgoritmo
