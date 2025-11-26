# BITACORA DE DESARROLLO – El Gran Torneo de la Arena
Curso: Programacion Orientada a Objetos (2025-2B)

## Integrantes
- **Esteban-Monroy** – Logica de Combate y Clases
- **abraham21587** – Items, Tienda y Demas

---

# TABLA DE REGISTRO DE DECISIONES

| Fecha | Decision | Motivo | Responsable |
|-------|----------|--------|-------------|
| 20/11 | Crear clase Personaje (padre) | Para no repetir vida, ataque, defensa en cada heroe | Esteban |
| 21/11 | Agregar Nivel y XP | Para que los personajes puedan mejorar | Abraham |
| 21/11 | Crear Sanador | Necesitabamos un personaje que cure, con mana | Esteban |
| 21/11 | Crear ObjetoMagico | Para tener objetos unificados en el inventario | Abraham |
| 21/11 | Merge de ramas | Hubo conflictos y tocó resolverlos a mano | Esteban |
| 21/11 | Limitar curacion del Sanador | Curaba demasiado, ahora escala con nivel | Esteban |
| 21/11 | Restaurar codigo perdido | En el merge se borraron lineas por error | Abraham |
| 21/11 | Crear Arquero | Para variedad y uso de flechas limitadas | Esteban |
| 21/11 | Crear PocionVida | Primer objeto funcional del inventario | Abraham |
| 21/11 | Crear CristalMagico | Para recuperar energia/mana | Abraham |
| 21/11 | Crear Guerrero y Mago | Roles clasicos del combate | Esteban |
| 22/11 | Crear TomoConocimiento | Objeto que sube stats permanentes | Abraham |
| 22/11 | Ajustar Talisman | Era complejo el efecto de turnos extra | Abraham |
| 22/11 | Crear Paladin | Tanque del equipo | Abraham |
| 22/11 | Arreglar conflicto en Sanador.h | Los dos editamos el mismo archivo | Esteban |
| 22/11 | Crear AmuletoFuria | Objeto pensado para el Guerrero | Abraham |
| 22/11 | Crear ElixirSombrio | Objeto ofensivo con costo en vida | Abraham |
| 22/11 | Crear RunaProtectora | Primer buff de defensa | Esteban |
| 23/11 | Crear EscudoBendito | Mas opciones para la tienda | Abraham |
| 24/11 | Crear ObjetoGenerico | Habia demasiados .cpp para objetos simples | Abraham |
| 24/11 | Programar ObjetoGenerico | Switch interno para determinar efecto | Esteban |
| 25/11 | Crear Oponente con IA basica | Para que los enemigos tomen decisiones | Abraham |
| 25/11 | Crear clase Guild | Para separar tienda, heroes y gestion | Abraham |
| 25/11 | Limpiar codigo del Guerrero | Habia cosas static innecesarias | Abraham |
| 25/11 | Arreglar Paladin | Su defensa no funcionaba | Abraham |
| 25/11 | Arreglar Sanador | No funcionaba con nuevos items | Abraham |
| 25/11 | Crear clase Arena | Separamos la pelea de Guild | Abraham |
| 25/11 | Enemigos aleatorios | Para evitar peleas repetidas | Abraham |
| 25/11 | Programar combate en Arena.cpp | Logica de turnos en while | Esteban |
| 25/11 | Sacar Inventario a clase aparte | Guild estaba muy grande | Abraham |
| 25/11 | Usar unordered_map en Inventario | Mas rapido que buscar en vectores | Esteban |
| 25/11 | Corregir nombre del main | Tenia un espacio y no compilaba | Abraham |
| 25/11 | Juntar todo en main.cpp | Menu principal funcional | Abraham |
| 26/11 | Poner logs de combate | Para encontrar errores de daño negativo | Esteban |
| 26/11 | Arreglos finales | Pruebas completas antes de entregar | Abraham |
| 26/11 | Subir proyecto final | Codigo definitivo y funcional | Abraham |
| 26/11 | Hacer documentacion | Se crea README y esta bitacora | Esteban |

---

# ANALISIS DE PROCESO (RESUMIDO)

## Esteban-Monroy
### Arquitectura de clases
Hice la clase padre Personaje para evitar codigo repetido y usar polimorfismo.

### Separar Arena
Guild estaba mezclando tienda y combate. Dividirlo facilito debug y orden.

### Logs de combate
Habia daño negativo. Con cout identifiqué errores y los corregi.

---

## abraham21587
### Objeto Generico
Habia demasiados .cpp para cada objeto. Unifique todo en uno y borramos archivos innecesarios.

### Manejo del input
Si escribian letras, el programa se trababa. Agregue validacion para evitar loops infinitos.

### Oro y Tienda
Peleas sin recompensa eran aburridas. Añadí monedas y tienda para mejorar progresion.

---

