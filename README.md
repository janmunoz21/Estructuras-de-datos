Repositorio de Jan Marco Muñoz para la clase de Estructuras de datos

'''mermaid
classDiagram
    class Arista {
        -Vertice vertice1
        -Vertice vertice2
        +Arista()
        +Arista(Vertice v1, Vertice v2)
        +Vertice getVertice1()
        +Vertice getVertice2()
        +void setVertice1(Vertice v)
        +void setVertice2(Vertice v)
    }
    
    class Cara {
        -deque~Vertice~ vertices
        -deque~Arista~ aristas
        +Cara()
        +deque~Vertice~ getVertices()
        +deque~Arista~ getAristas()
        +void setVertices(deque~Vertice~ vertices)
        +void setAristas(deque~Arista~ aristas)
    }
    
    class Objeto {
        -string nombre
        -deque~Vertice~ vertices
        -deque~Cara~ caras
        +Objeto()
        +Objeto(string nombre)
        +string getNombre()
        +deque~Vertice~ getVertices()
        +deque~Cara~ getCaras()
        +void setNombre(string n)
        +void setVertices(deque~Vertice~ vertices)
        +void setCaras(deque~Cara~ caras)
        +Vertice puntoMayor()
        +Vertice puntoMenor()
    }
    
    class Vertice {
        -float x
        -float y
        -float z
        +Vertice()
        +Vertice(float x, float y, float z)
        +float getX()
        +float getY()
        +float getZ()
        +void setX(float x)
        +void setY(float y)
        +void setZ(float z)
    }

    class Sistema {
        -deque~Objeto~ objetos
        +Sistema()
        +deque~Objeto~ getObjetos()
        +void setObjetos(deque~Objeto~ o)
        +int buscarObjeto(string nombre)
        +bool nombreValido(string_view nombre)
        +bool numeroNaturalValido(string_view numero)
        +bool numeroEnteroValido(string_view numero)
        +bool validarArchivo(string ruta)
        +void crearAristas(Cara cara)
        +void cargarObjeto(string ruta)
        +void listado()
        +void agregarVerticesCara(deque~Vertice~ vertices, Cara cara, int i1, int i2, int i3, int i4)
        +void envolvente(Objeto objeto)
        +void envolvente()
        +void descargar(Objeto objeto)
        +void guardar(Objeto objeto, string nombre)
    }
    
    Vertice --> Arista
    Vertice --> Cara
    Arista --> Cara
    Cara --> Objeto
    Vertice --> Objeto
    Objeto --> Sistema
