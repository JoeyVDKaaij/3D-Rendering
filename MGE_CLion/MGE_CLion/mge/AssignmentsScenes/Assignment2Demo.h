//
// Created by joey on 25/10/2025.
//

#ifndef MGE_CLION_ASSIGNMENT2DEMO_H
#define MGE_CLION_ASSIGNMENT2DEMO_H

#include "../MGEDemo.hpp"

class Assignment2Demo: public MGEDemo
{
    //PUBLIC FUNCTIONS

public:
    Assignment2Demo();
    virtual ~Assignment2Demo();

    //override initialize so we can add a DebugHud
    virtual void initialize();

protected:
    //override so we can construct the actual scene
    virtual void _initializeScene();

    //override render to render the hud as well.
    virtual void _render();

private:
    DebugHud* _hud;                   //hud display

    void _updateHud();

    Assignment2Demo(const Assignment2Demo&);
    Assignment2Demo& operator=(const Assignment2Demo&);
};

#endif //MGE_CLION_ASSIGNMENT2DEMO_H
