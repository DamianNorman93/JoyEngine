:: g++ -I src/include -L src/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2 
:: g++ -I src/include -L src/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -mwindows
g++ -I src/include -L src/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image 
:: pause
:: cls
start main.exe 
:: exit
