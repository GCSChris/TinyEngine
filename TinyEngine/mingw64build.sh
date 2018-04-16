# Run with sh mingw64build.sh


COMPILE="g++ -D MINGW -std=c++14 -shared -fPIC -static-libgcc -static-libstdc++ -I./include/ -I./pybind11/include/ `python3 -m pybind11 --includes` *.cpp -o mygameengine.pyd `python3-config --ldflags` -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_ttf -lSDL2_image -mwindows -L libwinpthread-1.dll"
COMPILE_TINY_MATH="g++ -D MINGW -std=c++14 -shared -fPIC -static-libgcc -static-libstdc++ -I./include/ -I./pybind11/include/ `python3 -m pybind11 --includes` tinymath.cpp -o tinymath.pyd `python3-config --ldflags` -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_ttf -lSDL2_image -mwindows -L libwinpthread-1.dll"


echo $COMPILE
echo "-------------------------------------------"
eval $COMPILE

echo $COMPILE_TINY_MATH
echo "-------------------------------------------"
eval $COMPILE_TINY_MATH
