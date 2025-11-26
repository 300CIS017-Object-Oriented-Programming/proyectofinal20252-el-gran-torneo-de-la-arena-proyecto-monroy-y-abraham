# BITÁCORA DE DESARROLLO - EL GRAN TORNEO DE LA ARENA

## Información del Proyecto
**Proyecto:** El Gran Torneo de la Arena - Paradise  
**Integrantes:** 
- Esteban-Monroy (anteriormente juanjosegda)
- abraham21587

**Curso:** Programación Orientada a Objetos  
**Período:** 2025-2B

---

## Tabla de Registro de Decisiones y Procesos

| **Fecha** | **Qué decidí** | **Por qué lo hice así** | **Responsable** |
|-----------|---|---|---|
| 20/11/2025 | Crear clase base `Personaje` abstracta | Para aplicar herencia y compartir atributos comunes entre todos los tipos de personajes (vida, ataque, defensa, experiencia) | Esteban |
| 21/11/2025 | Implementar subclases: Guerrero, Mago, Arquero | Cada tipo de personaje necesita comportamientos únicos en su método `atacar()`. Esto permite polimorfismo y evita duplicación de código | Esteban |
| 21/11/2025 | Crear estructura `Efecto` para buffs/debuffs temporales | En lugar de modificar directamente atributos, guardar efectos en un vector permite múltiples efectos simultáneos y revertilos automáticamente | abraham |
| 21/11/2025 | Implementar clase `Sanador` con habilidad de curar | Los support characters requieren mecánicas especiales diferentes. El Sanador puede gastar mana para curar a aliados durante combate | abraham |
| 21/11/2025 | Crear jerarquía de Objetos Mágicos (ObjetoGenerico → ObjetoMagico → subclases) | Permite que cada item tenga comportamiento único mediante polimorfismo, pero comparta interfaz común para uso genérico | Esteban |
| 22/11/2025 | Crear clase `Inventario` centralizada con `unordered_map` | Un inventario compartido facilita distribuir items, controlar cuáles están disponibles y implementar tienda. `unordered_map` da búsqueda O(1) por ID | abraham |
| 22/11/2025 | Implementar items mágicos: PocionVida, TomoConocimiento, TalismanVelocidad | Cada objeto tiene efecto único (restaurar vida, aumentar ataque temporalmente, etc.). Esto crea variedad en estrategia de equipo | abraham |
| 22/11/2025 | Implementar clase `Paladin` con atributos de defensa alta | Necesitábamos personaje tank que balanceara ofensa y defensa, permitiendo formaciones estratégicas | abraham |
| 22/11/2025 | Crear AmuletoFuria, ElixirSombrio, EscudoBendito, RunaProtectora | Ampliar opciones de objetos mágicos para que cada héroe tenga equipamiento único según su rol | abraham, Esteban |
| 23/11/2025 | Implementar clase `Arena` que orquesta combates por turnos | Centralizar lógica de combate separa responsabilidades: Guild gestiona recursos, Arena gestiona batallas | Esteban |
| 23/11/2025 | Diseñar flujo de turnos: héroes ataquen primero → enemigos contraatacan → actualizar efectos | El orden de turnos importa estratégicamente. Dar prioridad a héroes les da pequeña ventaja pero balanceada | Esteban |
| 23/11/2025 | Crear vector `registroCombate` para auditar cada acción | Registrar cada movimiento (quién atacó, cuánto daño, efectos aplicados) ayuda a debugging y permite reproducir combates | Esteban |
| 24/11/2025 | Implementar sistema de experiencia y subida de nivel | La progresión motiva a jugar múltiples combates. Al subir de nivel, personajes mejoran todos sus atributos proporcionalmente | abraham |
| 24/11/2025 | Implementar clase `ObjetoGenerico` como base para items | Permitir crear objetos simples y mágicos con interfaz común facilitó extensibilidad del sistema | Esteban |
| 24/11/2025 | Crear tienda en Guild donde comprar items con monedas | Un sistema económico donde victorias → monedas → items mejores → más poder crea ciclo motivador | abraham |
| 25/11/2025 | Implementar clase `Oponente` como enemigos con niveles | Necesitábamos enemigos con dificultad variable para escalar desafío según progresión del jugador | abraham |
| 25/11/2025 | Crear clase `Guild` que gestiona héroes, monedas y puntos | Centralizar datos de gremio: inventario de personajes, recursos económicos, estadísticas globales | abraham |
| 25/11/2025 | Conectar Guild + Arena + Inventario en `main.cpp` | Las tres clases deben trabajar juntas: Arena accede a héroes de Guild e items de Inventario | Esteban |
| 25/11/2025 | Crear menú principal interactivo en `main.cpp` | Permitir que jugador crear héroes, acceda a tienda, inicie combates e inspeccione estadísticas de forma sencilla | abraham |
| 25/11/2025 | Implementar `leerEntero()` con try-catch para validar entrada | C++ cin es propenso a errores. Manejo de excepciones previene crashes si usuario ingresa letras en lugar de números | abraham |
| 25/11/2025 | Crear función `limpiarPantalla()` para mejorar UX | Pequeños detalles como limpiar pantalla y mensajes claros mejoran significativamente la experiencia del usuario | abraham |
| 26/11/2025 | Implementar destructores completos en todas las clases | C++ requiere liberar memoria dinámicamente asignada. Destructores bien hechos previenen memory leaks que degradan performance | abraham |
| 26/11/2025 | Crear `registroCombate` detallado con cada acción | Logs detallados son invaluables para encontrar bugs de lógica. Permite auditar si daño y efectos se calculan correctamente | Esteban |

