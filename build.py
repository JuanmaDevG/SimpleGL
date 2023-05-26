######################################################################################################################
#This build file automatically manages:
#
#-> The dependencies in this order: (ninja wrapper for python) (build.ninja file cosntruction) (compilation with ninja)
# (test compilation and run) (automated .obj file cleanup)
#
#-> Make a useful info log about ninja and it's compile and clean options
#
######################################################################################################################
from ninja import Writer

COMPILER = "clang++"
SOURCE_NAMES = "VBO EBO VAO Shader"

def writeFile():
    pass

if __name__ == "__main__":
    pass
    print("Build system ready")