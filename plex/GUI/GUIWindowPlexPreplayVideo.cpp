
#include "GUIDialogPlexAudioSubtitlePicker.h"

#include "GUIWindowPlexPreplayVideo.h"
#include "plex/PlexTypes.h"
#include "guilib/GUIWindow.h"
#include "filesystem/Directory.h"

#include "FileItem.h"
#include "guilib/GUILabelControl.h"
#include "ApplicationMessenger.h"
#include "PlexApplication.h"

CGUIWindowPlexPreplayVideo::CGUIWindowPlexPreplayVideo(void)
 : CGUIMediaWindow(WINDOW_PLEX_PREPLAY_VIDEO, "PlexPreplayVideo.xml")
{
}

CGUIWindowPlexPreplayVideo::~CGUIWindowPlexPreplayVideo()
{
}

bool
CGUIWindowPlexPreplayVideo::OnMessage(CGUIMessage &message)
{
  bool ret = CGUIMediaWindow::OnMessage(message);

  if (message.GetMessage() == GUI_MSG_WINDOW_INIT)
  {
    if (m_vecItems->GetContent() == "movies")
      m_vecItems->SetContent("movie");
    if (m_vecItems->GetContent() == "episodes")
      m_vecItems->SetContent("episode");
    
    g_plexApplication.m_preplayItem = m_vecItems->Get(0);
  } else if (message.GetMessage() == GUI_MSG_WINDOW_DEINIT)
    g_plexApplication.m_preplayItem.reset();
  
  
  return ret;
}

bool
CGUIWindowPlexPreplayVideo::OnAction(const CAction &action)
{
  if (action.GetID() == ACTION_PLAYER_PLAY)
  {
    CApplicationMessenger::Get().PlayFile(*m_vecItems->Get(0));
    return true;
  }
  
  return CGUIMediaWindow::OnAction(action);
}

CFileItemPtr
CGUIWindowPlexPreplayVideo::GetCurrentListItem(int offset)
{
  if (offset == 0 && m_vecItems->Size() > 0)
    return m_vecItems->Get(0);
  
  return CFileItemPtr();
}
