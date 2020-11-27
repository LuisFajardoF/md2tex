# md2tex

Herramienta para la elaboración de documentos PDF combinando Markdown y Latex. La herramienta
tiene como finalidad generar código Latex a partir de un texto elaborado en formato Markdown
en su mayoría ya que en el encabezado deben ír algunos parámetros de configuración para Latex.
La mayoría del texto debe estar escrito en formato Markdown, de manera que el programa pueda
reconocer un elemento de sintaxis de Markdown y construya un elemento recíproco en Latex. 

## Herramientas de Desarrollo
- cmake 3.13.4 (o superior)
- re2c 2.0.3
- bison 3.3.2 (o superior)
- treecc 0.3.11

Para instalar las herramientas de desarrollo en su ordenador, vaya al siguiente recurso: 
<a href="https://drive.google.com/file/d/1gjG3IdHRtXiU0dUrDh2AdgSdwRH9ri9h/view?usp=sharing" target="_blank">Herramientas de Desarrollo</a>

## Compilacion y ejecucion de md2tex

Este proyecto ha sido escrito en C++ haciendo uso de las herramientas mencionadas en el apartado
anterior. Los siguientes pasos son para compilar y ejecutar `md2tex`. 
```
mkdir build && cd build
cmake ../
make
./md2tex ../tests/yourfile.md
```

## Compilacion con Latex

Temporalmente podrá encontrar el código generado en `/latex/tex/` y compilarlo con los comandos
de compilación de Latex o haciendo uso de **CMake**. Si hace uso de **CMake** descargue <a href="cmake.org/Wiki/images/8/80/UseLATEX.cmake" target="_blank">UseLATEX.cmake</a> y copie el archivo en la carpeta `/latex/`.

Deberá crear un archivo `CMakeLists.txt` similar al siguiente:

```
cmake_minimum_required(VERSION 2.8.4)
project(UseLATEX_DOC NONE)

include(UseLATEX.cmake)

add_latex_document(
	tex/yourfile.tex
  )
```
Puede encontrar más información acerca de la construcción de archivos **CMakeLists.txt** en 
el siguiente recurso: <a href="https://gitlab.kitware.com/kmorel/UseLATEX/-/blob/master/UseLATEX.pdf" target="_blank">LATEX Document Building Made Easy</a>.

Para compilar con `pdflatex` utilizando **CMake** ejecute los siguientes comandos:

```
mkdir build && cd build
cmake ../
make
```

Si no se genera ningun error, su archivo PDF estará dentro de la carpeta `/build/`.

## Lo que el interprete hace hasta ahora

En el archivo `input.txt`:

```
!--
    cover : default {
        title: MyDocument
        date: today
        author: Pink Panter
    }
    class: article
--!

---

# Section 1 author 
## special chars: {} :;< >!¡``"@$%&*()-_=+^ ~ 
## \ []' .,?¿Hola?
## Subsection 1
### SubSubSection1
#### Paragraph1
#### Paragraph2
##### Subparagraph1
#####   ## Subparagraph2
### SubSubSection1
# Section 2
Other plain text
This is plain text #
hola:{};< >!¡``"@$%&*()-_=+^ ~ \ []' 
#### Section 3
.,?¿Hola?
---

# Page 2

---

## Page 3
```