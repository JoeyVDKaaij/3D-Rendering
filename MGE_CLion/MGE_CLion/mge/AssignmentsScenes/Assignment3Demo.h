//
// Created by joey on 25/10/2025.
//

#ifndef MGE_CLION_ASSIGNMENT3DEMO_H
#define MGE_CLION_ASSIGNMENT3DEMO_H

#include "../MGEDemo.hpp"

class Assignment3Demo: public MGEDemo
{
    //PUBLIC FUNCTIONS

public:
    Assignment3Demo();
    virtual ~Assignment3Demo();

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

    Assignment3Demo(const Assignment3Demo&);
    Assignment3Demo& operator=(const Assignment3Demo&);
};

#endif //MGE_CLION_ASSIGNMENT3DEMO_H
