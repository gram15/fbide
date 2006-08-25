#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

/**
 * This is a main application class.
 */

 class Main : public wxFrame
 {
     public:
        Main();
        ~Main();

        void OnClose (wxCloseEvent & event);

    private:
      DECLARE_EVENT_TABLE()
 };

#endif // MAIN_H_INCLUDED
