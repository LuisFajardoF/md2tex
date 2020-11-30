# md2tex

Herramienta para la elaboración de documentos PDF combinando Markdown y Latex. La herramienta
tiene como finalidad generar código Latex a partir de un texto elaborado en formato Markdown
en su mayoría ya que en el encabezado deben ír algunos parámetros de configuración para Latex.
La mayoría del texto debe estar escrito en formato Markdown, de manera que el programa pueda
reconocer un elemento de sintaxis de Markdown y construya un elemento recíproco en Latex. 

## Herramientas de Desarrollo
- cmake 3.13.4 (o superior)
- flex 2.6.4 (o superior)
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
# Section 1 {My First Section} 

special chars: { } : ; < > ! ¡ ``" @ $ % & * ( ) - _ = + ^ 
special chars: \ []' .,?¿Hola?
~~reserved words:~~ __logo, institution, title, subject, author, cover, report, date, place__ 

## Subsection 1

Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Augue eget arcu dictum varius duis at. Elementum curabitur vitae nunc sed velit dignissim sodales. Neque convallis a cras semper auctor neque vitae tempus. Rhoncus urna neque viverra justo nec. Velit euismod in pellentesque massa placerat duis ultricies.  

Tempor nec feugiat nisl pretium fusce id velit ut. Habitant morbi tristique senectus et. Egestas sed sed risus pretium quam. Scelerisque mauris pellentesque pulvinar pellentesque habitant morbi. Curabitur gravida arcu ac tortor dignissim. Ac turpis egestas maecenas pharetra.  

Lectus quam id leo in vitae turpis massa sed elementum. Leo duis ut diam quam nulla porttitor massa id neque. Tellus integer feugiat scelerisque varius morbi enim nunc faucibus a. In cursus turpis massa  tincidunt dui ut ornare lectus sit. Ac tortor dignissim convallis aenean et tortor at risus viverra.

#### Paragraph1
Quam quisque id diam vel quam elementum pulvinar etiam. Sit amet volutpat consequat mauris nunc congue nisi.

#### Paragraph2
unc congue nisi. Sodales ut eu sem integer vitae justo.

##### Subparagraph1
Lectus urna duis convallis convallis tellus id interdum velit laoreet. Massa id neque aliquam vestibulum morbi blandit cursus. Dolor sed viverra ipsum nunc aliquet bibendum enim facilisis gravida.

#####   ## Subparagraph2 ##
Elementum integer enim neque volutpat ac tincidunt vitae semper quis. Vivamus at augue eget arcu dictum. Arcu non odio euismod lacinia.

### SubSubSection1

# Section 2
Other plain text
This is plain text #

#### Paragraph3
hola:{};< >!¡``"@$%&*()-_=+^ \ []' .,?¿Hola?
```

En el archivo `input2.txt`:

```
**bold** *italic* *abc*
plain text
*italic*

_other italic_ ( _ ) {guion bajo}
__other bold__ __abc__ _abx_ ~~avc~~ 

# My Title with **bold** letter
#### **This paragraph is bold** 
**This text is bold** 

# My Title with __bold__ letter
#### __This paragraph is bold__ 
__This text is bold__ 

# My Title with *italic* letter
#### *This paragraph is italic* 
*This text is italic*

# My Title with _italic_ letter
#### _This paragraph is italic_ 
_This text is italic_

# My Title with ~~underline~~ letter
#### ~~This paragraph is underline~~ 
~~This text is underline~~
```

En el archivo `cover1.txt`:

```
!--
    cover: default {
        title: Gesti'on de Memoria Din'amica
        author: Luis E. Fajardo & 2nd Author
        date: today
    }
    enumerate: yes
--!

# Primera Secci'on

Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Elit at imperdiet dui accumsan sit amet nulla facilisi. Urna duis convallis convallis tellus id interdum velit laoreet. Mi eget mauris pharetra et ultrices neque ornare aenean euismod. Nulla aliquet enim tortor at. Purus sit amet volutpat consequat mauris. Risus ultricies tristique nulla aliquet. Faucibus nisl tincidunt eget nullam non nisi est sit amet. Mi bibendum neque egestas congue quisque egestas diam in. Lectus proin nibh nisl condimentum id venenatis. Egestas sed sed risus pretium quam vulputate dignissim suspendisse.


