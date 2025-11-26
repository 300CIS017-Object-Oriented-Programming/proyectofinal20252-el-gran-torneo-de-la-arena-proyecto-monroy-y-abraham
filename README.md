# El Gran Torneo de la Arena

## Presentación general

**El Gran Torneo de la Arena** es un simulador de combates por turnos donde el jugador crea un equipo de héroes especializados, los entrena ganando experiencia, compra equipamiento mágico y los enfrenta contra enemigos en batallas dentro de una arena.

El sistema gestiona automáticamente:

- La creación y administración de héroes.
- La distribución y uso de objetos mágicos.
- El cálculo de daño y defensa.
- Los efectos especiales temporales.
- La progresión de personajes mediante experiencia y niveles.

El proyecto simula lo esencial de un RPG por turnos sencillo pero funcional:  
crear personajes con diferentes roles, equiparlos, llevarlos a combatir, resolver los turnos y determinar al equipo ganador.

---

## Integrantes

- **Esteban Monroy**
- **Abraham Waggon**

---

## ¿Qué hace el programa?

1. **Creación y gestión de héroes**

   El jugador cuenta con diferentes roles de héroes, cada uno con fortalezas y mecánicas propias:

   - **Guerrero**: ataque físico fuerte y defensa equilibrada.
   - **Mago**: alto daño mágico, menor vida, gestión de energía.
   - **Sanador**: se especializa en curar a sus aliados y mantener al equipo con vida.
   - **Paladín**: alta defensa, puede curarse y mejorar sus estadísticas temporalmente.
   - **Arquero**: daño a distancia, buena precisión y habilidades especiales con flechas.

2. **Sistema de gremio (Guild)**

   Todos los héroes pertenecen a un gremio.  
   El gremio administra:

   - La lista de héroes disponibles.
   - Las **monedas** del jugador.
   - Los **puntos** ganados por victorias.
   - La tienda de héroes (para comprar nuevos personajes).

3. **Inventario mágico**

   Existe un inventario global con **objetos mágicos** que alteran los atributos de los personajes.  
   Algunos ejemplos:

   - **Poción de Vida**
   - **Cristal Mágico**
   - **Amuleto de Furia**
   - **Escudo Bendito**
   - **Talisman de Velocidad**
   - **Runa Protectora**
   - **Tomo de Conocimiento**
   - **Elixir Sombrío**
   - Además de **objetos genéricos** configurables (ObjetoGenerico).

   Desde el menú se pueden ver los objetos, equiparlos a héroes y usarlos durante los combates.

4. **Combates por turnos en la Arena**

   En la Arena, el equipo del jugador se enfrenta a un grupo de oponentes generados según una dificultad elegida.  
   En cada turno se realiza:

   - Turno de los héroes (el jugador decide acciones).
   - Turno de los enemigos (IA decide atacar o usar objetos).
   - Actualización de efectos temporales (buffs, curaciones, etc.).
   - Verificación de vida para determinar si alguien muere.

   Al finalizar la pelea se determina el equipo ganador y se otorgan recompensas.

5. **Sistema de experiencia y nivel**

   Tras cada victoria los personajes ganan **experiencia (XP)**.  
   Cuando alcanzan la experiencia necesaria:

   - Suben de nivel.
   - Aumentan sus estadísticas: vida máxima, ataque y defensa.
   - Se reinicia su barra de XP para el siguiente nivel.

6. **Menú interactivo**

   El programa cuenta con un **menú principal** por consola desde donde se puede:

   - Gestionar héroes.
   - Revisar y administrar el inventario.
   - Entrar a la tienda de héroes.
   - Entrar a la tienda de objetos mágicos.
   - Ir a la Arena a combatir.
   - Ver estadísticas globales del gremio.
   - Salir del juego.

---

## Diagrama de clases UML

![Diagrama UML](img.png)

- Primer UML donde se define de manera básica la idea puntual del desarrollo del proyecto:  
  se muestran las clases principales (`Personaje`, sus subclases, `Guild`, `Inventario`, `Arena`, `ObjetoMagico`, etc.) y sus relaciones.

---

## Imágenes del proyecto funcionando

A continuación se muestran capturas de pantalla del programa en ejecución:

![img_1.png](img_1.png)
- **Menú principal del juego.**

---

![img_2.png](img_2.png)
- **Opción 1: “Gestionar héroes”**, donde se muestran las diferentes funciones disponibles.

---

![img_3.png](img_3.png)
- **Ver lista de héroes:** se muestran los héroes registrados en la Guild  
  (inicialmente hay héroes predeterminados).

---

