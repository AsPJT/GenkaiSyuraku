//#define GENKAI_SYURAKU_TOUCH
#include "MainFrame.hpp"

#ifdef __ANDROID__
int android_main(void) {
#else
	int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
#endif

		// ログ出力を行わない
		::DxLib::SetOutApplicationLogValidFlag(FALSE);
		
		// UTF-8に変更
		::DxLib::SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8);

		// ウインドウモードにする
#ifndef __ANDROID__
		::DxLib::ChangeWindowMode(TRUE);
#endif

		// 画面の解像度を指定する
		::DxLib::SetGraphMode(1920, 1080, 32);

		// ウインドウのタイトルを変更する
#ifndef __ANDROID__
		::DxLib::SetMainWindowText(u8"GenkaiSyuraku");
#endif

		// ライブラリの初期化
		if (::DxLib::DxLib_Init() == -1) return false;

		// ロード中表示
		const int load_font{ ::DxLib::CreateFontToHandle(nullptr, 100, 0, DX_FONTTYPE_NORMAL) };

		::DxLib::DrawStringToHandle(650, 800, u8"Now Loading...\n■□□□□", ::DxLib::GetColor(255, 255, 255), load_font);
		::DxLib::LoadGraphScreen(0, 0, u8"image/title1.png", FALSE);

		::DxLib::DrawStringToHandle(650, 800, u8"Now Loading...\n■■□□□", ::DxLib::GetColor(255, 255, 255), load_font);
		::DxLib::ProcessMessage();

		// メインフレームを定義
		::MainFrame mainFrame;
		::DxLib::DrawStringToHandle(650, 800, u8"Now Loading...\n■■■□□", ::DxLib::GetColor(255, 255, 255), load_font);
		::DxLib::ProcessMessage();

		//ゲームを初期化
		mainFrame.init(load_font);

		// ゲームループ
		while (mainFrame.loop());

		// ゲームの終了処理
		mainFrame.end();

		return 0;
	}