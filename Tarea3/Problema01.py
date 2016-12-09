from hmm import SimpleTagger
import util

def train(train_data_filename, rare_train_data_filename, hmm_model_filename):
    print '1. Entrenamiento hmm model'
    hmm_model = SimpleTagger(3)
    hmm_model.train(file(train_data_filename, 'r'))

    print . Reemplazar rare words 
    rare_words = hmm_model.rare_words
    util.process_rare_words(
        file(train_data_filename),
        file(rare_train_data_filename, 'w'),
        rare_words,
        util.rare_words_rule_p1)

    print '3. Entrenamiento modelo hmm de nuevo utilizando la nueva data (con RARE_TAG)'
    hmm_model_rare = SimpleTagger(3)
    hmm_model_rare.train(file(rare_train_data_filename))
    hmm_model_rare.write_counts(file(hmm_model_filename, 'w'))


def tag(test_data_filename, result_filename, hmm_model_filename):
    print '1. Cargar Hmm '
    tagger = SimpleTagger(3)
    tagger.read_counts(file(hmm_model_filename))

    print '2. Prueba de tag'
    tagger.tag(test_data_filename, result_filename)


def main():
    TRAIN = False
    # 1. Entrenamiento
    hmm_model_filename = 'p1.model'
    train_data_filename = 'gene.train'
    rare_train_data_filename = 'p1.gene.train'
    if TRAIN:
        train(train_data_filename, rare_train_data_filename, hmm_model_filename)

    # 2. tagging  o etiquetado
    test_data_filename = 'gene.dev'
    result_filename = 'gene_dev.p1.output'
    tag(test_data_filename, result_filename, hmm_model_filename)

if __name__ == '__main__':
    main()
