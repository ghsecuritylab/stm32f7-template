#include "main_frame.h"
#include "main.h"
#include "cmsis_os.h"
#include "ff.h"

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "Framewin", ID_MAIN_FRAMEWIN_0, 1, 0, 480, 272, 0, 0x64, 0 },
  { BUTTON_CreateIndirect, "Button1", ID_MAIN_BUTTON_0, 42, 35, 143, 56, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button2", ID_MAIN_BUTTON_1, 202, 39, 150, 52, 0, 0x0, 0 },
};

extern uint8_t sdAppliReq;

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'Framewin'
    //
    hItem = pMsg->hWin;
    FRAMEWIN_SetText(hItem, "STM32F746G-DISCOVERY");
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_MAIN_BUTTON_0: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        sdAppliReq = 1;
        break;
      case WM_NOTIFICATION_RELEASED:
        
        break;
      }
      break;
    case ID_MAIN_BUTTON_1: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        HAL_NVIC_SystemReset();
        break;
      case WM_NOTIFICATION_RELEASED:
        
        break;
      }
      break;
    }
    break;
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       CreateFramewin
*/
WM_HWIN CreateFramewin(void);
WM_HWIN CreateFramewin(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}

/*************************** End of file ****************************/
