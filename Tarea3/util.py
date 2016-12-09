import sys
import re

DEBUG = False
NUMERIC_TAG = '_NUMERIC_'
ALL_UPPERCASE_TAG = '_ALLUPPERCASE_'
LAST_UPPERCASE_TAG = '_LASTUPPERCASE_'
RARE_TAG = '_RARE_'
RARE_WORD_THRESHOLD = 5


def is_numeric(word):
    '''
    La palabra contiene a lo menos un caracter numerico
    '''
    find_numeric = False
    if re.match('[0-9]+', word):
        find_numeric = True
    return find_numeric


def is_all_uppercase(word):
    '''
    La palabra esta compuesta de letras mayusculas.
    '''
    all_uppercase = False
    if re.match('^[A-Z]+$', word):
        all_uppercase = True
    return all_uppercase


def is_last_uppercase(word):
    '''
    La palabra es rara, no todos son mayusculas y terminan con letras mayusculas.
    '''
    last_uppercase = False
    if re.match('.*[A-Z]$', word):
        last_uppercase = True
    return last_uppercase
    # return word[-1].isupper()


def rare_words_rule_p1(word):
    '''
    Remplazando infrequent words (Count(x) < 5) con simbolos comunes RARE.
    '''
    return RARE_TAG


def rare_words_rule_p3(word):
    '''
    Palabra raras que no estan incluidas en las demas palabras
    '''
    w = RARE_TAG
    if is_numeric(word):
        w = NUMERIC_TAG
    # caso contrario:
    if is_all_uppercase(word):
        w = ALL_UPPERCASE_TAG
    if is_last_uppercase(word):
        w = LAST_UPPERCASE_TAG
    return w


def process_rare_words(input_file, output_file, rare_words, processer):
    """
    Aplicando las reglas de palabras raras  para procesar el entrenamiento de la data
    """
    l = input_file.readline()
    while l:
        line = l.strip()
        if line:
            fields = line.split(' ')
            word = fields[0]
            tag = fields[-1]
            if word in rare_words:
                if DEBUG:
                    print 'Palabras raras: {word}, TAG: {tag}'.format(word=word, tag=processer(word))
                word = processer(word)  # Aplicando reglas de palabras raras
            output_file.write('{0} {1}\n'.format(word, tag))
        else:
            output_file.write('\n')
        l = input_file.readline()


def test_data_iterator(test_file):
    """
    Retorna un iterador que marca una palabra al mismo tiemp desde el test_file
    el test_file tiene una palabra en cada linea, la oraciones terminan con una linea en blanco
    """
    l = test_file.readline()
    while l:
        line = l.strip()
        if line:
            yield line  # una palabra
        else:
            yield None  # termino con una linea en blanco
        l = test_file.readline()


def test_sent_iterator(testdata_iterator):
    """
    Retorna un iterador
    """
    current_sentence = []  # Buffer de la oracion analisada
    for word in testdata_iterator:
            if word is None:
                if current_sentence:  # Procesando el final de la oracion
                    yield current_sentence
                    current_sentence = []  # Resetenado el buffer
                else:  # opteniendo una cadena vacia
                    sys.stderr.write("Peligro: opteniendo una cadena de entrada vacia.\n")
                    raise StopIteration
            else:
                current_sentence.append(word)  # Agregar un token a la salida

    if current_sentence:  # Si la ultima linea es blanca, nosotros la hacemos
        yield current_sentence   # Caso contrario existe mas tokens
                                # En el flujo retornan mas oraciones


def test():
    print is_last_uppercase('DDDeD')


if __name__ == '__main__':
    test()
