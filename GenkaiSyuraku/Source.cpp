#include "MainFrame.hpp"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	// ログ出力を行わない
	DxLib::SetOutApplicationLogValidFlag(FALSE);

	// UTF-8に変更
	SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8);

	// ウインドウモードにする
	DxLib::ChangeWindowMode(TRUE);

	// 画面の解像度を指定する
	DxLib::SetGraphMode(1920, 1080, 32);

	// ウインドウのタイトルを変更する
	DxLib::SetMainWindowText("GenkaiSyuraku");

	// ライブラリの初期化
	if (DxLib::DxLib_Init() == -1) return false;

	// ロード中表示
	DxLib::DrawStringToHandle(600, 500, "Now Loading...\n■■■■", GetColor(255, 255, 255), CreateFontToHandle(NULL, 100, 0, DX_FONTTYPE_NORMAL));

	// 描画先グラフィック領域の指定
	DxLib::SetDrawScreen(DX_SCREEN_BACK);

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