---

## Análisis Personal de Razonamiento por Miembro

### ESTEBAN-MONROY: Mi Proceso de Razonamiento Detallado

#### Entrada 1: Diseño de la Clase Base Personaje (20/11/2025)

| Aspecto | Descripción |
|---------|-----------|
| **Qué decidí** | Crear una clase abstracta `Personaje` que sirva como fundación para todas las subclases (Guerrero, Mago, Sanador, Paladin, Arquero). |
| **Por qué lo hice así** | Observé que todos los personajes necesitan atributos comunes: vida, ataque, defensa, experiencia, nombre, nivel. Si implementaba cada personaje por separado, tendría código duplicado. La herencia permite que todas compartan la implementación. |
| **Problema identificado** | Diferentes tipos de personajes comparten muchas características pero tienen comportamientos únicos de ataque. |
| **Análisis realizado** | Si uso herencia, puedo definir una vez los atributos compartidos y cada subclase solo implementa su propio `atacar()`. |
| **Decisión tomada** | Crear clase abstracta con método `atacar()` virtual puro, obligando a cada subclase a implementarlo. |
| **Beneficio obtenido** | Evité duplicación de 200+ líneas de código. Cuando necesito agregar un nuevo personaje, solo hago la subclase con su atacar() único. |
| **Alternativa considerada** | Usar composición en lugar de herencia, pero hubiera sido más complejo y lento en tiempo de desarrollo. |

---

#### Entrada 2: Arquitectura de Arena Separada de Guild (23/11/2025)

| Aspecto | Descripción |
|---------|-----------|
| **Qué decidí** | Implementar clase `Arena` completamente separada de `Guild`, donde Arena controla toda la lógica de combate. |
| **Por qué lo hice así** | Inicialmente pensé meter la lógica de combate dentro de Guild, pero rápidamente vi que se volvería inmanejable. Guild tiene 300+ líneas solo gestionar héroes y monedas. |
| **Problema identificado** | El principio de responsabilidad única (SRP) dice que cada clase debe tener una sola razón para cambiar. Guild = gestión de recursos. Arena = lógica de combate. |
| **Análisis realizado** | Separar en clases distintas permite que cada una sea mantenible, testeable y reutilizable sin efectos secundarios. |
| **Decisión tomada** | Crear Arena que reciba referencias a Guild e Inventario, pero mantenga su propia lógica independiente. |
| **Beneficio obtenido** | Ahora puedo tener múltiples tipos de combate (1v1, 2v2, torneo) sin modificar Guild. Código más modular y escalable. |
| **Conflicto resuelto** | Arena necesitaba acceder a héroes de Guild. Solucioné pasando referencias de punteros, no copiando datos. |

