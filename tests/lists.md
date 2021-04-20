# Unordered List

## default
[unordered-list]{
    - item1
    - item2
    - item3
}

## label: ast 
[unordered-list; ast]{
    + item1
    + item2
    + item3
}

## label: cdot 
[unordered-list; cdot]{
    * item1
    * item2
    * item3
}

## label: circ 
[unordered-list; circ]{
* item1
* item2
* item3
}

## label: dash 
[unordered-list; dash]{
- item1
- item2
- item3
}

## label: diamond 
[unordered-list; diamond]{
- item1
- item2
- item3
}

## label: star 
[unordered-list; star]{
- item1
- item2
- item3
}

## label: triangle 
[unordered-list; triangle]{
- item1
- item2
- item3
}

## label: bullet _(default)_ and noitemsep 
[unordered-list; bullet; noitemsep]{
- item1
- item2
- item3
}

---

# Ordered List

## default
[ordered-list] {
    1. item1
    2. item2
    3. item3
}

## label: alph
[ordered-list; alph] {
    1. item1
    2. item2
    3. item3
}

## label: Alph
[ordered-list; Alph] {
    1. item1
    2. item2
    3. item3
}

## label: roman
[ordered-list; roman] {
    1. item1
    2. item2
    3. item3
}

## label: Roman
[ordered-list; Roman] {
    1. item1
    2. item2
    3. item3
}

## label: arabic _(default)_ and noitemsep
[ordered-list; arabic; noitemsep] {
    1. item1
    2. item2
    3. item3
}

---

# Nested List

## Soporta 6 niveles
#### Los primeros 4 adoptan el entorno _enumerate_ y los 'ultimos 2 adoptan el entorno _itemize_
#### El primer nivel debe comenzar al inicio de la l'inea y los subniveles deben 'ir separados por 4 espacios o un tab.
##### No se soportan bloques de texto dentro de los items en este tipo de lista.

[nested-list] {
1. Level 1
    a. Level 2
        i. Level 3
            A. Level 4
                + Level 5
                    * Level 6
                    * Level 6
                + Level 5
            B. Level 4
        ii. Level 3
    b. Level 2
2. Level 1
}

---

# Description List

## default description list
[description-list] {
    First. Item 1
    Second. Item 2
    Third. Item 3
}

## _description list_ param: noitemsep
[description-list; noitemsep] {
    First. Item 1
    Second. Item 2
    Third. Item 3
}

# ToDo List
[todo-list; noitemsep] {
    - item1
    + item2
    * item3
    + item4
    - item5
}
