#pragma once
#ifndef __BRAIN_HPP__
#define __BRAIN_HPP__
#include <string>

#define LENGTH_OF_IDEAS 100
class Brain {
    public:
        Brain();
        Brain(const Brain &other);
        Brain&operator=(const Brain &other);
        virtual ~Brain();
    private:
        std::string ideas[LENGTH_OF_IDEAS];
};

#endif