---

#### Entrada 3: Implementación de registroCombate para Debugging (26/11/2025)

| Aspecto | Descripción |
|---------|-----------|
| **Qué decidí** | Crear un vector `registroCombate` que captura CADA acción (quién atacó, daño, efectos, muertes) durante toda la batalla. |
| **Por qué lo hice así** | Durante testing encontré un bug donde el daño se calculaba incorrectamente en ciertos turnos. Sin logs, era imposible saber qué sucedía. |
| **Problema enfrentado** | Bug misterioso: a veces el daño era 0, a veces correcto, parecía aleatorio y no podía reproducirlo. |
| **Análisis realizado** | Sin visibilidad de cada turno, no podía reproducir el problema. Necesitaba saber exactamente qué pasó en cada paso del combate. |
| **Decisión tomada** | Cada acción registra string con formato: "Guerrero atacó Enemigo por 25 daño" → almacenar en vector `registroCombate`. |
| **Resultado obtenido** | Reproduje el bug: efectos temporales se aplicaban dos veces. Lo identifiqué y corregí completamente. |
| **Aprendizaje clave** | Los logs detallados ahorran horas de debugging. Es tan importante como el código mismo. Sin visibility no hay debugging posible. |

---

#### Entrada 4: Diseño del Sistema de Efectos Temporales (22/11/2025)

| Aspecto | Descripción |
|---------|-----------|
| **Qué decidí** | Crear estructura `Efecto` que guarda buffs/debuffs como objetos separados en vector, en lugar de modificar directamente atributos. |
| **Por qué lo hice así** | Colaboré con abraham para resolver este problema. Inicialmente pensé: "¿Por qué no solo incrementar `ataque` directamente?" Pero vimos que causaría problemas críticos. |
| **Problema identificado** | Si hay 3 efectos simultáneos (ataque+10, defensa+5, ataque-2), y uno expira, ¿cómo sé cuál revertir sin dañar los otros? |
| **Análisis realizado** | Guardar efectos como objetos con duraciones permite revertilos automáticamente cuando expire el turno sin ambigüedad. |
| **Decisión tomada** | Crear estructura `Efecto {tipo, valor, turnosRestantes}` y vector `efectosActivos` en clase `Personaje`. |
| **Implementación** | Cada turno, itero efectos, decremento turnosRestantes. Si llega a 0, lo remuevo del vector automáticamente. |
| **Beneficio obtenido** | Código limpio, manejo de múltiples efectos simultáneos sin conflictos, fácil de debuggear, escalable. |

---

### ABRAHAM21587: Mi Proceso de Razonamiento Detallado

#### Entrada 1: Uso de unordered_map en Inventario (22/11/2025)

| Aspecto | Descripción |
|---------|-----------|
| **Qué decidí** | Implementar Inventario usando `unordered_map<string, ObjetoMagico*>` en lugar de `vector<ObjetoMagico*>`. |
| **Por qué lo hice así** | Estudié complejidad de algoritmos y vi que si tengo 50+ items y busco por ID, vector es O(n) lento. unordered_map es O(1) instantáneo. |
| **Problema enfrentado** | Necesitaba búsqueda rápida de items por ID ("amuleto_furia_1", "pocion_vida_5") en cada distribución de combate. |
| **Opciones consideradas** | (1) vector + búsqueda lineal = O(n), (2) unordered_map = O(1), (3) map ordenado = O(log n). |
| **Análisis cuantitativo** | En juego con 50 items, hacer 100 búsquedas por turno: Vector: 100×50 = 5000 ops | unordered_map: 100×1 = 100 ops = 50x más rápido. |
| **Decisión tomada** | unordered_map, porque velocidad de búsqueda es crítica en combates frecuentes donde se distribuyen items. |
| **Código implementado** | `unordered_map<string, ObjetoMagico*> items;` + método `ObjetoMagico* buscar(string id) { return items[id]; }` |
| **Beneficio obtenido** | Escalabilidad garantizada. Si futuro agrego 500 items, sigue siendo O(1). Vector escalaría a O(500). |

