#include <iostream>
#include <sstream>
#include <string>
#include <init.h>

int main()
{
    ios::sync_with_stdio(false);
    cerr.tie(nullptr);
    cerr << std::nounitbuf;
    string s;
    stringstream ss;
    int frame;

    // init_read();

    /*
        你可以在读入后进行一些相关预处理，时间限制：5秒钟
        init();
    */

    int totalFrame = 14400;
    for (int i = 0; i < totalFrame; i++)
    {
        // bool skip = frame_read(i);
        // if (skip) continue;

        /* 输出当前帧的操作，此处仅作示例 */
        cout << "Frame " << i << "\n";
        string player0_Action = "Move R";
        string player1_Action = "Move U";

        /* 合成一个字符串再输出，否则输出有可能会被打断 */
        string action = player0_Action + "\n" + player1_Action + "\n";
        cout << action;

        /* 不要忘记刷新输出流，否则游戏将无法及时收到响应 */
        cout << flush;
    }
}
