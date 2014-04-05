Podstawowe tryby wyświetlania
Dźwięk przestrzenny openal

Aplikacja ma robić 2 rzeczy:
 Wyświetlać dowolny obiekt - wygenerować geometrię obiektu z biblioteki glut
Po naciśnięciu spacji obiekt ma wydawać dźwięk
Przy użyciu strzałek obiekt ma się przesuwac lewo prawo gora dol
Kamera ma się nie ruszać

Wyswietlanie 2 tryby:
     cieniowanie goranda - wierzchołki o losowych kolorach
     na 5+ tekstury

Oddać 8.04.2014


Kompilacja na linuksie:
g++ main.cpp -lGL -lGLU -lglut -lalut -lopenal -std=c++11

Użyte biblioteki na linuksie:
freealut 1.1.0
freeglut 2.8.1
openal-soft 1.15.1