---

#### Entrada 2: Implementación de leerEntero() Robusta (25/11/2025)

| Aspecto | Descripción |
|---------|-----------|
| **Qué decidí** | Crear función `leerEntero()` que maneja excepciones cuando usuario ingresa datos inválidos. |
| **Por qué lo hice así** | Probé el programa con usuarios reales (mi familia) y vieron que si ingresaban letras, el programa fallaba silenciosamente. |
| **Problema enfrentado** | C++ cin es inseguro. Si espero int y recibo "abc", entra en estado de error y el programa se congela o behaves strangely. |
| **Escenario testado** | Yo: "Ingresa número de opción (1-5)" | Usuario: "hola" (typo accidental) | Resultado: Programa congelado o loop infinito. |
| **Análisis realizado** | Necesitaba capturar entrada inválida y mostrar error claro pidiendo reintento, no fallar silenciosamente. |
| **Decisión tomada** | Usar try-catch con `stoi()` que lanza excepción si conversión falla + validación de entrada vacía. |
| **Código implementado** | `try { return stoi(entrada); } catch(...) { cout << "Error: ingresa número válido"; return -1; }` |
| **Beneficio obtenido** | Experiencia de usuario 10x mejor. Menú es robusto, amigable, intuitivo. Usuarios no se frustran con crashes. |

---

#### Entrada 3: Sistema Económico de Tienda (25/11/2025)

| Aspecto | Descripción |
|---------|-----------|
| **Qué decidí** | Crear sistema donde victorias = monedas = items = poder (loop económico motivador). |
| **Por qué lo hice así** | Jugué RPGs como Pokémon, Zelda, Final Fantasy. Todos tienen este loop: pelear → ganar → comprar → mejorar → pelear más fácil. |
| **Problema identificado** | Sin sistema de progresión económica, ¿por qué un jugador se esforzaría en combates? Sin motivación abandona rápidamente. |
| **Análisis de gamedesign** | Sin motivación → usuario aburre en turno 2. Con motivación → usuario juega 20+ turnos queriendo items mejores. |
| **Decisión tomada** | Implementar loop: Victoria → +50 monedas → Tienda ofrece items → Compra AmuletoFuria (+10 ataque) → Próximo combate más fácil. |
| **Código implementado** | Arena.cpp: `if(todosHeroesVivos()) gremio->incrementarMonedas(50);` + Guild.cpp: `tiendaObjetos()` + Validación de fondos. |
| **Efecto acumulativo** | Nivel 1 ganas 50 monedas, compras armadura → Nivel 2 ganas más fácil → Espiral ascendente adictiva. |
| **Beneficio obtenido** | Jugabilidad adictiva. Usuarios quieren seguir jugando, sienten progresión, no se aburren rápidamente. |

---

#### Entrada 4: Arquitectura de Clases de Objetos Mágicos (22-24/11/2025)

