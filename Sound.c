#include "Sound.h"



/*@breif    播放按钮音效
* @param    无
* @return	无
*/
void Play_Button_Sound()
{
    PlaySound(TEXT("Sound\\Button.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

