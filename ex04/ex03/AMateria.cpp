#include "ICharacter.hpp"
#include <string>
#include "AMateria.hpp"

AMateria::AMateria(): type("AMateria") {}

AMateria::AMateria(const AMateria &other) {
    *this = other;
}

AMateria &AMateria::operator=(const AMateria &other) {
    if (this == &other) {
    } else {
        this->type = other.type;
    }
    return *this;
}

AMateria::AMateria(std::string const & type): type(type) {
}

AMateria::~AMateria() {
}

std::string const & AMateria::getType() const {
    return this->type;
}

void AMateria::use(ICharacter& target) {
    (void) target;
}
