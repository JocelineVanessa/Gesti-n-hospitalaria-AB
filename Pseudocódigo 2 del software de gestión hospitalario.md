**Pseudocódigo 2 del software de gestión hospitalario** 

#### **Clase Usuario**

Atributos:  
\- NombreUsuario: Nombre del usuario (String).  
\- Contraseña: Contraseña del usuario (String).  
\- Rol: Rol del usuario (ADMINISTRADOR, MÉDICO, RECEPCIONISTA) (String).  
\- Permisos: Lista de permisos del usuario (Lista de booleanos).

**Funciones:**  
\- AsignarPermisosPorRol(): Asigna permisos al usuario por rol.  
\- VerificarPermiso(permiso): Verifica si el usuario tiene permisos específicos.  
\- ValidarContraseña(inputContraseña): Valida la contraseña ingresada.  
\- GuardarUsuarios(usuarios, archivo): Guarda la lista de usuarios en un Csv.  
\- CargarUsuarios(usuarios, archivo): Carga la lista de usuarios desde un Csv.  
\- CrearUsuario(usuarios): Crea un nuevo usuario y lo agrega a la lista.  
\- MostrarUsuarios(usuarios): Muestra la lista de usuarios y sus permisos.

**Clase Paciente**  
    Atributos:  
\- Nombre: Nombre completo del paciente (String)  
       \- ID: DNI del paciente (String)  
       \- FechaIngreso: Fecha de ingreso del paciente (String)  
       \- HistorialClinico: Historial médico del paciente (String)

    **Funciones:**  
        \- RegistrarPaciente(): Permite ingresar los datos de un nuevo paciente.  
        \- EliminarPaciente(): Elimina un paciente de los registros.  
        \- BuscarPaciente(criterio): Realiza una búsqueda por nombre, ID o fecha de ingreso.  
        \- AgregarHistorial(historia): Añade registros al historial clínico del paciente.

**Clase Médico**  
    Atributos:  
         \- Nombre: Nombre completo del médico (String)  
         \- ID: DNI del médico (String)  
         \- Especialidad: Especialidad médica del doctor (String)  
\- FechaNacimiento: Fecha de nacimiento del médico (día, mes, año \- String).  
\- Correo: Correo electrónico del médico (String).  
\- Telefono: Teléfono del médico (String).  
\- Edad: Edad calculada del médico (Entero)

    **Funciones:**  
        \- RegistrarMedico(): Permite registrar un nuevo médico.  
        \- CalcularEdad(diaNacimiento, mesNacimiento, añoNacimiento): Calcula la edad del utilizando la fecha de nacimiento y la fecha actual.  
        \- EliminarMedico(): Elimina un médico de los registros.  
        \- ListaMedicosPorEspecialidad(): Lista de médicos.

**Clase Cita**  
    Atributos:  
        \- IDPaciente: Identificación del paciente asociado (String)  
        \- IDMedico: Identificación del médico asignado (String)  
        \- Fecha: Fecha de la cita (String)  
        \- Urgencia: Nivel de urgencia de la cita (String)

    **Funciones:**  
        \- CrearCita(): Crea una nueva cita.  
        \- ModificarCita(): Modifica una cita existente.  
        \- EliminarCita(): Elimina una cita existente.  
        \- OrdenarCitasPorFecha(): Ordena citas por fecha o urgencia.

**Clase Archivo**  
    Atributos:  
        \- ArchivoPacientes: Archivo de almacenamiento de pacientes (String)  
        \- ArchivoMedicos: Archivo de almacenamiento de médicos (String)  
        \- ArchivoCitas: Archivo de almacenamiento de citas (String)  
        \- ArchivoBackup: Archivo de backup para copia de seguridad (String)

    **Funciones:**  
        \- GuardarPaciente(paciente): Guarda los datos de un paciente en archivo.  
        \- GuardarMedico(medico): Guarda los datos de un médico en archivo.  
        \- GuardarCita(cita): Guarda los datos de una cita en archivo.  
        \- RealizarBackup(): Crea una copia de seguridad de todos los archivos de datos.

**Clase Reporte**  
    Atributos:  
        \- RangoFechas: Intervalo de fechas para el reporte (String)  
        \- PacientesAtendidos: Lista de pacientes atendidos en el rango de fecha establecido(Lista)  
        \- CitasPendientes: Citas médicas pendientes por especialidad o médico (Lista)

    **Funciones:**  
        \- ReportePacientesAtendidos():Crea un reporte de los pacientes atendidos en el rango.  
        \- ReporteCitasPendientes(): Crea un reporte de citas pendientes.