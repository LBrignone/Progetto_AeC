//
// Created by Luca Brignone on 27/10/22.
//

#ifndef PROGETTO_CONSTCONVERSION_HPP
#define PROGETTO_CONSTCONVERSION_HPP

template <typename containerType, typename ConstIt>
typename containerType::iterator constItToNonConstIt(containerType& c, ConstIt it)
{
    return c.erase(it, it);
}

#endif //PROGETTO_CONSTCONVERSION_HPP