# Segunda Secci'on

Dis parturient montes nascetur ridiculus. Condimentum vitae sapien pellentesque habitant morbi tristique senectus. Bibendum est ultricies integer quis auctor elit sed vulputate mi. Ac tortor dignissim convallis aenean et tortor at risus. At urna condimentum mattis pellentesque id nibh tortor. Adipiscing commodo elit at imperdiet dui accumsan sit. Tortor aliquam nulla facilisi cras fermentum odio. Nunc id cursus metus aliquam. Commodo odio aenean sed adipiscing diam donec adipiscing tristique risus. Nec ultrices dui sapien eget mi proin sed libero. Proin sed libero enim sed faucibus turpis. Non tellus orci ac auctor. Nunc scelerisque viverra mauris in aliquam.
```

En el archivo `cover2.txt`:

```
!--
    cover: report {
        logo: logo_unitec123-4.jpg
        institution: Universidad Tecnol'ogica Centroamaericana
        title: Gesti'on de Memoria Din'amica
        subject: Sistemas Operativos
        author: Luis Fajardo & 2nd Author
        date: today
        place: San Pedro Sula
    }
    enumerate: no
--!

# First Section
Scelerisque varius morbi enim nunc faucibus a. Venenatis a condimentum vitae sapien. Ullamcorper a lacus vestibulum sed arcu non odio euismod lacinia. Erat nam at lectus urna duis convallis convallis. Sit amet mattis vulputate enim. Dictumst quisque sagittis purus sit amet volutpat consequat. Ullamcorper  dignissim cras tincidunt lobortis feugiat vivamus. Dapibus ultrices in iaculis nunc sed. Eu volutpat odio  facilisis mauris sit. Et netus et malesuada fames ac turpis egestas sed tempus. Cursus sit amet dictum sit  amet justo.

#### First Paragraph
Diam maecenas sed enim ut. Metus vulputate eu scelerisque felis. Varius vel pharetra vel turpis. Amet nulla facilisi morbi tempus iaculis urna id volutpat lacus. Penatibus et magnis dis parturient montes. Vitae justo eget magna fermentum iaculis eu non diam phasellus. Arcu cursus vitae congue mauris rhoncus aenean vel elit  scelerisque. Facilisi nullam vehicula ipsum a. Amet nisl purus in mollis. Vulputate eu scelerisque felis  imperdiet. Vel elit scelerisque mauris pellentesque pulvinar pellentesque habitant.

# Second Section
Urna duis convallis convallis tellus id interdum. Pellentesque dignissim enim sit amet venenatis. Blandit  turpis cursus in hac habitasse platea dictumst. Dictum sit amet justo donec enim diam. Tortor id aliquet  lectus proin nibh nisl condimentum. Maecenas volutpat blandit aliquam etiam. Urna molestie at elementum eu facilisis sed odio morbi. Id leo in vitae turpis. Elementum integer enim neque volutpat ac tincidunt vitae. Pharetra vel turpis nunc eget. In aliquam sem fringilla ut morbi tincidunt augue.

## Second Subsection
In arcu cursus euismod quis. Congue nisi vitae suscipit tellus. Integer enim neque volutpat ac tincidunt vitae semper. Accumsan lacus vel facilisis volutpat est velit egestas dui. Tristique risus nec feugiat in  fermentum posuere urna nec tincidunt. Amet facilisis magna etiam tempor. Elit ullamcorper dignissim cras  tincidunt lobortis feugiat. Vitae congue eu consequat ac felis donec. Ipsum dolor sit amet consectetur  adipiscing elit pellentesque. Tincidunt ornare massa eget egestas purus. Felis eget velit aliquet sagittis  id consectetur purus ut faucibus.
```

## Errores

#### Error en tiempo de ejecucion
```
terminate called after throwing an instance of 'std::out_of_range'
  what():  basic_string::replace: __pos (which is 32) > this->size() (which is 31)
```
Este error se genera cuando se encuentra un elemento de marcado negrita o subrayado al final de una cadena.

#### Causa
En el analisis lexico se deberan hacer validaciones para cuando un elemnento de enfasis
llega a fin de cadena.

**La unica manera de saltar este error es escribiendo mas texto despues de un elemento de enfasis o bien escribiendo un espacio al final de la cadena**