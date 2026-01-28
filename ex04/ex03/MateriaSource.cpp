#include "MateriaSource.hpp"
#include <iostream>

// --- Orthodox Canonical Form ---

MateriaSource::MateriaSource() {
    for (int i = 0; i < MATERIAS_LENGTH; i++) {
        _materias[i] = NULL;
    }
}

MateriaSource::MateriaSource(const MateriaSource& other) {
    for (int i = 0; i < MATERIAS_LENGTH; i++) {
        if (other._materias[i])
            _materias[i] = other._materias[i]->clone(); // deep copy
        else
            _materias[i] = NULL;
    }
}

void MateriaSource::assign(MateriaSource & other) {
    for (int i = 0; i < MATERIAS_LENGTH; i++) {
        if (this->_materias[i] && other._materias[i]) {
            if (this->_materias[i]->getType() == other._materias[i]->getType()) {
                *this->_materias[i] = *other._materias[i];
            } else {
                delete this->_materias[i];
                this->_materias[i] = other._materias[i]->clone();
            }
        } else {
            if (this->_materias[i] != NULL) {
                delete this->_materias[i];
            }
            this->_materias[i] = (other._materias[i] ?
                    other._materias[i]->clone():
                    NULL);
        }
    }
}

MateriaSource& MateriaSource::operator=(MateriaSource& other) {
    if (this!= &other) {
        this->assign(other);
    }
    return *this;
}

MateriaSource::~MateriaSource() {
    for (int i = 0; i < MATERIAS_LENGTH; i++) {
        if (_materias[i])
            delete _materias[i];
    }
}

// --- 主要なメソッドの実装 ---

void MateriaSource::learnMateria(AMateria* m) {
    if (!m) return;

    for (int i = 0; i < MATERIAS_LENGTH; i++) {
        if (_materias[i] == NULL) {
            _materias[i] = m; // ポインタを保存（所有権を受け取る）
            return;
        }
    }
    // 配列が満杯の場合の処理
    // 課題のmain例では new したものを直接渡しているため、
    // ここで保存できないとメモリリークする可能性がある。
    // 良い設計とは言えない気がする。仕方ない...
    std::cout << "MateriaSource is full!" << std::endl;
    delete m; 
}

AMateria* MateriaSource::createMateria(std::string const & type) {
    for (int i = 0; i < MATERIAS_LENGTH; i++) {
        if (_materias[i] != NULL && _materias[i]->getType() == type) {
            return _materias[i]->clone(); // 見つかったらクローンを返す
        }
    }
    return NULL;
}