![img_4.png](img_4.png)
- **Ver detalles de un héroe:** al ingresar el ID (por ejemplo `heroe_1`) se visualizan
  sus datos: nivel, HP, experiencia, ataque y defensa.

---

![img_5.png](img_5.png)
- **Despedir héroe:** elimina al héroe de la lista y de la Guild.  
  La opción “Volver” regresa al menú principal.

---

![img_6.png](img_6.png)
- **Opción 2: Inventario.**  
  Permite ver los objetos disponibles, equiparlos a héroes y regresar al menú principal.

---

![img_7.png](img_7.png)
- **Opción 3: Tienda de héroes.**  
  Usa el sistema de monedas: al iniciar el jugador tiene una cantidad base
  (por ejemplo 300 monedas) que puede gastar para comprar nuevos héroes.

---

![img_8.png](img_8.png)
- **Opción 4: Tienda de objetos.**  
  Permite comprar objetos mágicos o crear nuevos (dependiendo de los puntos y monedas
  disponibles).

---

![img_9.png](img_9.png)  
![img_10.png](img_10.png)  
![img_11.png](img_11.png)  
![img_12.png](img_12.png)  
![img_13.png](img_13.png)  
![img_14.png](img_14.png)

- **Opción 5: Ir a la Arena (pelear).**  
  Muestra los héroes listos, genera a los oponentes según la dificultad elegida, presenta
  a los enemigos con sus características y permite:

   - Escoger si los objetos se reparten automáticamente o manualmente.
   - Equipar objetos a héroes específicos.
   - Iniciar el sistema de turnos de combate.

---

![img_15.png](img_15.png)
- **Opción 6: Estadísticas.**  
  Muestra la información global de la Guild: número de victorias, monedas acumuladas,
  puntos, etc.

---

![img_16.png](img_16.png)
- Dependiendo de la versión del menú, las opciones finales pueden incluir:
   - Guardar partida.
   - Cargar partida.
   - Salir del juego.

---

## Cómo funciona técnicamente

El código está organizado en módulos claros:

- **`Personaje.h / Personaje.cpp`**  
  Clase base que define las propiedades y comportamientos comunes de todos los personajes:
  vida, vida máxima, ataque, defensa, experiencia, nivel, uso de objetos y gestión de efectos.

- **Subclases de Personaje:**
   - `Guerrero`
   - `Mago`
   - `Sanador`
   - `Paladin`
   - `Arquero`

  Cada uno redefine su forma de atacar y, en algunos casos, añade recursos propios
  (furia, energía, mana, estamina, etc.).

- **`Guild.h / Guild.cpp`**  
  Administra la colección de héroes, las monedas, los puntos y la lógica de la tienda de héroes.

- **`Arena.h / Arena.cpp`**  
  Gestiona:
   - La generación de enemigos según dificultad.
   - La preparación del combate (equipamiento de objetos).
   - El ciclo de turnos (héroes y enemigos).
   - La lógica de IA de los oponentes.
   - El cálculo de recompensas y experiencia al finalizar el combate.

- **`Inventario.h / Inventario.cpp`**  
  Contiene todos los objetos mágicos disponibles, su stock y las funciones para listarlos,
  asignarlos a héroes y actualizar existencias.

- **Objetos mágicos**  
  Clases como `PocionVida`, `AmuletoFuria`, `EscudoBendito`, `TalismanVelocidad`,
  `CristalMagico`, `TomoConocimiento`, `ElixirSombrio`, `RunaProtectora` y `ObjetoGenerico`
  heredan de `ObjetoMagico` y definen diferentes tipos de efectos (curación, aumento de ataque,
  aumento de defensa, etc.).

- **`main.cpp`**  
  Punto de entrada del programa.  
  Implementa el menú principal y conecta todas las piezas: Guild, Inventario y Arena.

---

## Conceptos de POO utilizados

- **Herencia:**
   - `Guerrero`, `Mago`, `Sanador`, `Paladin` y `Arquero` heredan de `Personaje`.
   - Los distintos ítems heredan de `ObjetoMagico`.

- **Polimorfismo:**
   - Cada personaje implementa su versión específica de `atacar()`.
   - Cada objeto mágico aplica su propio efecto al usarse.

- **Encapsulación:**
   - Los atributos se mantienen privados y se accede a través de métodos públicos o protegidos.

- **Punteros y memoria dinámica:**
   - Se crean y administran héroes, enemigos y objetos mediante punteros.

- **Estructuras de datos STL:**
   - `std::vector` para listas de personajes/enemigos/objetos.
   - `std::unordered_map` (o `std::map`) para almacenar y buscar objetos por nombre.

---
