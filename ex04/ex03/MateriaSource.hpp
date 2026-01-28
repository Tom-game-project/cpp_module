#pragma once
#include "IMateriaSource.hpp"
#include "AMateria.hpp"
#ifndef __MATERIASOURCE_H__
#define __MATERIASOURCE_H__

#define MATERIAS_LENGTH 4

class MateriaSource: public IMateriaSource {
    private:
        AMateria* _materias[MATERIAS_LENGTH]; // 学習したマテリアのテンプレートを格納
        void assign(MateriaSource &other);

    public:
        MateriaSource();
        MateriaSource(const MateriaSource& other);
        MateriaSource& operator=(MateriaSource& other);
        virtual ~MateriaSource();

        virtual void learnMateria(AMateria* m);
        virtual AMateria* createMateria(std::string const & type);
};

#endif