| Aspecto | Descripción |
|---------|-----------|
| **Qué decidí** | Crear jerarquía: ObjetoGenerico → ObjetoMagico → Subclases concretas (PocionVida, AmuletoFuria, ElixirSombrio, etc.) |
| **Por qué lo hice así** | Necesitaba que cada item tuviera efecto único pero interfaz común. Colaboré con Esteban en diseño arquitectónico. |
| **Problema enfrentado** | 8 tipos de items diferentes. Cada uno hace algo diferente. ¿Cómo implemento esto sin code duplication ni switch-case gigante? |
| **Opciones consideradas** | Opción 1: Switch-case gigante (malo, modificar código base cada item nuevo). Opción 2: Polimorfismo (cada hereda, sobrescribe aplicarEfecto). |
| **Análisis realizado** | Switch-case viola Open/Closed Principle. Si agrego item 9, modifico Arena/Guild. Polimorfismo = extensible sin modificaciones. |
| **Decisión tomada** | Jerarquía polimórfica donde cada item hereda de `ObjetoMagico` y sobrescribe `aplicarEfecto(Personaje*)`. |
| **Código implementado** | `class PocionVida : public ObjetoMagico { void aplicarEfecto(Personaje* p) override { p->restaurarVida(50); } }` |
| **Ventaja principal** | Arena hace `item->aplicarEfecto(heroe)` sin saber tipo específico. Polimorfismo lo resuelve en runtime. |
| **Extensibilidad futura** | Si agrego "Espada Legendaria", creo clase nueva que hereda. Cero cambios a Arena o Guild. |
| **Aprendizaje clave** | Polimorfismo es poder. Permite extensibilidad sin modificar código existente (Open/Closed Principle de SOLID). |

---

---

### ABRAHAM21587: Mi Proceso de Razonamiento Detallado

#### Entrada 1: Uso de unordered_map en Inventario (22/11/2025)

**Qué decidí:** Implementar Inventario usando `unordered_map<string, ObjetoMagico*>` en lugar de `vector<ObjetoMagico*>`.

**Por qué lo hice así:** Estudié complejidad de algoritmos y vi que si tengo 50+ items y busco por ID, vector es O(n) lento. unordered_map es O(1) instantáneo.

**Mi proceso de razonamiento completo:**
- **Problema enfrentado:** Necesitaba búsqueda rápida de items por ID ("amuleto_furia_1", "pocion_vida_5").
- **Opciones consideradas:** (1) vector + búsqueda lineal = O(n), (2) unordered_map = O(1), (3) map ordenado = O(log n).
- **Análisis:** En un juego con 50 items, hacer 100 búsquedas por turno:
  - Vector: 100 × 50 = 5000 operaciones
  - unordered_map: 100 × 1 = 100 operaciones
  - Diferencia: 50x más rápido
- **Decisión tomada:** unordered_map, porque velocidad de búsqueda es crítica en combates frecuentes.
- **Implementación:** 
  ```cpp
  unordered_map<string, ObjetoMagico*> items;
  ObjetoMagico* buscar(string id) { return items[id]; } // O(1)
  ```
- **Beneficio:** Escalabilidad. Si en futuro agregamos 500 items, sigue siendo O(1).

---

#### Entrada 2: Implementación de leerEntero() Robusta (25/11/2025)

**Qué decidí:** Crear función `leerEntero()` que maneja excepciones cuando usuario ingresa datos inválidos.

**Por qué lo hice así:** Probé el programa con usuarios reales (mi familia) y vieron que si ingresaban letras, el programa fallaba silenciosamente.

**Mi proceso de razonamiento completo:**
- **Problema enfrentado:** cin de C++ es inseguro. Si espero un int y recibo "abc", entra en estado de error.
- **Escenario testado:** 
  - Yo: "Ingresa número de opción"
  - Usuario: "hola" (typo)
  - Resultado: Programa congelado o comportamiento extraño
- **Análisis:** Necesitaba capturar esto y mostrar error claro.
- **Decisión tomada:** Usar try-catch con stoi() que lanza excepción si conversión falla.
  ```cpp
  int leerEntero() {
    string entrada;
    getline(cin, entrada);
    if (entrada.empty()) continue; // Usuario presionó Enter vacío
    try {
      return stoi(entrada); // Convierte string a int
    } catch (...) {
      cout << "Error: ingresa un número válido\n";
      return -1; // Indica error
    }
  }
  ```
- **Beneficio:** Experiencia de usuario 10x mejor. Menú es robusto y amigable.

---

#### Entrada 3: Sistema Económico de Tienda (25/11/2025)

**Qué decidí:** Crear sistema donde victorias = monedas = items = poder (loop económico).

