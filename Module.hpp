#ifndef MODULE_H
#define MODULE_H

class Module {

	public:
		/* Constructor */
		Module();
		/* Default destructor */
		virtual ~Module();

		/* Main loop */
		void run();

		/* Initialize module settings */
		virtual bool initialize() = 0;
		/* Processing loop. */
		virtual void runTasks() = 0;

		/* Pause and unpause processing loop */
		bool pause();
		bool unPause();

	protected:
		bool paused;
};

#endif /* MODULE_H */
