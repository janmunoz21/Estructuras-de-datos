#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Autor;
class Album;

class Cancion {
public:
    string nombre;  
    Autor* autor;    
    string genero;   
    Album* album;    
    int anio;        

    Cancion(string nombre, Autor* autor, string genero, Album* album, int anio)
        : nombre(nombre), autor(autor), genero(genero), album(album), anio(anio) {}
};

class Autor {
public:
    string nombre;                
    vector<Cancion*> canciones;   

    Autor(string nombre) : nombre(nombre) {}

    void agregarCancion(Cancion* cancion) {
        canciones.push_back(cancion);
    }

    // Método para obtener las canciones del autor ordenadas alfabéticamente
    vector<Cancion*> obtenerCancionesOrdenadas() {
        vector<Cancion*> cancionesOrdenadas = canciones;
        sort(cancionesOrdenadas.begin(), cancionesOrdenadas.end(), [](Cancion* a, Cancion* b) {
            return a->nombre < b->nombre;
        });
        return cancionesOrdenadas;
    }
};

class Album {
public:
    string nombre;                
    int anio;                     
    vector<Cancion*> canciones;   

    Album(string nombre, int anio) : nombre(nombre), anio(anio) {}

    // Método para agregar una canción al álbum
    void agregarCancion(Cancion* cancion) {
        canciones.push_back(cancion);
    }

    // Método para obtener las canciones del álbum ordenadas alfabéticamente
    vector<Cancion*> obtenerCancionesOrdenadas() {
        vector<Cancion*> cancionesOrdenadas = canciones;
        sort(cancionesOrdenadas.begin(), cancionesOrdenadas.end(), [](Cancion* a, Cancion* b) {
            return a->nombre < b->nombre;
        });
        return cancionesOrdenadas;
    }
};

class JaveMusic {
public:
    unordered_map<string, Autor*> autores;   
    unordered_map<string, Album*> albumes;   
    vector<Cancion*> canciones;              

    // Destructor de la clase JaveMusic para liberar la memoria asignada dinámicamente
    ~JaveMusic() {
        for (auto& par : autores) {
            delete par.second;
        }
        for (auto& par : albumes) {
            delete par.second;
        }
        for (auto& cancion : canciones) {
            delete cancion;
        }
    }

    // Método para obtener o crear un autor
    Autor* obtenerAutor(string nombre) {
        if (autores.find(nombre) == autores.end()) {
            autores[nombre] = new Autor(nombre);
        }
        return autores[nombre];
    }

    // Método para obtener o crear un álbum
    Album* obtenerAlbum(string nombre, int anio) {
        if (albumes.find(nombre) == albumes.end()) {
            albumes[nombre] = new Album(nombre, anio);
        }
        return albumes[nombre];
    }

    // Método para agregar una canción al sistema
    void agregarCancion(string nombre, string autorNombre, string genero, string albumNombre, int anio) {
        Autor* autor = obtenerAutor(autorNombre);
        Album* album = obtenerAlbum(albumNombre, anio);
        Cancion* nuevaCancion = new Cancion(nombre, autor, genero, album, anio);
        canciones.push_back(nuevaCancion);
        autor->agregarCancion(nuevaCancion);
        album->agregarCancion(nuevaCancion);
    }

