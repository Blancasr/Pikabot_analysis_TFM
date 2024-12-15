import sys

def create_hash(function_name):
    hash_=0
    for c in function_name:
        if (c == '\0'): break
        else:
            val = ord(c)
            hash_ = ((val | 0x60) + hash_ )*2
    return hash_

if (len(sys.argv) == 1):
    function_name = 'funcion_de_prueba'
    print("No se ha introducido ningún nombre de función como parámetro, introduzcala como primer argumento.\nSe usará 'función de prueba' como nombre.\n\n")
else:
    function_name = sys.argv[1]

print("Nombre de función:",function_name)
hash_ = create_hash(function_name)
print("Hash de la función:",hash_)