**Por qué lo hice así:** Jugué RPGs como Pokémon, Zelda, Final Fantasy. Todos tienen este loop: pelear → ganar → comprar → mejorar → pelear más fácil.

**Mi proceso de razonamiento completo:**
- **Observación:** Sin sistema de progresión económica, ¿por qué un jugador se esforzaría en combates?
- **Análisis de gamedesign:** 
  - Sin motivación → usuario aburre en turno 2
  - Con motivación → usuario juega 20 turnos queriendo items
- **Decisión tomada:** Implementar loop: Victoria → +50 monedas → Tienda ofrece items → Compra AmuletoFuria (+10 ataque) → Próximo combate gana más fácil.
- **Implementación:**
  - Arena.cpp: `if (gremio->todosHeroesVivos()) gremio->incrementarMonedas(50);`
  - Guild.cpp: Función tiendaObjetos() donde compras con monedas
  - Efecto acumulativo: Nivel 1 ganas 50, compras armadura → Nivel 2 ganas más fácil → spiral ascendente
- **Beneficio:** Jugabilidad adictiva. Usuarios quieren seguir jugando.

---

#### Entrada 4: Arquitectura de Clases de Objetos Mágicos (22-24/11/2025)

**Qué decidí:** Crear jerarquía: ObjetoGenerico → ObjetoMagico → Subclases concretas (PocionVida, AmuletoFuria, ElixirSombrio, etc.)

**Por qué lo hice así:** Necesitaba que cada item tuviera efecto único pero interfaz común. Colaboré con Esteban en diseño.

**Mi proceso de razonamiento completo:**
- **Problema:** 8 tipos de items diferentes (PocionVida, CristalMagico, AmuletoFuria, ElixirSombrio, EscudoBendito, RunaProtectora, TalismanVelocidad, TomoConocimiento). Cada uno hace algo diferente.
- **Análisis de opciones:**
  - Opción 1: Switch-case gigante. Malo. Si agrego item 9, modifico código base.
  - Opción 2: Polimorfismo. Cada item hereda de base y sobrescribe aplicarEfecto().
- **Decisión tomada:** Jerarquía polimórfica.
  ```cpp
  class ObjetoMagico {
    virtual void aplicarEfecto(Personaje* p) = 0; // Virtual puro
  };
  class PocionVida : public ObjetoMagico {
    void aplicarEfecto(Personaje* p) override { p->restaurarVida(50); }
  };
  class AmuletoFuria : public ObjetoMagico {
    void aplicarEfecto(Personaje* p) override { p->agregarEfecto("ataque", +15, 3); }
  };
  ```
- **Ventaja:** Arena puede hacer `item->aplicarEfecto(heroe)` sin saber el tipo específico.
- **Extensibilidad:** Si en futuro agrego "Espada Legendaria", solo creo clase nueva que hereda de ObjetoMagico. Cero cambios a Arena o Guild.
- **Aprendizaje:** Polimorfismo es poder. Permite extensibilidad sin modificar código existente (Principio Open/Closed).

---

## Notas Importantes

Los commits iniciales bajo usuario "juanjosegda" corresponden al trabajo de **Esteban-Monroy**. Hubo discrepancia en la configuración de Git que fue corregida posteriormente, ahora apareciendo bajo su usuario correcto.

## Reflexión Final del Equipo

Este proyecto nos permitió aplicar conceptos avanzados de POO (herencia, polimorfismo, encapsulación) en un contexto práctico. El desafío principal fue mantener el código limpio y extensible mientras agregábamos características iterativamente.

**Lecciones aprendidas:**
- La separación de responsabilidades (Guild ≠ Arena) es crítica para mantenibilidad
- Usar estructuras de datos adecuadas (unordered_map vs vector) impacta rendimiento
- Registrar acciones durante ejecución facilita debugging exponencialmente
- La colaboración y comunicación previene conflictos de merge
- Pequeños detalles de UX mejoran mucho la percepción del programa
