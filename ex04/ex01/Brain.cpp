#include "Brain.hpp"

Brain::Brain() {
    for (int i = 0; i < LENGTH_OF_IDEAS; i++) {
        this->ideas[i] = "Idea";
    }
}

Brain::Brain(const Brain &other) {
    for (int i = 0; i < LENGTH_OF_IDEAS; i++) {
        this->ideas[i] = other.ideas[i];
    }
}

Brain &Brain::operator=(const Brain &other){
    if (this != &other) {
        for (int i = 0; i < LENGTH_OF_IDEAS; i++) {
            this->ideas[i] = other.ideas[i];
        }
    }
    return *this;
}

Brain::~Brain() {
}
