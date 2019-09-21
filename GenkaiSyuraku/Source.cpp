#include "MainFrame.hpp"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// メインフレームを定義
	MainFrame mainFrame;

	//ゲームを初期化
	mainFrame.init();

	// ゲームループ
	while(mainFrame.loop());

	// ゲームの終了処理
	mainFrame.end();

	return 0;
}