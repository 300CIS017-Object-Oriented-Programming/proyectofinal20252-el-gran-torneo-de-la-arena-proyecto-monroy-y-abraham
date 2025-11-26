

# El Gran Torneo de la Arena

## Presentación General

**"El Gran Torneo de la Arena"** es un simulador de combates por turnos donde el jugador crea un equipo de héroes especializados, los entrena ganando experiencia, compra equipamiento mágico, y los enfrenta contra enemigos en emocionantes batallas. El sistema gestiona todo automáticamente: desde la distribución de objetos mágicos hasta el cálculo de daño, efectos especiales y progresión de personajes.

El proyecto simula todo lo que sucede en un RPG por turnos simple pero funcional: crear personajes con diferentes roles (Guerrero, Mago, Sanador, Paladín, Arquero), equiparlos con objetos mágicos que modifican sus atributos, y llevarlos a combatir contra enemigos en una arena. Durante cada combate, el sistema controla los turnos, calcula quién ataca a quién, aplica efectos temporales, y determina al ganador.

## Integrantes

- **Esteban Monroy**
- **Abraham Waggon**

## ¿Qué hace el programa?

1. **Creación de Héroes:** El jugador puede crear héroes con diferentes roles. Cada rol tiene fortalezas únicas:
   - **Guerrero:** Ataque poderoso y defensa equilibrada
   - **Mago:** Ataque mágico especial pero con menos vida
   - **Sanador:** Puede curar a sus aliados durante el combate
   - **Paladín:** Defensa alta y ataque equilibrado
   - **Arquero:** Ataque rápido con múltiples disparos

2. **Sistema de Gremio:** Los héroes pertenecen a un gremio que gestiona monedas y puntos. Cada victoria en combate otorga monedas para comprar mejoras.

3. **Inventario Mágico:** Existe una tienda con objetos mágicos que modifican los atributos de los personajes. Hay pociones de vida, cristales de poder, amuletos de furia, elixires, escudos benditos, runas protectoras, talismanes de velocidad y tomos de conocimiento.

4. **Combates por Turnos:** Los héroes se enfrentan contra enemigos en duelos por turnos. En cada turno:
   - Los héroes atacan primero
   - Los enemigos contraatacan
   - Se actualizan los efectos temporales 
   - Se verifica si alguien muere

5. **Sistema de Experiencia:** Cada victoria otorga experiencia. Cuando acumulan suficiente, los personajes suben de nivel y mejoran sus atributos.

6. **Menú Interactivo:** El programa tiene un menú fácil de usar donde puedes crear héroes, acceder a la tienda, iniciar combates y ver estadísticas de tus personajes.

## Diagrama de Clases UML




## Imágenes del Proyecto Funcionando

A continuación se muestran capturas de pantalla del programa en ejecución:


## Cómo Funciona Técnicamente

El código está organizado en módulos claros:

- **Personaje.h/cpp:** Clase base abstracta que define qué es un personaje (vida, ataque, defensa, experiencia).
- **Subclases de Personaje:** Guerrero, Mago, Sanador, Paladín, Arquero, cada uno con su propio método `atacar()` especializado.
- **Guild.h/cpp:** Gestiona el equipo de héroes, monedas, puntos y la tienda donde comprar objetos.
- **Arena.h/cpp:** Controla los combates. Maneja los turnos, calcula daño, aplica efectos y determina ganadores.
- **Inventario.h/cpp:** Gestiona todos los objetos mágicos disponibles en el juego.
- **Objetos Mágicos:** Diferentes clases para cada tipo de objeto (PocionVida, CristalMagico, AmuletoFuria, etc.), todos heredan de ObjetoMagico.
- **main.cpp:** Menú principal del programa donde el jugador interactúa con el sistema.

### Conceptos de POO Utilizados

- **Herencia:** Los personajes heredan de una clase base Personaje. Los objetos mágicos heredan de ObjetoMagico.
- **Polimorfismo:** Cada personaje implementa su propio método `atacar()` de forma diferente. Cada objeto tiene su propio `aplicarEfecto()`.
- **Encapsulación:** Los atributos de cada clase son privados, se accede a través de métodos públicos.
- **Punteros:** Se usan punteros para manejar dinámicamente héroes, objetos y enemigos.
- **Estructuras de Datos STL:** Se usan `vector` para listas y `unordered_map` para búsquedas rápidas.







