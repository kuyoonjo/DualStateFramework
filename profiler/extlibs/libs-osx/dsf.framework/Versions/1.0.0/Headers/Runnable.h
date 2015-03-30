//
//  Runnable.h
//  dsf
//
//  Created by Yu Chen on 10/17/14.
//
//

#ifndef dsf_Runnable_h
#define dsf_Runnable_h

namespace dsf
{
    /*! \brief Executing messages.
     * \details The interface provides a run method which executes messages.
     */
    class Runnable
    {
    public:
        /*! \brief State of the object.
         *
         * RUNNING: The object is running. <br>
         * STOPPED: The object is stopped. <br>
         * READY: The object is ready to run. <br>
         * DELETED: The object is marked as deleted. System will automatically delete it.
         */
        enum State
        {
            RUNNING, STOPPED, READY, DELETED
        };
        /*! Returns the current state. */
        virtual State getState() = 0;
    protected:
        /*! Executes messages */
        virtual void run() = 0;
    };
}

#endif
