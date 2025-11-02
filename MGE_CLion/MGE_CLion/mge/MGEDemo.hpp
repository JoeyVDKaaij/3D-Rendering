#ifndef MGEDEMO_HPP
#define MGEDEMO_HPP

#include "core/AbstractGame.hpp"

class DebugHud;

/**
 * An example subclass of AbstractGame showing how we can setup a scene.
 */
class MGEDemo: public AbstractGame
{
    //PUBLIC FUNCTIONS

	public:
		MGEDemo();
		~MGEDemo() override;

        //override initialize so we can add a DebugHud
        void initialize() override;

	protected:
	    //override so we can construct the actual scene
        void _initializeScene() override;

	    //override render to render the hud as well.
	    void _render() override;

	private:
		DebugHud* _hud;                   //hud display

        void _updateHud();

        MGEDemo(const MGEDemo&);
        MGEDemo& operator=(const MGEDemo&);
};

#endif // MGEDEMO_HPP
