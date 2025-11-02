//
// Created by joey on 25/10/2025.
//

#ifndef MGE_CLION_ASSIGNMENT4DEMO_H
#define MGE_CLION_ASSIGNMENT4DEMO_H

#include "../MGEDemo.hpp"

class Assignment4Demo: public MGEDemo
{
    //PUBLIC FUNCTIONS

public:
    Assignment4Demo();
    virtual ~Assignment4Demo();

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

    Assignment4Demo(const Assignment4Demo&);
    Assignment4Demo& operator=(const Assignment4Demo&);
};

#endif //MGE_CLION_ASSIGNMENT4DEMO_H
