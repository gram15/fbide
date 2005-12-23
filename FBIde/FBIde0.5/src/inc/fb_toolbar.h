#ifndef FB_TOOLBAR_H_
#define FB_TOOLBAR_H_

class FB_Frame;

class FB_ToolBar {
    
    private:
        FB_Frame * m_Parent;
        wxToolBar * m_ToolBar;
        
        void ShowToolBar();
        void HideToolBar();
        
    public:
        FB_ToolBar( FB_Frame * parent );
        ~FB_ToolBar();
        void Show( bool status = true );
        void EnableTool(int toolId, const bool enable);
};

#endif