    // Método para cargar canciones desde un archivo de texto
    void cargarDesdeArchivo(const string& rutaArchivo) {
        ifstream archivo(rutaArchivo);
        string linea;

        getline(archivo, linea); // Leer el número de canciones (no lo necesitamos para este código)
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string nombre, autorNombre, genero, albumNombre, anioStr;
            int anio;

            // Leer y separar cada campo de la línea
            getline(ss, nombre, '|');
            getline(ss, autorNombre, '|');
            getline(ss, genero, '|');
            getline(ss, albumNombre, '|');
            getline(ss, anioStr);
            anio = stoi(anioStr);

            // Agregar la canción al sistema
            agregarCancion(nombre, autorNombre, genero, albumNombre, anio);
        }
    }

    // Listar todos los autores presentes, ordenados alfabéticamente
    void listarAutoresOrdenados() {
        vector<string> autoresOrdenados;
        for (const auto& par : autores) {
            autoresOrdenados.push_back(par.first);
        }
        sort(autoresOrdenados.begin(), autoresOrdenados.end());
        for (const string& autor : autoresOrdenados) {
            cout << autor << endl;
        }
    }

    // Dado un autor, listar todas sus canciones ordenadas alfabéticamente
    void listarCancionesPorAutor(string autorNombre) {
        if (autores.find(autorNombre) != autores.end()) {
            vector<Cancion*> cancionesOrdenadas = autores[autorNombre]->obtenerCancionesOrdenadas();
            for (const auto& cancion : cancionesOrdenadas) {
                cout << cancion->nombre << endl;
            }
        } else {
            cout << "Autor no encontrado." << endl;
        }
    }

    // Listar todos los álbumes presentes, ordenados cronológicamente
    void listarAlbumesOrdenados() {
        vector<Album*> albumesOrdenados;
        for (const auto& par : albumes) {
            albumesOrdenados.push_back(par.second);
        }
        sort(albumesOrdenados.begin(), albumesOrdenados.end(), [](Album* a, Album* b) {
            return a->anio < b->anio;
        });
        for (const auto& album : albumesOrdenados) {
            cout << album->nombre << " (" << album->anio << ")" << endl;
        }
    }

    // Dado un álbum, listar todas las canciones ordenadas alfabéticamente
    void listarCancionesPorAlbum(string albumNombre) {
        for (const auto& par : albumes) {
            if (par.second->nombre == albumNombre) {
                vector<Cancion*> cancionesOrdenadas = par.second->obtenerCancionesOrdenadas();
                for (const auto& cancion : cancionesOrdenadas) {
                    cout << cancion->nombre << endl;
                }
                return;
            }
        }
        cout << "Álbum no encontrado." << endl;
    }

    // Listar todas las canciones y su álbum, ordenadas alfabéticamente primero por el álbum y después por el nombre de la canción
    void listarCancionesOrdenadasPorAlbum() {
        vector<pair<string, Cancion*>> cancionesOrdenadas;
        for (const auto& cancion : canciones) {
            cancionesOrdenadas.push_back({ cancion->album->nombre, cancion });
        }
        sort(cancionesOrdenadas.begin(), cancionesOrdenadas.end(), [](pair<string, Cancion*> a, pair<string, Cancion*> b) {
            if (a.first == b.first) {
                return a.second->nombre < b.second->nombre;
            }
            return a.first < b.first;
        });
        for (const auto& par : cancionesOrdenadas) {
            cout << par.second->nombre << " (" << par.second->album->nombre << ")" << endl;
        }
    }
};

int main() {
    JaveMusic javeMusic; // Crear una instancia de JaveMusic
    javeMusic.cargarDesdeArchivo("example3.txt"); // Cargar las canciones desde el archivo

    // Mostrar las funcionalidades solicitadas en el taller
    cout << "Autores ordenados alfabéticamente:" << endl;
    javeMusic.listarAutoresOrdenados();
    cout << endl;

    cout << "Canciones por autor (Autor3):" << endl;
    javeMusic.listarCancionesPorAutor("autor3");
    cout << endl;

    cout << "Álbumes ordenados cronológicamente:" << endl;
    javeMusic.listarAlbumesOrdenados();
    cout << endl;

    cout << "Canciones en el álbum 'album1_au3':" << endl;
    javeMusic.listarCancionesPorAlbum("album1_au3");
    cout << endl;

    cout << "Canciones ordenadas por álbum:" << endl;
    javeMusic.listarCancionesOrdenadasPorAlbum();
    cout << endl;

    return 0;
}
